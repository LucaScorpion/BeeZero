#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include <functional>

std::function<bool(String)> getCommand(const String &name);

bool commandDelay(const String &input);

bool commandHold(const String &input);

bool commandPress(const String &input);

bool commandRelease(const String &input);

bool commandType(const String &input);

#endif
