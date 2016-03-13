#include "Arduino.h"
#include "Mma7361Accelerometer.h"
#include "display.h"

// Awkward include method for external libraries
// Remove this when PlatformIO supports extra lib dirs
#include "../../../src/Mma7361Accelerometer.cpp"

/**
 * Pins
 */
const int pinX = 14;        // X Axis
const int pinY = 15;        // Y Axis
const int pinZ = 16;        // Z Axis
const int pinSleep = 12;    // Sleep pin (can be replaced by pull-up to vcc)
const int pinLed = 13;      // Board LED pin

/**
 * Prefs
 */

const int displayFreq = 50;    // Frequency to output data to Serial

/**
 * Internal
 */

int displayBeat = HIGH;     // Last heartbeat LED state

Mma7361Accelerometer sensor;        // Sensor class
Mma7361Calibration calibration;     // Calibration struct

/**
 * Setup
 */
void setup()
{
    // Send LED high on startup
    pinMode(pinLed, OUTPUT);

    // Serial
    Serial.begin(9600);

    // Wake-up sensor by pulling pinSleep high.
    pinMode(pinSleep, INPUT_PULLUP);
    digitalWrite(pinSleep, HIGH);

    // Statically calibrate the sensor
    calibration.xMin = 235;
    calibration.xMax = 730;
    calibration.yMin = 280;
    calibration.yMax = 782;
    calibration.zMin = 215;
    calibration.zMax = 710;

    // Apply calibration
    sensor.calibrate(calibration);
}

/**
 * Main loop
 */
void loop()
{
    // Read sensor inputs
    int x = analogRead(pinX);
    int y = analogRead(pinY);
    int z = analogRead(pinZ);

    // Heartbeat LED
    displayBeat = (displayBeat == HIGH) ? LOW : HIGH;
    digitalWrite(pinLed, displayBeat);

    // Update sensor
    sensor.update(x, y, z);

    // Display some raw info
    displayClear();
    displayRaw(x, y, z);

    // Show the Gravity Vector
    displayGravityVector(sensor);

    // Show something human-readable
    displayObservations(sensor);

    // Wait for next call
    delay(displayFreq);
}

