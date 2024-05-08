#include "commands.h"
#include "keys.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <functional>
#include <map>

/**
 * Call a function for each value in an input string.
 * The input string is treated as space-separated values, multiple subsequent spaces are automatically skipped.
 * If a value function call returns `false`, no further values are processed and the function returns `false`.
 * If all values function calls return `true`, the function also returns `true`.
 *
 * @param input The command input.
 * @param valueFn The function to call for each value.
 * @return Whether all value function calls were successful.
 */
bool forEachValue(const String &input, const std::function<bool(String)> &valueFn) {
    int startIndex = 0;

    while (startIndex < input.length()) {
        // Get the end index, or set it to the string length if no space is found.
        int endIndex = input.indexOf(' ', startIndex);
        if (endIndex < 0) {
            endIndex = input.length();
        }

        // Get the input part.
        const String val = input.substring(startIndex, endIndex < 0 ? input.length() : endIndex);

        // Already set the next starting point.
        startIndex = endIndex + 1;

        // Skip empty values.
        if (val == "") {
            continue;
        }

        // Run the function with the value.
        if (!valueFn(val)) {
            return false;
        }
    }

    return true;
}

bool commandHold(const String &input) {
    return forEachValue(input, [](const String &val) {
        // Get the key code, check if it is valid.
        const char key = getKey(val);
        if (key == 0) {
            return false;
        }

        Keyboard.press(key);
        return true;
    });
}

bool commandRelease(const String &input) {
    if (input == "") {
        Keyboard.releaseAll();
        return true;
    }

    return forEachValue(input, [](const String &val) {
        // Get the key code, check if it is valid.
        const char key = getKey(val);
        if (key == 0) {
            return false;
        }

        Keyboard.release(key);
        return true;
    });
}

bool commandPress(const String &input) {
    return commandHold(input) && commandRelease(input);
}

bool commandDelay(const String &input) {
    const long ms = input.toInt();
    delay(ms);
    return true;
}

bool commandType(const String &input) {
    for (int i = 0; i < input.length(); i++) {
        Keyboard.write(input[i]);
    }
    return true;
}

bool commandTypeLn(const String &input) {
    const bool result = commandType(input);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    return result;
}

const std::map<String, std::function<bool(String)> > commands = {
    {"delay", commandDelay},
    {"hold", commandHold},
    {"press", commandPress},
    {"release", commandRelease},
    {"type", commandType},
    {"typeln", commandTypeLn},
};

std::function<bool(String)> getCommand(const String &name) {
    const auto fn = commands.find(name);
    return fn == commands.end() ? nullptr : fn->second;
}
