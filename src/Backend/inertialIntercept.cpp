#include "Backend/inertialIntercept.h"

#include "Backend/utilityMath.h"

// Calibrate the sensor. Do not move for about 2 seconds or calibration will fail
void InertialIntercept::Calibrate() {
    vex::inertial::calibrate();
}



// Set the rotation of the inertial sensor in radians
void InertialIntercept::SetRotation(double rotation) {
    vex::inertial::setRotation(RadiansToDegrees(rotation), vex::degrees);
}



// Get the corrected rotation of the inertial sensor in radians
double InertialIntercept::GetRotation() {
    return DegreesToRadians(vex::inertial::rotation() * mBias);
}

// Get the corrected rotation of the inertial sensor within 0 to 2pi radians
double InertialIntercept::GetHeading() {
    return FixedFMod(GetRotation(), M_PI * 2.0);
}

// Get whether or not the inertial sensor is plugged in
bool InertialIntercept::GetInstalled() {
    return vex::inertial::installed();
}

// Get whether or not the inertial sensor is currently calibrating
bool InertialIntercept::GetCalibrating() {
    return vex::inertial::isCalibrating();
}

// Get the temperature of the inertial sensor in degrees celsius
double InertialIntercept::GetTemperature() {
    return vex::inertial::temperature();
}