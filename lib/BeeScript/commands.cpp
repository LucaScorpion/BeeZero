#include <Arduino.h>
#include <functional>
#include <iostream>
#include <map>

inline bool commandHold(String input) {
    std::cout << "hold " << input << std::endl;
    return true;
}

inline bool commandPress(String input) {
    std::cout << "press " << input << std::endl;
    return true;
}

inline bool commandRelease(String input) {
    if (input == "") {
        std::cout << "release all" << input << std::endl;
        return true;
    }

    std::cout << "release " << input << std::endl;
    return true;
}

inline bool commandSleep(String input) {
    const long ms = input.toInt();
    delay(ms);
    return true;
}

inline bool commandType(String input) {
    std::cout << "type " << input << std::endl;
    return true;
}

const std::map<String, std::function<bool(String)>> commands = {
    {"hold", commandHold},
    {"press", commandPress},
    {"release", commandRelease},
    {"sleep", commandSleep},
    {"type", commandType},
};
