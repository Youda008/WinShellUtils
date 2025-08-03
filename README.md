# Windows Shell Utils

The existence of this repository is the result of the worst shell interpreter design in the history of mankind. It's hard to imagine a scripting language as sloppy and illogical as the Windows Command Line, where even the most basic things, that could be done with a simple one-liner in bash, require you to travel to depths of hell scary even to a Doom guy.


## Content

### set_output.bat

**Purpose**: Sets an output of a command into a specified environment variable.\
**How to use**: `call set_output.bat MY_OUTPUT_VAR program arg1 arg2 arg3`\
-> the output of command `program arg1 arg2 arg3` is exported into variable `%MY_OUTPUT_VAR%`

### GetKnownFolderPath.exe

**Purpose**: Retrieves the path of one of the standard Windows folders, such as Documents, Saves Games, AppData, ...\
**How to use**: `GetKnownFolderPath.exe SavedGames`\
**Possible folder names**: `GetKnownFolderPath.exe /list`\
**How to build in msys2/mingw**: `g++ -municode -D_UNICODE -o GetKnownFolderPath.exe GetKnownFolderPath.cpp -luuid -lole32 -static-libgcc -static-libstdc++`\
**How to build in MS tools**: I hope you tell me.

### GetKnownFolderPath.bat

**Purpose**: Combines the two utils above together for a slightly easier usage.\
**How to use**: `GetKnownFolderPath.bat SAVED_GAMES_DIR SavedGames`\
-> the full path of the "Saved Games" directory is stored in variable `%SAVED_GAMES_DIR%`
