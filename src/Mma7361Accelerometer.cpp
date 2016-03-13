#include "Arduino.h"
#include "Mma7361Accelerometer.h"

/**
 * Set the calibration for the sensor
 */
void Mma7361Accelerometer::calibrate(Mma7361Calibration userCalibration)
{
    calibration = userCalibration;
}

/**
 * Update sensor readings
 */
void Mma7361Accelerometer::update(int x, int y, int z) {
    rawVector.x = x;
    rawVector.y = y;
    rawVector.z = z;

    // Mark cached values as stale
    vectorStale = true;
    magnitudeStale = true;
}

/**
 * Get the gravity vector for the sensor
 */
ForceVector Mma7361Accelerometer::getForceVector()
{
    // Calculate vector if stale
    if (vectorStale) {
        vectorStale = false;

        // X
        float xDelta = (calibration.xMax - calibration.xMin) / 2;
        float xShift = (calibration.xMin + (xDelta));
        vector.x = (rawVector.x - xShift) / xDelta;

        // Y
        float yDelta = (calibration.yMax - calibration.yMin) / 2;
        float yShift = (calibration.yMin + (yDelta));
        vector.y = (rawVector.y - yShift) / yDelta;

        // Z
        float zDelta = (calibration.zMax - calibration.zMin) / 2;
        float zShift = (calibration.zMin + (zDelta));
        vector.z = (rawVector.z - zShift) / zDelta;
    }

    return vector;
}

/**
 * Get the gForce magnitude
 */
double Mma7361Accelerometer::getGForce()
{
    // Obtain vector by function, so it can refreshed if stale
    ForceVector localVector = getForceVector();

    // Calculate magnitude if stale
    if (magnitudeStale) {
        magnitudeStale = false;
        magnitude = sqrt(sq(localVector.x) + sq(localVector.y) + sq(localVector.z));
    }

    return magnitude;
}