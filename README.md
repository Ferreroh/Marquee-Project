# CSOPESY Marquee Console 
# Group 8 - FERRER, RODRIGO, ROGACION

This C++ console program accepts commands for setting, starting, stopping, and adjusting the speed of a left-and-right marquee animation.

## Quick Start

### Prerequisites

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
