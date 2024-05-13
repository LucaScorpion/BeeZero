#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <functional>

bool forEachValue(const String &input, const std::function<bool(String)> &valueFn);

#endif
