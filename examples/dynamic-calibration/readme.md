# Dynamic Calibration

This library provides a calibration class which you can use to dynamically calibrate your MMA7361.

It's not recommended (or required) that you calibrate your device every time; you can instead take measurements from
one calibration session and use them statically with your device thereafter.

## Calibration Procedure

While calibration is running, you should carefully rotate the sensor through all sides, 
spending some time on each side to "wobble" the sensor and find its absolute zero point.

The calibrator measures the "stability" of the readings, in the hope to only capture values which represent stable
1g readings (gravity) rather than any acceleration or shock induced by operator handling.

The example calibrator also shows the "raw" extreme values, so if you over-G or under-G the accelerometer, you will know.

The calibrator uses a stack of averages to locate the extreme sensor values for the sensor at 1g.

In testing, minimum values were between 230-250, with maximum values between 710-780.

## Transferring to Static Calibration

Note the values from the Serial output under the `CALIBRATED` heading:
```
Rate: 1704

X=469, Y=463, Z=729
CALIBRATED
X: min=250 max=703
Y: min=284 max=785
Z: min=217 max=706
EXTREMES
X: min=228 max=740
Y: min=157 max=801
Z: min=174 max=880

VECTOR: X=-0.03, Y=-0.28, Z=1.10, G=1.13
```

These values can be used to configure the `MMA7361Calibration` struct with static calibration figures:

```
    calibration.xMin = 250;
    calibration.xMax = 703;
    calibration.yMin = 284;
    calibration.yMax = 785;
    calibration.zMin = 217;
    calibration.zMax = 706;
```

See the code under `static-calibration` as an example of how to use static calibration.

# Environment

These examples are intended to be used with the following environment

## Software
 - [PlatformIO](platformio.org) 
 - [CLion](https://www.jetbrains.com/clion/)

## Hardware
 - [Teensy 3.1](https://www.pjrc.com/teensy/teensy31.html) (Arduino derivative)

## Wiring
![Teensy 3.1 and MMA7361 Accelerometer](../../docs/wiring.png)

## Compiling
 - `platformio init`
 - `platformio run --target upload`