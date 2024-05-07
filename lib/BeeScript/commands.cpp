#include <Arduino.h>
#include <Keyboard.h>
#include <functional>
#include <map>

inline bool commandHold(String input) {
    // TODO
    return true;
}

inline bool commandPress(String input) {
    // TODO
    return true;
}

inline bool commandRelease(String input) {
    if (input == "") {
        Keyboard.releaseAll();
    } else {
        // TODO
    }
    return true;
}

inline bool commandSleep(String input) {
    const long ms = input.toInt();
    delay(ms);
    return true;
}

inline bool commandType(String input) {
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
