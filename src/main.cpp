#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <BeeScript.cpp>

const String payloadOneFile = "one.txt";
const String payloadTwoFile = "two.txt";

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
    String script = readPayloadScript(number == 1 ? payloadOneFile : payloadTwoFile);
    processScript(script);
}

void runDev() {
    // Begin serial output, wait a bit to ensure the monitor is ready.
    Serial.begin(9600);
    delay(2000);
    Serial.println("Hello from BeeZero");
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
        // runPayload(mode);
    }
}

void loop() {
    // Do nothing.
    delay(1);
}
