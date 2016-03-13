#include "display.h"
#include "Arduino.h"

void displayClear()
{
    for (int i=0; i<10; i++) {
        Serial.println("");
    }
}

void displayRate(int rate)
{
    Serial.println("");
    Serial.print("Rate: ");
    Serial.print(rate);
}

void displayRaw(int x, int y, int z)
{
    Serial.println("");
    Serial.println("");
    Serial.print("X=");
    Serial.print(x);
    Serial.print(", Y=");
    Serial.print(y);
    Serial.print(", Z=");
    Serial.print(z);
}

void displayGravityVector(Mma7361Accelerometer sensor)
{
    ForceVector vector = sensor.getForceVector();

    // Display single axis vectors
    Serial.println("");
    Serial.println("");
    Serial.print("VECTOR: X=");
    Serial.print(vector.x);
    Serial.print(", Y=");
    Serial.print(vector.y);
    Serial.print(", Z=");
    Serial.print(vector.z);

    // Display calculated magnitude from vector.
    // We expect, at idle and any angle, this displays "1", for 1g.
    Serial.print(", G=");
    Serial.print(sensor.getGForce());
}

void displayCalibratorValues(Mma7361Calibration calibration, Mma7361Calibration extremes)
{
    // Calibrated Axis
    Serial.println("");
    Serial.println("CALIBRATED");

    Serial.print("X: ");
    Serial.print("min=");
    Serial.print(calibration.xMin);
    Serial.print(" max=");
    Serial.print(calibration.xMax);

    Serial.println();
    Serial.print("Y: ");
    Serial.print("min=");
    Serial.print(calibration.yMin);
    Serial.print(" max=");
    Serial.print(calibration.yMax);

    Serial.println();
    Serial.print("Z: ");
    Serial.print("min=");
    Serial.print(calibration.zMin);
    Serial.print(" max=");
    Serial.print(calibration.zMax);

    // Extremes
    Serial.println("");
    Serial.println("EXTREMES");

    Serial.print("X: ");
    Serial.print("min=");
    Serial.print(extremes.xMin);
    Serial.print(" max=");
    Serial.print(extremes.xMax);

    Serial.println();
    Serial.print("Y: ");
    Serial.print("min=");
    Serial.print(extremes.yMin);
    Serial.print(" max=");
    Serial.print(extremes.yMax);

    Serial.println();
    Serial.print("Z: ");
    Serial.print("min=");
    Serial.print(extremes.zMin);
    Serial.print(" max=");
    Serial.print(extremes.zMax);
}