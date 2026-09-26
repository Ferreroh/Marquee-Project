/*
 * CSOPESY Marquee Project
 * Group 8
 *
 * Members:
 *   Ferrer, Angel June
 *   Rodrigo, Betina Heart
 *   Rogacion, Rob Nigel
 *
 * Version: 1
 *
 * Description:
 *   Displays the welcome header and handles the main command loop.
 *
 * Compile: g++ -std=c++17 main.cpp -o Marquee -pthread
 * Run: ./Marquee
 */

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cctype>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

int main() {
    // Display the welcome header and group details once.
    std::cout << "Welcome to CSOPESY!\n\n";
    std::cout << "Group developer: Group 8\n";
    std::cout << "Ferrer, Angel June\n";
    std::cout << "Rodrigo, Betina Heart\n";
    std::cout << "Rogacion, Rob Nigel\n\n";
    std::cout << "Version: 1\n";
    std::cout << "Version date: 2026-09-18\n\n";

    // Store the user's command and the text for the marquee.
    std::string command;
    std::string marqueeText;

    // These values must remain available between command-loop iterations.
    int speed = 100;
    bool marqueeRunning = false;
    bool endAnimation = false;
    std::size_t marqueePosition = 0;
    int marqueeDirection = 1;

    std::mutex stateMutex;
    std::mutex outputMutex;
    std::condition_variable animationCondition;

    // Run the marquee separately so the console can still accept commands.
    std::thread animationThread([&]() {
        constexpr std::size_t displayWidth = 60;
        std::unique_lock<std::mutex> stateLock(stateMutex);

        while (!endAnimation) {
            animationCondition.wait(stateLock, [&]() {
                return marqueeRunning || endAnimation;
            });

            if (endAnimation) {
                break;
            }

            const std::string text = marqueeText;
            const int frameDelay = speed;
            const bool textFitsDisplay = text.length() < displayWidth;
            const std::string scrollableText =
                textFitsDisplay ? text : " " + text + " ";
            const std::size_t maximumPosition =
                textFitsDisplay
                    ? displayWidth - text.length()
                    : scrollableText.length() - displayWidth;

            std::string frame;
            if (textFitsDisplay) {
                // Keep the original behavior for text shorter than the display.
                frame = std::string(marqueePosition, ' ') + text;
            }
            else {
                // Pan a fixed-width window across text that is 60 or more
                // characters long so the entire message remains animated.
                frame = scrollableText.substr(
                    marqueePosition,
                    displayWidth
                );
            }

            if (maximumPosition > 0) {
                if (marqueeDirection > 0 &&
                    marqueePosition >= maximumPosition) {
                    marqueeDirection = -1;
                }
                else if (marqueeDirection < 0 && marqueePosition == 0) {
                    marqueeDirection = 1;
                }

                if (marqueeDirection > 0) {
                    ++marqueePosition;
                }
                else {
                    --marqueePosition;
                }
            }

            stateLock.unlock();
            {
                std::lock_guard<std::mutex> outputLock(outputMutex);
                // Save the cursor, update the line above the prompt, and
                // restore the cursor so typed input remains in place.
                std::cout << "\033[s\033[1A\r\033[2KMarquee: "
                          << frame << "\033[u" << std::flush;
            }
            stateLock.lock();

            animationCondition.wait_for(
                stateLock,
                std::chrono::milliseconds(frameDelay),
                [&]() { return !marqueeRunning || endAnimation; }
            );
        }
    });

    // Keep displaying the prompt until the user exits.
    while (true) {
        {
            std::lock_guard<std::mutex> outputLock(outputMutex);
            std::cout << "Command> " << std::flush;
        }

        // Read the complete command, including spaces.
        // End the loop if input is no longer available.
        if (!std::getline(std::cin, command)) {
            break;
        }

        std::lock_guard<std::mutex> outputLock(outputMutex);

        if (command == "help") {
            // Display all commands and their descriptions.
            std::cout
                << "help - displays the commands and their descriptions\n"
                << "start_marquee - starts or resumes the marquee animation\n"
                << "stop_marquee - pauses the marquee animation\n"
                << "set_text <your_string> - saves text for the marquee\n"
                << "set_speed <milliseconds> - sets the refresh rate from 10 to 1000 ms\n"
                << "exit - terminates the console\n";
        }
        else if (command == "start_marquee") {
            // Start or resume the left-and-right animation.
            std::lock_guard<std::mutex> stateLock(stateMutex);
            if (marqueeText.empty()) {
                std::cout
                    << "Error: No marquee text has been set. "
                    << "Use set_text <your_string>.\n";
            }
            else if (marqueeRunning) {
                std::cout << "Marquee is already running.\n";
            }
            else {
                marqueeRunning = true;
                std::cout << "Marquee animation started.\n";
                animationCondition.notify_one();
            }
        }
        else if (command == "stop_marquee") {
            // Pause the animation at its current position.
            std::lock_guard<std::mutex> stateLock(stateMutex);
            if (!marqueeRunning) {
                std::cout << "Marquee is not running.\n";
            }
            else {
                marqueeRunning = false;
                std::cout << "Marquee animation stopped.\n";
                animationCondition.notify_one();
            }
        }
        else if (command == "set_text" ||
                 command.compare(0, 9, "set_text ") == 0) {
            // Accept text after "set_text " on the same line.
            const std::string newText =
                command.size() > 9 ? command.substr(9) : "";

            const bool blankText = newText.empty() ||
                newText.find_first_not_of(" \t\r\n") == std::string::npos;

            if (blankText) {
                std::cout
                    << "Error: No text provided. "
                    << "Use set_text <your_string>.\n";
            }
            else {
                std::lock_guard<std::mutex> stateLock(stateMutex);
                marqueeText = newText;
                marqueePosition = 0;
                marqueeDirection = 1;
                std::cout << "Text saved for marquee: "
                          << marqueeText << "\n";
                animationCondition.notify_one();
            }
        }
        else if (command == "set_speed" ||
                 command.compare(0, 10, "set_speed ") == 0) {
            // Get the value after "set_speed ".
            std::istringstream values(
                command.size() > 10 ? command.substr(10) : ""
            );

            int newSpeed;
            std::string extra;

            if (!(values >> newSpeed) || (values >> extra) ||
                newSpeed < 10 || newSpeed > 1000) {
                std::cout
                    << "Error: Use set_speed <10 to 1000 milliseconds>.\n";
            }
            else {
                std::lock_guard<std::mutex> stateLock(stateMutex);
                speed = newSpeed;
                std::cout << "Speed set to " << speed << " ms.\n";
                animationCondition.notify_one();
            }
        }
        else if (command == "exit") {
            // Stop and join the animation thread before ending the program.
            {
                std::lock_guard<std::mutex> stateLock(stateMutex);
                marqueeRunning = false;
                endAnimation = true;
            }
            animationCondition.notify_one();
            std::cout << "Terminating console...\n";
            std::cout << "Goodbye!\n";
            break;
        }
        else {
            // Display an error if the command is not recognized.
            std::cout << "Error: Unrecognized command. Type help.\n";
        }

        std::cout << "\n";
    }

    // Also clean up correctly when the input stream closes unexpectedly.
    {
        std::lock_guard<std::mutex> stateLock(stateMutex);
        marqueeRunning = false;
        endAnimation = true;
    }
    animationCondition.notify_one();

    if (animationThread.joinable()) {
        animationThread.join();
    }

    return 0;
}
