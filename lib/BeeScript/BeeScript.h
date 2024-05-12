#ifndef BEESCRIPT_H
#define BEESCRIPT_H

#include <Arduino.h>
#include <map>

class BeeScript {
private:
    const String &script;

    std::map<String, String> context;

    explicit BeeScript(const String &script);

    bool execute();

    bool processLine(String line);

    bool assignVariable(const String &name, String input);

    String resolveInput(String input);

public:
    static bool run(const String &script);
};

#endif
