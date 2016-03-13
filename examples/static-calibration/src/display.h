#include "Mma7361Accelerometer.h"

/**
 * Clear the display by flushing some new lines
 */
void displayClear();

/**
 * Display the raw sensor values
 */
void displayRaw(int x, int y, int z);

/**
 * Display the gravity vector
 */
void displayGravityVector(Mma7361Accelerometer sensor);

/**
 * Display some human-friendly feedback
 */
void displayObservations(Mma7361Accelerometer sensor);