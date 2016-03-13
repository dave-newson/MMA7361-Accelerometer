#include "Arduino.h"
#include "Mma7361Accelerometer.h"
#include "Mma7361Calibrator.h"
#include "display.h"

// Awkward include method for external libraries
// Remove this when PlatformIO supports extra lib dirs
#include "../../../src/Mma7361Accelerometer.cpp"
#include "../../../src/Mma7361Calibrator.cpp"

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

const int displayFreq = 100;    // Frequency to output data to Serial

/**
 * Internal
 */

int displayLast = 0;        // Last millis something was displayed
int displayBeat = HIGH;     // Last heartbeat LED state
int rate = 0;               // Number of times looped since last display

Mma7361Calibrator calibrator;       // Calibration class
Mma7361Accelerometer sensor;        // Sensor class

Mma7361Calibration calibration;     // Calibration struct
Mma7361Calibration extremes;        // Extremes measured by calibrator

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
}

/**
 * Main loop
 */
void loop()
{
    // Record the loop rate
    rate++;

    // Read sensor inputs
    int x = analogRead(pinX);
    int y = analogRead(pinY);
    int z = analogRead(pinZ);

    // Dynamically calibrate sensor
    calibrator.calibrate(x, y, z);

    // Every 500ms, display the stats of calibration
    if (millis() - displayLast > displayFreq) {
        displayLast = millis();

        // Heartbeat LED
        displayBeat = (displayBeat == HIGH) ? LOW : HIGH;
        digitalWrite(pinLed, displayBeat);

        // Re-calibrate the update the sensor
        calibration = calibrator.getCalibration();
        sensor.calibrate(calibration);
        sensor.update(x, y, z);

        // Display some raw info
        displayClear();
        displayRate(rate);
        displayRaw(x, y, z);
        extremes = calibrator.getExtremes();
        displayCalibratorValues(calibration, extremes);

        // Show the Gravity Vector
        displayGravityVector(sensor);

        // Reset rate before next loop
        rate = 0;
    }
}