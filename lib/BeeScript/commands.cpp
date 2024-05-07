#include <Arduino.h>
#include <Keyboard.h>
#include <keys.cpp>
#include <functional>
#include <map>

inline bool commandHold(const String &input) {
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

        // Get the key code, check if it is valid.
        const char key = getKey(val);
        if (key == 0) {
            return false;
        }

        Keyboard.press(key);
    }

    return true;
}

inline bool commandRelease(const String &input) {
    if (input == "") {
        Keyboard.releaseAll();
    } else {
        // TODO: Currently this block is a duplicate of commandHold, that could probably be refactored.
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

            // Get the key code, check if it is valid.
            const char key = getKey(val);
            if (key == 0) {
                return false;
            }

            Keyboard.release(key);
        }
    }
    return true;
}

inline bool commandPress(const String &input) {
    return commandHold(input) && commandRelease(input);
}

inline bool commandSleep(const String &input) {
    const long ms = input.toInt();
    delay(ms);
    return true;
}

inline bool commandType(const String &input) {
    for (int i = 0; i < input.length(); i++) {
        Keyboard.write(input[i]);
    }
    return true;
}

const std::map<String, std::function<bool(String)>> commands = {
    {"hold", commandHold},
    {"press", commandPress},
    {"release", commandRelease},
    {"sleep", commandSleep},
    {"type", commandType},
};
