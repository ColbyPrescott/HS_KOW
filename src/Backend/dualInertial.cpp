#include "Backend/dualInertial.h"

#include <math.h>
#include "Backend/utilityMath.h"

// Calibrate both of the inertial sensors
void DualInertial::Calibrate() {
    mInertialA.calibrate();
    mInertialB.calibrate();
}

// Get the average absolute yaw angle of both inertial sensors in radians
double DualInertial::GetRotation() {
    // Get the rotation values in radians
    double inertialARotation = DegreesToRadians(mInertialA.rotation(vex::degrees));
    double inertialBRotation = DegreesToRadians(mInertialB.rotation(vex::degrees));

    // Apply biases from the 18000 degree tests
    inertialARotation *= mBiasA;
    inertialBRotation *= mBiasB;

    // Return one if the other inertial sensor is not installed
    if(!mInertialA.installed()) return inertialBRotation;
    if(!mInertialB.installed()) return inertialARotation;

    // Return the average between the two inertial sensors
    return (inertialARotation + inertialBRotation) / 2.0;
}

// Get the rotation within 0 to 2pi radians
double DualInertial::GetHeading() {
    return FixedFMod(GetRotation(), M_PI * 2.0);
}

// Get whether or not one of the inertial sensors is still calibrating
bool DualInertial::GetCalibrating() {
    return mInertialA.isCalibrating() || mInertialB.isCalibrating();
}

// Get the average temperature of both inertial sensors
double DualInertial::GetTemperature() {
    // Get the temperature of each sensor
    double inertialATemp = mInertialA.GetTemperature();
    double inertialBTemp = mInertialB.GetTemperature();

    // Return one if the other inertial sensor is not installed
    if(!mInertialA.installed()) return inertialBTemp;
    if(!mInertialB.installed()) return inertialATemp;

    // Return the average between the two inertial sensors
    return (inertialATemp + inertialBTemp) / 2.0;
}