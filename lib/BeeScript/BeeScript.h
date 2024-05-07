#ifndef BEESCRIPT_H
#define BEESCRIPT_H

#include <Arduino.h>

class BeeScript {
private:
    static bool processLine(String line);

public:
    static bool processScript(const String &script);
};

#endif
