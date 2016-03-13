#include "Mma7361Calibrator.h"
#include "Arduino.h"

/**
 * Run a single calibrate cycle
 */
void Mma7361Calibrator::calibrate(int x, int y, int z) {
    // Record: Stable readings only
    if (isStable(x, &stableX) && isStable(y, &stableY) && isStable(z, &stableZ)) {
        storeReadings(x, &readingsX);
        storeReadings(y, &readingsY);
        storeReadings(z, &readingsZ);
    }

    // Record: Unstable readings (includes over-G and under-G data)
    storeReadings(x, &unstableX);
    storeReadings(y, &unstableY);
    storeReadings(z, &unstableZ);
}

/**
 * Verify the given axis is stable.
 */
bool Mma7361Calibrator::isStable(int x, stabilityTracker *tracker) {

    // Add to tracker
    tracker->stack[tracker->current] = x;
    
    // Increment tracker post
    tracker->current++;

    // Reset current if out of bounds
    if (tracker->current >= tracker->size) {
        tracker->current = 0;
        tracker->enabled = true;
    }

    if (!tracker->enabled) {
        return false;
    }

    // Get min/max for threshold check
    int min = 1024;
    int max = 0;
    for (int i=0; i < tracker->size; i++) {
        min = tracker->stack[i] < min ? tracker->stack[i] : min;
        max = tracker->stack[i] > max ? tracker->stack[i] : max;
    }

    // Return true if axis is within threshold
    return ((max - min) < stabilityThreshold);
}

/**
 * Store readings from the axis
 * Updates the extreme reading (min/max) of the given Axis
 * Stores the incidental readings (Y, Z) at the time, for offset calculations
 */
void Mma7361Calibrator::storeReadings(int x, axisReadings *store)
{
    // Note: For the purposes of value tracking, we believe 0 to mean "not set".
    // So any entry with a "0" is not an actual value.

    // If the Average is not for the min, set it high
    // max will be 0, which is fine.
    if (store->min.average == 0) {
        store->min.average = 1023;
    }

    // Min
    if (store->min.average > x) {
        store->min.stack[store->min.current] = x;
        store->min.current++;
    }

    // Reset counters if overflowing
    if (store->min.current > store->min.size) {
        store->min.current = 0;

        // Update averages
        long xA = 0;
        for (int i=0; i < store->min.size; i++) {
            xA += store->min.stack[i];
        }

        // Make averages
        store->min.average = xA / store->min.size;
    }

    // Max
    if (store->max.average < x) {
        store->max.stack[store->max.current] = x;
        store->max.current++;
    }

    if (store->max.current > store->max.size) {
        store->max.current = 0;

        // Update averages
        long xB = 0;
        for (int i=0; i < store->max.size; i++) {
            xB += store->max.stack[i];
        }

        // Make average
        store->max.average = xB / store->max.size;
    }
}

/**
 * Get the calculated calibration values
 */
Mma7361Calibration Mma7361Calibrator::getCalibration()
{
    Mma7361Calibration calibration;

    // X
    calibration.xMin = readingsX.min.average;
    calibration.xMax = readingsX.max.average;

    // Y
    calibration.yMin = readingsY.min.average;
    calibration.yMax = readingsY.max.average;

    // Z
    calibration.zMin = readingsZ.min.average;
    calibration.zMax = readingsZ.max.average;

    return calibration;
}

/**
 * Get the extremes of the calibrated measurements
 */
Mma7361Calibration Mma7361Calibrator::getExtremes()
{
    Mma7361Calibration calibration;

    // X
    calibration.xMin = unstableX.min.average;
    calibration.xMax = unstableX.max.average;

    // Y
    calibration.yMin = unstableY.min.average;
    calibration.yMax = unstableY.max.average;

    // Z
    calibration.zMin = unstableZ.min.average;
    calibration.zMax = unstableZ.max.average;

    return calibration;
}