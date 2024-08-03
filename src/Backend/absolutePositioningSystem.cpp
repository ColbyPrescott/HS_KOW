#include "Backend/absolutePositioningSystem.h"

#include "vex.h"

// Manually set the absolute position in inches
void AbsolutePositioningSystem::SetPosition(double x, double y) {
    mX = x;
    mY = y;
}

// Manually set the absolute angle in degrees
void AbsolutePositioningSystem::SetAngle(double angle) {
    mAngle = angle;
}



// Get the absolute X coordinate in inches
double AbsolutePositioningSystem::GetX() {
    return mX;
}

// Get the absolute Y coordinate in inches
double AbsolutePositioningSystem::GetY() {
    return mY;
}

// Get the absolute angle in degrees
double AbsolutePositioningSystem::GetAngle() {
    return mAngle;
}



// Assuming only one APS is running, create a global task function to call Tick() on a specific APS
namespace {
    double singleInstanceRefreshRate;
    AbsolutePositioningSystem* singleInstanceAPS;

    int SingleInstanceTrackingLoop() {
        while(true) {
            singleInstanceAPS->Tick();
            vex::this_thread::sleep_for(1000.0 / singleInstanceRefreshRate);
        }
    }
}

// Start tracking the absolute position with an optional specific refresh rate
void AbsolutePositioningSystem::StartTracking(double refreshRate) {
    singleInstanceRefreshRate = refreshRate;
    singleInstanceAPS = this;
    vex::task trackingLoop = vex::task(SingleInstanceTrackingLoop);
}



// Single tick to update absolute position
void AbsolutePositioningSystem::Tick() {
    // Find average travel distance
    double leftMotorPosition = mLeftDrivetrainMotor->position(vex::degrees);
    double rightMotorPosition = mRightDrivetrainMotor->position(vex::degrees);
    
    double leftMotorTravel = leftMotorPosition - mPrevLeftDrivetrainMotorPosition;
    double rightMotorTravel = rightMotorPosition - mPrevRightDrivetrainMotorPosition;

    double averageTravel = (leftMotorTravel + rightMotorTravel) / 2.0;

    // Add travel to absolute coordinate
    mX += cos(mPrevInertialSensorAngle * M_PI / 180.0) * averageTravel;
    mY += sin(mPrevInertialSensorAngle * M_PI / 180.0) * averageTravel;
    
    // Update previous tick values
    mPrevLeftDrivetrainMotorPosition = leftMotorPosition;
    mPrevRightDrivetrainMotorPosition = rightMotorPosition;
    mPrevInertialSensorAngle = mInertialSensor->rotation();
}