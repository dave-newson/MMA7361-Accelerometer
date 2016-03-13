#include "display.h"
#include "Arduino.h"

void displayClear()
{
    for (int i=0; i<5; i++) {
        Serial.println("");
    }
}

void displayRaw(int x, int y, int z)
{
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

void displayObservations(Mma7361Accelerometer sensor)
{
    double gForce = sensor.getGForce();
    ForceVector vector = sensor.getForceVector();

    Serial.println("");
    Serial.println("");
    Serial.print("I am ");

    if (gForce < 0.15) {
        Serial.print("in Free-fall!!");
    } else if (gForce < 0.5) {
        Serial.print("Falling!");
    } else if (vector.x > 0.8) {
        Serial.print("on my Right side");
    } else if (vector.x < -0.8) {
        Serial.print("on my Left side");
    } else if (vector.y > 0.8) {
        Serial.print("on my Front");
    } else if (vector.y < -0.8) {
        Serial.print("on my Back");
    } else if (vector.z > 0.8) {
        Serial.print("Sunny-side up :)");
    } else if (vector.z < -0.8) {
        Serial.print("Upside Down :(");
    } else {
        Serial.print("");
    }

    Serial.println("");
}
