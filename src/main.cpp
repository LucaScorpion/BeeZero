#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <BeeScript.cpp>

/*****************
 * Configuration *
 *****************/

const String PAYLOAD_ONE_FILE = "one.txt";
const String PAYLOAD_TWO_FILE = "two.txt";

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

void runPayload(int number) {
    String script = readPayloadScript(number == 1 ? PAYLOAD_ONE_FILE : PAYLOAD_TWO_FILE);
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
    // TODO
    int mode = 0;

    if (mode == 0) {
        runDev();
    } else {
        runPayload(mode);
    }
}

void loop() {
    // Do nothing.
    delay(1);
}
