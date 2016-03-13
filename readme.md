# MMA7361 Accelerometer

A simple library for the MMA7361 3-axis accelerometer.
Includes a calibration library, to discover calibration settings for your specific MMA7361.

# Quick Start

This library exists because the MMA7361 requires some individual axis calibration.

 - Use [the dynamic-calibration example](examples/dynamic-calibration/) to obtain some calibration values for your MMA7361.
 - Once calibration values have been obtained, [see the static-calibration example](examples/static-calibration).

# Calibration

``` cpp
Mma7361Calibrator calibrator;
Mma7361Calibration calibration;

loop()
{
    // Read
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    int z = analogRead(zPin);

    // Calibrate
    calibrator.calibrate(x, y, z);
    
    // Get calibration
    calibration = calibrator.getCalibration();
    
    // Display
    Serial.println("");
    Serial.print("Xmin=");
    Serial.print(calibration.xMin);
    Serial.print("Xmax=");
    Serial.print(calibration.xMax);
    // etc ..
}
```

While calibrating, slowly rotate the accelerometer through all orientations continuously, until values stabilise.

# Usage

Once calibration values have been obtained, set those values statically for use with the sensor:
``` cpp
Mma7361Calibration calibration;
calibration.xMin = 234;
calibration.xMax = 727;
calibration.yMin = 283;
calibration.yMax = 782;
calibration.zMin = 218;
calibration.zMax = 704;
```
 
You can then configure the MMA7361 class:
``` cpp
Mma7361 sensor;
sensor.calibrate(calibration);
```

Finally, you can take some measurements:
``` cpp
sensor.update(x, y, z);

// Get the G Force
double gForce = sensor.getGForce(); 

// Get the force vector
ForceVector vector = sensor.getForceVector();
```

Each value is given in G.

All values are cached between calls to `update`, so expensive calculations (like the gForce magnitude) are not repeated.

# About the MMA7361

As seen on
 - [Sparkfun](https://www.sparkfun.com/products/retired/9652)
 - [ElectroSchematics](http://www.electroschematics.com/10467/learn-use-mma7361/)
 
DataSheet: [http://pdf1.alldatasheet.com/datasheet-pdf/view/246143/FREESCALE/MMA7361L.html]

The MMA7361 is a simple 3-axis accelerometer, which can measure in the range of either 1.5g or 6g.
It uses voltage in the range of 0v to 3.3v, to indicate the accelerometer measurements.

## MMA7361 Measurement Variance

The data sheet for the MMA7361 says that, when in 1.5g mode, it provides the g-force for each axis
with a sensitivity of between 740mV and 860mV per G, with an ideal target of 800mV for 1g.

This gives a variance of 120mv at source; roughly a variance of 10% for the signal.

Arduino boards which incorporate the MMA7361 raise this voltage into the 3.3v range, 
so it can be easily measured using analogRead.

In testing this, the variance on a single axis is much lower than 10% (ie. it performs much better than claimed),
however between the 3 axis on the device, they each provide different levels of readings, so they are not 
directly comparable.  In effect, the values for 1g on the X axis are not the same as on the Y or Z axis.
 
Due to this variance between the axis, some calibration is required.

## Dynamic Calibration

The process of dynamic calibration requires you to slowly are carefully rotate your sensor through all the major axis
and sides of the device.  

It's not recommended to use this method every time; but instead perform it once in order
to obtain a set of values specific to your MMA7361.

## Post-calibration Variance

The calibration brings all axis into sync with each other, 
providing a much more accurate reading of axis acceleration and magnitude.

However, this library makes no attempt to stabilise the variance of the measurements taken from the sensor, 
so you must apply your own "smoothing" between individual readings.

# Other libraries

If this library doesn't float your boat, there are several other implementations for the MMA7361:
 
 - https://github.com/jeroendoggen/Arduino-MMA7361-library
 - https://github.com/IndianTinker/MMA7361Library
 - https://gist.github.com/nataliefreed/7815633
