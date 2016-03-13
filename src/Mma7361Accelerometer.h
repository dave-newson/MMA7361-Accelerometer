#ifndef MMA7361_ACC_H
#define MMA7361_ACC_H

/**
 * Populate with calibration data for the MMA7361 sensor
 */
struct Mma7361Calibration
{
    // X
    int xMin;
    int xMax;

    // Y
    int yMin;
    int yMax;

    // Z
    int zMin;
    int zMax;
};

/**
 * Vector representing the gravity forces
 * 1.f = 1g.
 */
struct ForceVector {
    float x;
    float y;
    float z;
};

/**
 * MMA7361 Accelerometer
 * Uses caching and lazy-calculations, to avoid unnecessary processing.
 */
class Mma7361Accelerometer {

public:

    /**
     * Set the calibration values of the sensor
     */
    void calibrate(Mma7361Calibration calibration);

    /**
     * Update voltage readings for the sensor
     */
    void update(int x, int y, int z);

    /**
     * Get the force vector
     */
    ForceVector getForceVector();

    /**
     * Get the GForce
     * This is the magnitude of the Force Vector.
     */
    double getGForce();

protected:

    /**
     * Calibration settings
     */
    Mma7361Calibration calibration;

    /**
     * Raw input vector, in 0-1023 analog read
     */
    ForceVector rawVector;

    /**
     * True when the vector has not yet been calculated since last update
     */
    bool vectorStale = true;

    /**
     * Cached force vector
     */
    ForceVector vector;

    /**
     * True when the magnitude has not yet been calculated since last update
     */
    bool magnitudeStale = true;

    /**
     * Cached magnitude calculation
     */
    double magnitude;

};

#endif //MMA7361_ACC_H
