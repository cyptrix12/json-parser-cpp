# JSON Parser in C++

This project is a simple JSON parser implemented in C++. It serves as a foundational tool for parsing JSON files.

## How to Use

1. **Compile the Code**:
   - Use your preferred C++ compiler to build the executable from the source code.

2. **Run the Executable**:
   - Open a terminal and navigate to the directory containing the compiled executable.
   - Execute the program by typing its name and pressing Enter.

3. **Available Commands**:
   - `h`: Display the help menu with a list of available commands.
   - `o <filename>`: Open a JSON file for parsing.
     - Example: To open a file named `data.json`, type `o data.json`.
     - The program will confirm if the file was opened successfully.
   - `c`: Parse the currently opened JSON file.

## Example Workflow

1. Compile the program:

   ```bash
   g++ -o json_parser plik.cpp
   ```

2. Run the program:

   ```bash
   ./json_parser
   ```

3. In the program:

   - Type `h` to view the help menu.
   - Open a JSON file by typing `o data.json`.
   - Parse the opened file by typing `c`.

## Notes
 - cpp file is written in polish.
