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
 * Compile: g++ -std=c++17 Marquee.cpp -o Marquee
 * Run: ./Marquee
 */

#include <iostream>
#include <string>
#include <sstream>

int main() {
    // Display the welcome header and group details once.
    std::cout << "Welcome to CSOPESY!\n\n";
    std::cout << "Group developer: Group 8\n";
    std::cout << "Ferrer, Angel June\n";
    std::cout << "Rodrigo, Betina Heart\n";
    std::cout << "Rogacion, Rob Nigel\n\n";
    std::cout << "Version: 1\n";
    std::cout << "Version date: 2026-09-18\n\n";

    // Store the user's command and the text for the marquee
    std::string command;
    std::string marqueeText;

    // Keep displaying the prompt until the user exits.
    while (true) {
        int speed = 100;
        std::cout << "Command> ";

        // Read the complete command, including spaces.
        // End the loop if input is no longer available.
        if (!std::getline(std::cin, command)) {
            break;
        }

        if (command == "help") {
            // Display all commands and their descriptions.
            std::cout
            << "help - displays the commands and its description\n"
            << "start_marquee - starts the marquee \"animation\"\n"
            << "stop_marquee - stops the marquee \"animation\"\n"
            << "set_text - accepts a text input and displays it as a marquee\n"
            << "set_speed - sets the marquee animation refresh in milliseconds\n"
            << "exit - terminates the console\n";
        }
        else if (command == "start_marquee") {
            // Insert start marquee logic here.
            // Start or resume the left-and-right animation.
        }
        else if (command == "stop_marquee") {
            // Insert stop marquee logic here.
            // Pause the animation at its current position.
        }
        else if (command == "set_text" ||
                 command.compare(0, 9, "set_text ") == 0) {
            // Insert set text logic here.
            // Accept text after "set_text " on the same line.
            // Check for missing or blank text before saving.
            // Store valid text in marqueeText and display confirmation.
        }
        else if (command == "set_speed" ||
                 command.compare(0, 10, "set_speed ") == 0) {
                    // Get the value after "set_speed ".
            std::istringstream values(
                command.size() > 9 ? command.substr(10) : ""
            );

            int newSpeed;
            std::string extra;

            if (!(values >> newSpeed) || (values >> extra) ||
                newSpeed < 10 || newSpeed > 1000) {
                std::cout
                    << "Error: Use set_speed <10 to 1000 milliseconds>.\n";
            }
            else {
                speed = newSpeed;
                std::cout << "Speed set to " << speed << " ms.\n";
            }
        }
        else if (command == "exit") {
            // Insert animation cleanup here before ending the program.
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

    return 0;
}