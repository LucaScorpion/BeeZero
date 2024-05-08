#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include <functional>

std::function<bool(String)> getCommand(const String &name);

#endif
