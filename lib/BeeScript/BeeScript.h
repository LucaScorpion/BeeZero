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

    bool processAssignVariable(const String &line);

    bool processCommand(const String &line);

    String resolveInput(const String &input);

    String readVariableName(const String &input, int startIndex);

public:
    static bool run(const String &script);
};

#endif
