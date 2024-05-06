#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <BeeScript.cpp>

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

String readPayloadScript(String file) {
    // Initialize the SD card.
    if (!SD.begin()) {
        return "";
    }

    // Open the payload file.
    File dataFile = SD.open(file, FILE_READ);
    if (!dataFile) {
        return "";
    }

    // Read the file contents and close it.
    String contents = dataFile.readString();
    dataFile.close();

    return contents;
}

void runPayload(String file) {
    String script = readPayloadScript(file);
    processScript(script);
}

void runDev() {
    // Begin serial output, wait a bit to ensure the monitor is ready.
    Serial.begin(9600);
    delay(2000);
    Serial.println("Hello from BeeZero");

    // Check if the SD card can be read.
    if (!SD.begin()) {
        Serial.println("SD initialization failed");
    } else {
        Serial.println("SD initialization done");

        // Check if the payload scripts exist.
        if (!SD.open(PAYLOAD_ONE_FILE, FILE_READ)) {
            Serial.println("Payload one file not found: " + PAYLOAD_ONE_FILE);
        }
        if (!SD.open(PAYLOAD_TWO_FILE, FILE_READ)) {
            Serial.println("Payload two file not found: " + PAYLOAD_ONE_FILE);
        }
    }

    Serial.println("All checks done");
}

/***********
 * Arduino *
 ***********/

void setup() {
    // Initialize the pins.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PAYLOAD_ONE_PIN, INPUT_PULLDOWN);
    pinMode(PAYLOAD_TWO_PIN, INPUT_PULLDOWN);

    // Read the payload mode and execute.
    if (digitalRead(PAYLOAD_ONE_PIN) == HIGH) {
        runPayload(PAYLOAD_ONE_FILE);
    } else if (digitalRead(PAYLOAD_TWO_PIN) == HIGH) {
        runPayload(PAYLOAD_TWO_FILE);
    } else {
        runDev();
    }

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    // Do nothing.
    delay(1);
}
