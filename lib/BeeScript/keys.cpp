#include <Arduino.h>
#include <Keyboard.h>
#include <map>

// See also: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers

const std::map<String, char> keys = {
    // Modifiers
    {"ctrl", KEY_LEFT_CTRL},
    {"shift", KEY_LEFT_SHIFT},
    {"alt", KEY_LEFT_ALT},
    {"option", KEY_LEFT_ALT},
    {"super", KEY_LEFT_GUI},
    {"command", KEY_LEFT_GUI},
    {"right-ctrl", KEY_RIGHT_CTRL},
    {"right-shift", KEY_RIGHT_SHIFT},
    {"altgr", KEY_RIGHT_ALT},
    {"option", KEY_RIGHT_ALT},
    {"right-super", KEY_RIGHT_GUI},
    {"right-command", KEY_RIGHT_GUI},

    // Misc
    {"up", KEY_UP_ARROW},
    {"down", KEY_DOWN_ARROW},
    {"left", KEY_LEFT_ARROW},
    {"right", KEY_RIGHT_ARROW},
    {"backspace", KEY_BACKSPACE},
    {"tab", KEY_TAB},
    {"return", KEY_RETURN},
    {"enter", KEY_RETURN},
    {"menu", KEY_MENU},
    {"esc", KEY_ESC},
    {"insert", KEY_INSERT},
    {"delete", KEY_DELETE},
    {"page-up", KEY_PAGE_UP},
    {"page-down", KEY_PAGE_DOWN},
    {"home", KEY_HOME},
    {"end", KEY_END},
    {"caps-lock", KEY_CAPS_LOCK},
    {"print-screen", KEY_PRINT_SCREEN},
    {"scroll-lock", KEY_SCROLL_LOCK},
    {"pause", KEY_PAUSE},

    // Numeric keypad
    {"num-lock", KEY_NUM_LOCK},
    {"kp-slash", KEY_KP_SLASH},
    {"kp-asterisk", KEY_KP_ASTERISK},
    {"kp-minus", KEY_KP_MINUS},
    {"kp-plus", KEY_KP_PLUS},
    {"kp-enter", KEY_KP_ENTER},
    {"kp-1", KEY_KP_1},
    {"kp-2", KEY_KP_2},
    {"kp-3", KEY_KP_3},
    {"kp-4", KEY_KP_4},
    {"kp-5", KEY_KP_5},
    {"kp-6", KEY_KP_6},
    {"kp-7", KEY_KP_7},
    {"kp-8", KEY_KP_8},
    {"kp-9", KEY_KP_9},
    {"kp-0", KEY_KP_0},
    {"kp-dot", KEY_KP_DOT},

    // Function
    {"f1", KEY_F1},
    {"f2", KEY_F2},
    {"f3", KEY_F3},
    {"f4", KEY_F4},
    {"f5", KEY_F5},
    {"f6", KEY_F6},
    {"f7", KEY_F7},
    {"f8", KEY_F8},
    {"f9", KEY_F9},
    {"f10", KEY_F10},
    {"f11", KEY_F11},
    {"f12", KEY_F12},
    {"f13", KEY_F13},
    {"f14", KEY_F14},
    {"f15", KEY_F15},
    {"f16", KEY_F16},
    {"f17", KEY_F17},
    {"f18", KEY_F18},
    {"f19", KEY_F19},
    {"f20", KEY_F20},
    {"f21", KEY_F21},
    {"f22", KEY_F22},
    {"f23", KEY_F23},
    {"f24", KEY_F24},
};

char getKey(String value) {
    if (value.length() == 1) {
        return value[0];
    }

    const auto mapped = keys.find(value);
    if (mapped != keys.end()) {
        return mapped->second;
    }

    return 0;
}
