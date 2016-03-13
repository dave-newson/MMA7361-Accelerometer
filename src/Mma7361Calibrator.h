#ifndef MMA7361_CAL_H
#define MMA7361_CAL_H

#include "Mma7361Accelerometer.h"

/**
 * Struct for recording values as a stack
 */
struct valueStack {
    const static int size = 200;
    int current = 0;
    int stack[valueStack::size];
};

/**
 * Stores the Axis Values as a stack
 * Includes an "average" reading, which includes averages from all update cycles.
 */
struct axisValueStack : valueStack {
    int average;
};

/**
 * Stores min/max value stacks for the axis.
 * It's assumed that min/max values are only read during moments of stability.
 */
struct axisReadings {
    axisValueStack min;
    axisValueStack max;
};

/**
 * Stability tracker is a stack of recorded values over the last ::max period.
 * Each tick we check the stability of the readings overall min/max values
 * and ensure they fall within a threshold limit.
 * This threshold is used
 */
struct stabilityTracker : valueStack {
    // Set to true after enough values are present for stability to be checked
    bool enabled = false;
};

/**
 * Calibration class
 */
class Mma7361Calibrator
{

public:

    /**
     * Run single calibration cycle
     */
    void calibrate(int x, int y, int z);

    /**
     * Get the calculated calibration struct
     */
    Mma7361Calibration getCalibration();

    /**
     * Get the extremes measured by the calibrator
     * Handy for checking if we've over/under-g'd the sensor.
     */
    Mma7361Calibration getExtremes();

private:

    /**
     * Threshold by which the tracked values can vary, and still be considered "stable".
     * This is the variance in voltage we're happy to accept before making a recording.
     * Setting this too high may result in over/under-G values being recorded.
     */
    const int stabilityThreshold = 10;

    /**
     * One stability tracker per axis.
     * Stable readings are only taken when the stabilityTracker has stable history.
     */
    stabilityTracker stableX;
    stabilityTracker stableY;
    stabilityTracker stableZ;

    /**
     * Stable readings
     * Readings are only taken when the stability tracker says we have stability.
     */
    axisReadings readingsX;
    axisReadings readingsY;
    axisReadings readingsZ;

    /**
     * Unstable readings
     * Always updated, regardless of the stability tracker.
     */
    axisReadings unstableX;
    axisReadings unstableY;
    axisReadings unstableZ;

    /**
     * Add X to the given stabilityTracker
     * Returns true if the given tracker has stable values.
     */
    bool isStable(int x, stabilityTracker *tracker);

    /**
     * Store X to axisReadings if > max or < min.
     * Store incidental values for Y and Z when X is recorded.
     */
    void storeReadings(int x, axisReadings *store);

};

#endif //MMA7361_CAL_H
