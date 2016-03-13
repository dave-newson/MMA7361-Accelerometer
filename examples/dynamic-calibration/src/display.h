#include "Mma7361Accelerometer.h"

/**
 * Clear the display by flushing some new lines
 */
void displayClear();

/**
 * Display how many cycles have been executed since last display
 * This lets us know how fast we can fill the arrays.
 */
void displayRate(int rate);

/**
 * Display the raw sensor values
 */
void displayRaw(int x, int y, int z);

/**
 * Display the acceleration vector and magnitude
 */
void displayGravityVector(Mma7361Accelerometer sensor);

/**
 * Display calibration for all axes
 */
void displayCalibratorValues(Mma7361Calibration calibration, Mma7361Calibration extremes);