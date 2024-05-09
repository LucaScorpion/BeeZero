#ifndef BEESCRIPT_H
#define BEESCRIPT_H

#include <Arduino.h>

class BeeScript {
private:
    const String &script;

    explicit BeeScript(const String &script);

    bool execute();

    bool processLine(String line);

    bool assignVariable(const String &variable, String input);

public:
    static bool run(const String &script);
};

#endif
