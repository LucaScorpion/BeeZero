#include "Arduino.h"
#include "commands.cpp"

bool processLine(String line) {
    line.trim();

    // Check if the line is empty or a comment.
    if (line.length() == 0 || line[0] == '#') {
        return true;
    }

    // Get the command from the line.
    const int spaceIndex = line.indexOf(' ');
    const String command = line.substring(0, spaceIndex < 0 ? line.length() : spaceIndex);

    // Get the rest of the line as the command input.
    String input = spaceIndex < 0 ? "" : line.substring(spaceIndex + 1);
    input.trim();

    // Get the command function, check if it exists.
    const auto fn = commands.find(command);
    if (fn == commands.end()) {
        return false;
    }

    // Execute the command.
    return fn->second(input);
}

bool processScript(const String &script) {
    int lineStart = 0;
    int lineEnd = script.indexOf('\n');

    while (true) {
        // Get the current line.
        // If there is no newline, read until the end of the script.
        if (lineEnd < 0) {
            lineEnd = script.length();
        }
        const String line = script.substring(lineStart, lineEnd);

        // Process the line, check for errors.
        if (!processLine(line)) {
            return false;
        }

        // Check if we have reached the end of the script.
        if (lineEnd >= script.length()) {
            break;
        }

        // Get the next line positions.
        lineStart = lineEnd + 1;
        lineEnd = script.indexOf('\n', lineStart);
    }

    return true;
}
