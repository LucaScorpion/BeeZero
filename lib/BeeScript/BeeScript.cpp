#include "BeeScript.h"
#include "commands.h"
#include "utils.h"
#include <Arduino.h>
#include <functional>

bool BeeScript::run(const String &script) {
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

    // Get the command from the line.
    const int spaceIndex = line.indexOf(' ');
    const String firstPart = line.substring(0, spaceIndex < 0 ? line.length() : spaceIndex);

    // Get the rest of the line as the command input.
    String rest = spaceIndex < 0 ? "" : line.substring(spaceIndex + 1);
    rest.trim();

    // Check if the command is a variable assignment.
    if (firstPart[0] == '$') {
        return assignVariable(firstPart, rest);
    }

    // Get the command function, check if it exists.
    const std::function<bool(String)> fn = getCommand(firstPart);
    if (fn) {
        // Resolve the input, execute the command.
        return fn(resolveInput(rest));
    }

    return false;
}

bool BeeScript::assignVariable(const String &name, String input) {
    input.trim();

    // Check if the input starts with an equals sign.
    if (input.indexOf('=') != 0) {
        return false;
    }

    context[name] = resolveInput(input.substring(1));
    return true;
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
