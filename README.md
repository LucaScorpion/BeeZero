# BeeZero

BeeZero is an Arduino-based keystroke injection USB stick.
It's inspired by the [Hak5 USB Rubber Ducky],
and meant as a tool for educational and training purposes.

## BeeScript

The BeeZero runs a simple custom scripting language called BeeScript.
For the scripting documentation, see [BeeScript.md](BeeScript.md).

## Hardware and Wiring

The BeeZero project is designed for the [Seeeduino XIAO],
but should work with any Arduino that supports the [Keyboard library].
A more complete board is the [Arduino MKR Zero],
which has a built-in SD card slot and small form factor,
requiring very minimal work to set everything up.

The default setup requires the following components:

- An Arduino board with SD card slot
- A single pole double throw on-off-on (SPDT) switch

An SPDT switch is a switch that can switch between three states.
This is used to select one of two payloads,
or to disable the payload for development purposes.

To connect the switch to your board, connect the center pole to ground,
and the other poles to pins 1 and 2.
When one of those pins is low, the board will run the respective payload.

![Wiring diagram](images/wiring.png)

Connecting the Arduino to a computer can be done by using the USB port,
or by soldering a USB connector directly to it.
The MKR Zero has some additional pads on the back which can be used for this:

![Backside wiring diagram](images/wiring-back.png)

Note that the USB data pads are not documented in the pinout diagrams,
but these can be found in the wiring schematics.

## Payloads

The BeeZero expects an SD card with two files: `one.txt` and `two.txt`.
These files are run as BeeScript when their respective pin is pulled low by the switch.
To disable the payloads, set the switch to the off state to ensure neither pin is connected to ground.

**Note:** the BeeZero only checks the pin states on boot,
so the switch should be set to the desired position _before_ plugging in the device.

## Troubleshooting

To check if the BeeZero and SD card are properly set up you can connect it to a computer in mode 0 (no payload).
It will run some checks, and if everything is okay, the built-in LED will turn on.
It will also output debug information over serial, about the SD connection and payload files.

After running a payload, the LED will also indicate if the run was successful.
If it was, it will be on continuously.
Otherwise, if an error occurred, it will blink based on the type of error.

| Number of blinks | Error                                 | Solution                                                                          |
|------------------|---------------------------------------|-----------------------------------------------------------------------------------|
| 1                | The SD card could not be initialized. | Check if the SD card is inserted and formatted properly (as FAT).                 |
| 2                | The payload file could not be read.   | Check if the right payload file exists. Note that the filename is case sensitive. |
| 3                | A payload script error occurred.      | Check if the script is valid.                                                     |

[Hak5 USB Rubber Ducky]: https://docs.hak5.org/hak5-usb-rubber-ducky

[Seeeduino XIAO]: https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html

[Arduino MKR Zero]: https://docs.arduino.cc/hardware/mkr-zero

[Keyboard library]: https://www.arduino.cc/reference/en/language/functions/usb/keyboard
