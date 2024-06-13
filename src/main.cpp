#include <Arduino.h>
#include <Keyboard.h>
#include <SD.h>
#include "BeeScript.h"

/*****************
 * Configuration *
 *****************/

const String PAYLOAD_ONE_FILE = "one.txt";
const String PAYLOAD_TWO_FILE = "two.txt";

#ifndef PAYLOAD_ONE_PIN
constexpr int PAYLOAD_ONE_PIN = 1;
#endif
#ifndef PAYLOAD_TWO_PIN
constexpr int PAYLOAD_TWO_PIN = 2;
#endif
#ifndef BUTTON_PIN
constexpr int BUTTON_PIN = 3;
#endif

/*******
 * Run *
 *******/

enum class Result {
    SUCCESS = 0,
    SD_ERROR = 1,
    FILE_ERROR = 2,
    SCRIPT_ERROR = 3,
};

Result runPayload(const String &file) {
    // Initialize the SD card.
    if (!SD.begin()) {
        return Result::SD_ERROR;
    }

    // Open the payload file.
    File dataFile = SD.open(file, FILE_READ);
    if (!dataFile) {
        return Result::FILE_ERROR;
    }

    // Read the file contents and close it.
    const String script = dataFile.readString();
    dataFile.close();

    // Execute the script.
    Keyboard.begin();
    return BeeScript::run(script) ? Result::SUCCESS : Result::SCRIPT_ERROR;
}

Result runDebug() {
    Result status = Result::SUCCESS;

    // Begin serial output, wait a bit to ensure the monitor is ready.
    Serial.begin(9600);
    delay(2000);
    Serial.println("Hello from BeeZero");

    // Check if the SD card can be read.
    Serial.print("SD initialization... ");
    if (!SD.begin()) {
        Serial.println("failed");
        status = Result::SD_ERROR;
    } else {
        Serial.println("done");

        // Check if the payload scripts exist.
        const bool oneExists = SD.exists(PAYLOAD_ONE_FILE);
        Serial.print("Payload one file (" + PAYLOAD_ONE_FILE + ")... ");
        Serial.println(oneExists ? "exists" : "not found");
        const bool twoExists = SD.exists(PAYLOAD_TWO_FILE);
        Serial.print("Payload two file (" + PAYLOAD_TWO_FILE + ")... ");
        Serial.println(twoExists ? "exists" : "not found");

        if (!oneExists || !twoExists) {
            status = Result::FILE_ERROR;
        }
    }

    Serial.println("All checks done");
    return status;
}

/***********
 * Arduino *
 ***********/

Result status = Result::SUCCESS;

void led(const bool on) {
#ifndef LED_INVERTED
    const int val = on ? HIGH : LOW;
#else
    const int val = on ? LOW : HIGH;
#endif
    digitalWrite(LED_BUILTIN, val);
}

void setup() {
    // Initialize the pins.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PAYLOAD_ONE_PIN, INPUT_PULLUP);
    pinMode(PAYLOAD_TWO_PIN, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Read the payload mode and execute.
    if (digitalRead(PAYLOAD_ONE_PIN) == LOW) {
        status = runPayload(PAYLOAD_ONE_FILE);
    } else if (digitalRead(PAYLOAD_TWO_PIN) == LOW) {
        status = runPayload(PAYLOAD_TWO_FILE);
    } else {
        status = runDebug();
    }

    led(true);
}

void loop() {
    // On success, do nothing.
    if (status == Result::SUCCESS) {
        delay(1);
        return;
    }

    // If an error occurred, blink.
    const int blinks = (int) status;
    for (int i = 0; i < blinks; i++) {
        led(true);
        delay(200);
        led(false);
        delay(200);
    }
    delay(800);
}
