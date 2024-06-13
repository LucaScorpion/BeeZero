#include "commands.h"
#include "keys.h"
#include "utils.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <map>

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

bool commandWrite(const String &input) {
    for (int i = 0; i < input.length(); i++) {
        Keyboard.write(input[i]);
    }
    return true;
}

bool commandWriteLn(const String &input) {
    const bool result = commandWrite(input);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    return result;
}

const std::map<String, std::function<bool(String)> > commands = {
        {"delay",   commandDelay},
        {"hold",    commandHold},
        {"press",   commandPress},
        {"release", commandRelease},
        {"led",     commandWrite},
        {"writeln", commandWriteLn},
};

std::function<bool(String)> getCommand(const String &name) {
    const auto fn = commands.find(name);
    return fn == commands.end() ? nullptr : fn->second;
}
