#include "Backend/dualInertial.h"

#include "Backend/utilityMath.h"

// Calibrate both of the inertial sensors
void DualInertial::Calibrate() {
    mInertialA.Calibrate();
    mInertialB.Calibrate();
}

// Get the average absolute yaw angle of both inertial sensors in radians
double DualInertial::GetRotation() {
    // Get the rotation values in radians
    double inertialARotation = mInertialA.GetRotation();
    double inertialBRotation = mInertialB.GetRotation();

    // Return one if the other inertial sensor is not installed
    if(!mInertialA.GetInstalled()) return inertialBRotation;
    if(!mInertialB.GetInstalled()) return inertialARotation;

    // Return the average between the two inertial sensors
    return (inertialARotation + inertialBRotation) / 2.0;
}

// Get the rotation within 0 to 2pi radians
double DualInertial::GetHeading() {
    return FixedFMod(GetRotation(), M_PI * 2.0);
}

// Get whether or not one of the inertial sensors is still calibrating
bool DualInertial::GetCalibrating() {
    return mInertialA.GetCalibrating() || mInertialB.GetCalibrating();
}

// Get the average temperature of both inertial sensors
double DualInertial::GetTemperature() {
    // Get the temperature of each sensor
    double inertialATemp = mInertialA.GetTemperature();
    double inertialBTemp = mInertialB.GetTemperature();

    // Return one if the other inertial sensor is not installed
    if(!mInertialA.GetInstalled()) return inertialBTemp;
    if(!mInertialB.GetInstalled()) return inertialATemp;

    // Return the average between the two inertial sensors
    return (inertialATemp + inertialBTemp) / 2.0;
}