#include "BeeScript.h"
#include "commands.h"
#include "utils.h"
#include <Arduino.h>
#include <functional>

bool BeeScript::run(const String &script) {
    // Note that we can't use `std::make_unique` here instead of `new` and `delete`, since that's not in C++11.
    const auto bs = new BeeScript(script);
    const bool result = bs->execute();
    delete bs;
    return result;
}

BeeScript::BeeScript(const String &script) : script(script) {
}

bool BeeScript::execute() {
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

bool BeeScript::processLine(String line) {
    line.trim();

    // Check if the line is empty or a comment.
    if (line.length() == 0 || line[0] == '#') {
        return true;
    }

    // Check if the line is a variable assignment.
    if (line[0] == '$') {
        return processAssignVariable(line);
    }

    return processCommand(line);
}

bool BeeScript::processAssignVariable(const String &line) {
    // We already know the line starts with '$', so start at index 1.
    const String varName = readVariableName(line, 1);

    // Check if we have a valid variable name.
    if (varName.length() == 0) {
        return false;
    }

    // Get the rest of the line, this should start with a '='.
    String rest = line.substring(varName.length() + 1);
    rest.trim();
    if (!rest.startsWith("=")) {
        return false;
    }

    // Resolve the value, store it in the context.
    context[varName] = resolveInput(rest.substring(1));

    return true;
}

bool BeeScript::processCommand(const String &line) {
    // Get the command from the line.
    const int spaceIndex = line.indexOf(' ');
    const String firstPart = line.substring(0, spaceIndex < 0 ? line.length() : spaceIndex);

    // Get the rest of the line as the command input.
    String rest = spaceIndex < 0 ? "" : line.substring(spaceIndex + 1);
    rest.trim();

    // Get the command function, check if it exists.
    const std::function<bool(String)> fn = getCommand(firstPart);
    if (fn) {
        // Resolve the input, execute the command.
        return fn(resolveInput(rest));
    }

    return false;
}

String BeeScript::readVariableName(const String &input, const int startIndex = 0) {
    int endIndex = startIndex;
    for (int i = startIndex; i < input.length(); i++) {
        // Starting characters can be a letter or underscore.
        const char c = input[i];
        if (isAlpha(c) || c == '_') {
            continue;
        }

        // Non-starting characters can also be a number.
        if (i > startIndex && isDigit(c)) {
            continue;
        }

        break;
    }

    return input.substring(startIndex, endIndex);
}

String BeeScript::resolveInput(const String &input) {
    return input;

    // TODO

    // Can we use the forEachValue func here?

    String result = "";

    forEachValue(input, [&](const String &val) {
        result = "";

        // The return value is unused here, so just return true.
        return true;
    });

    return result;
}
