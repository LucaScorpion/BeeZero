#include <Arduino.h>
#include <Keyboard.h>
#include <SD.h>
#include <SPI.h>
#include "BeeScript.h"

/*****************
 * Configuration *
 *****************/

const String PAYLOAD_ONE_FILE = "one.txt";
const String PAYLOAD_TWO_FILE = "two.txt";

constexpr int PAYLOAD_ONE_PIN = 1;
constexpr int PAYLOAD_TWO_PIN = 2;

/*******
 * Run *
 *******/

typedef enum {
    SUCCESS = 0,
    SD_ERROR = 1,
    FILE_ERROR = 2,
    SCRIPT_ERROR = 3,
} Result;

Result runPayload(const String &file) {
    // Initialize the SD card.
    if (!SD.begin()) {
        return SD_ERROR;
    }

    // Open the payload file.
    File dataFile = SD.open(file, FILE_READ);
    if (!dataFile) {
        return FILE_ERROR;
    }

    // Read the file contents and close it.
    const String script = dataFile.readString();
    dataFile.close();

    // Execute the script.
    Keyboard.begin();
    return BeeScript::run(script) ? SUCCESS : SCRIPT_ERROR;
}

Result runDebug() {
    Result status = SUCCESS;

    // Begin serial output, wait a bit to ensure the monitor is ready.
    Serial.begin(9600);
    delay(2000);
    Serial.println("Hello from BeeZero");

    // Check if the SD card can be read.
    Serial.print("SD initialization... ");
    if (!SD.begin()) {
        Serial.println("failed");
        status = SD_ERROR;
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
            status = FILE_ERROR;
        }
    }

    Serial.println("All checks done");
    return status;
}

/***********
 * Arduino *
 ***********/

Result status = SUCCESS;

void setup() {
    // Initialize the pins.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PAYLOAD_ONE_PIN, INPUT_PULLUP);
    pinMode(PAYLOAD_TWO_PIN, INPUT_PULLUP);

    // Read the payload mode and execute.
    if (digitalRead(PAYLOAD_ONE_PIN) == LOW) {
        status = runPayload(PAYLOAD_ONE_FILE);
    } else if (digitalRead(PAYLOAD_TWO_PIN) == LOW) {
        status = runPayload(PAYLOAD_TWO_FILE);
    } else {
        status = runDebug();
    }

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    // On success, do nothing.
    if (status == SUCCESS) {
        delay(1);
        return;
    }

    // If an error occurred, blink.
    for (int i = 0; i < status; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
    delay(800);
}
