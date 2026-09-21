# CSOPESY Marquee Console 
# Group 8 - FERRER, RODRIGO, ROGACION

This C++ console program accepts commands for setting, starting, stopping, and adjusting the speed of a left-and-right marquee animation.

## Quick Start

### Requirements

- `main.cpp`
- A C++17 compiler such as MinGW-w64 `g++`
- Command Prompt, Windows Terminal, or the Visual Studio Code terminal

### Run on Windows

1. Open the folder containing `main.cpp`.
2. Click the File Explorer address bar, type `cmd`, and press **Enter**.
3. Check that the compiler is available:

   ```cmd
   g++ --version
   ```

4. Compile the program:

   ```cmd
   g++ -std=c++17 main.cpp -o Marquee.exe -pthread
   ```

5. Run the program:

   ```cmd
   .\Marquee.exe
   ```

The welcome header and `Command> ` prompt should appear.

> **Important:** Run the program from an already-open terminal. If you double-click `Marquee.exe`, the window may close immediately after `exit`, making the termination messages difficult to see.

## Commands

| Command | Description |
| --- | --- |
| `help` | Displays all commands and their descriptions. |
| `set_text <text>` | Saves the text that will appear in the marquee. |
| `set_speed <number>` | Sets the animation delay from 10 to 1000 milliseconds. |
| `start_marquee` | Starts or resumes the marquee animation. |
| `stop_marquee` | Pauses the marquee animation at its current position. |
| `exit` | Terminates the console program. |

### Sample Command Sequence

Enter each command one at a time:

```text
help
set_text Operating Systems are fun!
set_speed 250
start_marquee
stop_marquee
exit
```


# Requirements Checklist
## Requirements for group review

Check each item once the group has reviewed and agreed on it. These boxes record requirements agreement, not completed implementation or testing.
  Ferrer  | Rodrigo  | Rogacion
- [ ]       [ ]        [ ] **Welcome header:** Display `Welcome to CSOPESY!` when the program starts.
- [ ]       [ ]        [ ] **Group developers:** Display `Group developer:` followed by Ferrer, Angel June; Rodrigo, Betina Heart; and Rogacion, Rob Nigel, each on a separate line.
- [ ]       [ ]        [ ] **Version date:** Display `Version date:` followed by a date in `YYYY-MM-DD` format. The supplied sample uses `2026-09-18`.
- [ ]       [ ]        [ ] **Command prompt:** Display exactly `Command> `, including one space after `>`.
- [ ]       [ ]        [ ] **Continuous loop:** Return to the prompt after processing each command, unless the user enters `exit` or the input stream ends.
- [ ]       [ ]        [ ] **Full-line input:** Use standard C++ input/output (`std::cin`, `std::cout`) and read the complete command line, preserving spaces within the supplied text. `std::getline(std::cin, input)` is suitable for the basic console.
- [ ]       [ ]        [ ] **Help output:** Display all six commands—help, start_marquee, stop_marquee, set_text, and set_speed, plus exit—with their descriptions matching the sample output.
- [ ]       [ ]        [ ] **Set text:** Accept `set_text <text>` on the same line. Recognize the command and separating space, extract the following text, and store it in a `std::string`. Display `Text saved for marquee: <text>` to confirm acceptance. For example, `set_text Operating Systems are fun!` saves the full phrase.
- [ ]       [ ]        [ ] **Start marquee:** Match start_marquee exactly and start or resume the text moving left and right while allowing the user to enter commands.
- [ ]       [ ]        [ ] **Stop marquee:** Match stop_marquee exactly and pause the animation at its current position.
- [ ]       [ ]        [ ] **Set speed:** Accept set_speed <milliseconds> and update the delay between movements. Accept whole numbers from 10 to 1000; lower values make the animation faster. Display an error for missing or invalid values and preserve the previous speed. 
- [ ]       [ ]        [ ] **Exit:** Match `exit` exactly, display `Terminating console...`, and end the command loop.
- [ ]       [ ]        [ ] **Unknown commands:** Display an error for unrecognized commands and return to `Command> ` without terminating the program. For example, `help123` must not execute `help`.
- [ ]       [ ]        [ ] **Incomplete set_text:** If `set_text` has no text or only whitespace after it, display a usage error, preserve any previously saved text, and return to the prompt.
