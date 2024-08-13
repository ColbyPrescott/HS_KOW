#include "Backend/absolutePositioningSystem.h"

#include "vex.h"
#include "Backend/utilityMath.h"

// Update the absolute position
void AbsolutePositioningSystem::TickTracking() {
    // Find average travel distance
    double leftMotorPosition = mLeftDrivetrainMotors->position(vex::degrees);
    double rightMotorPosition = mRightDrivetrainMotors->position(vex::degrees);
    
    double leftMotorTravel = (leftMotorPosition - mPrevLeftDrivetrainMotorPosition) * mDegreesToInchesRatio;
    double rightMotorTravel = (rightMotorPosition - mPrevRightDrivetrainMotorPosition) * mDegreesToInchesRatio;

    double averageTravel = (leftMotorTravel + rightMotorTravel) / 2.0;

    // Add travel to absolute coordinate
    mX += cos(mPrevInertialSensorAngle) * averageTravel;
    mY += sin(mPrevInertialSensorAngle) * averageTravel;
    mRotation = mInertialSensors->GetRotation();
    
    // Update previous tick values
    mPrevLeftDrivetrainMotorPosition = leftMotorPosition;
    mPrevRightDrivetrainMotorPosition = rightMotorPosition;
    mPrevInertialSensorAngle = mInertialSensors->GetRotation();
}

// Update the wheel velocities
void AbsolutePositioningSystem::TickDriving() {
    // Don't continue if no path points are buffered
    if(mPath.empty()) return;

    // Get a copy of the point to drive to
    PathPoint targetPoint = mPath.front();
    // Transform to local position
    targetPoint.x -= GetX();
    targetPoint.y -= GetY();
    // Transform to local rotation
    PathPoint tmpPoint = targetPoint;
    targetPoint.x = tmpPoint.x * cos(-GetRotation()) - tmpPoint.y * sin(-GetRotation());
    targetPoint.y = tmpPoint.x * sin(-GetRotation()) + tmpPoint.y * cos(-GetRotation());

    // Calculate how fast to drive towards targetPoint
    // Get distance to target
    double forwardInput = targetPoint.x;
    // 10 inches away is max speed
    forwardInput /= 10.0;
    // DEBUG Don't drive too fast
    forwardInput = Clamp(forwardInput, -0.3, 0.3);

    // Calculate how fast to turn towards targetPoint
    // Get direction to target
    double targetHeading = -atan2(targetPoint.y, targetPoint.x);
    // Aim to be driving backwards if turning more than 90 degrees
    if(targetHeading > M_2_PI || targetHeading < -M_2_PI) targetHeading = M_PI - fabs(targetHeading);
    // Convert to speed
    double rightwardInput = targetHeading;
    rightwardInput /= M_2_PI; // Max turning is 90 degrees away
    // Don't turn too much if position is super close
    if(targetPoint.x * targetPoint.x + targetPoint.y * targetPoint.y < 2 * 2) rightwardInput = Clamp(rightwardInput, -0.1, 0.1);
    // DEBUG Don't turn too fast
    rightwardInput = Clamp(rightwardInput, -0.3, 0.3);
    

    // Increase / decrease voltage of one side to help correct drifting caused by drivetrain friction or center of mass
    double rightWheelsVoltageBias = forwardInput >= 0 ? -0.03 : 0.03; // TODO This runs even if there's no input, causing the right side to lock up when controls stop

    // Set motor velocities
    leftWheels.spin(vex::forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), vex::volt);
    rightWheels.spin(vex::forward, fmin(fmax((forwardInput - rightwardInput + rightWheelsVoltageBias) * 12, -12), 12), vex::volt);

    // if(rand() % 50 == 0) printf("TX: %.1f, TY: %.1f, X: %.1f, Y: %.1f, F: %.2f, R: %.2f\n", targetPoint.x, targetPoint.y, GetX(), GetY(), forwardInput, rightwardInput);

    if(targetPoint.x * targetPoint.x + targetPoint.y * targetPoint.y < 5 * 5) mPath.erase(mPath.begin());
}

// Manually set the absolute position in inches
void AbsolutePositioningSystem::SetPosition(double x, double y) {
    mX = x;
    mY = y;
}

// Manually set the absolute angle in radians
void AbsolutePositioningSystem::SetRotation(double rotation) {
    mRotation = rotation;
}



// Get the absolute X coordinate in inches
double AbsolutePositioningSystem::GetX() {
    return mX;
}

// Get the absolute Y coordinate in inches
double AbsolutePositioningSystem::GetY() {
    return mY;
}

// Get the absolute angle in radians
double AbsolutePositioningSystem::GetRotation() {
    return mRotation;
}







// Set whether or not the APS is allowed to control the drivetrain
void AbsolutePositioningSystem::SetDriving(bool driving) {
    mDrivingEnabled = driving;
}

// Add a point to the drive path
void AbsolutePositioningSystem::AddPathPoint(PathPoint pathPoint) {
    mPath.push_back(pathPoint);
}

// DEBUG
void AbsolutePositioningSystem::NextPathPoint() {
    mPath.erase(mPath.begin());
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
void AbsolutePositioningSystem::StartTicking(double refreshRate) {
    singleInstanceRefreshRate = refreshRate;
    singleInstanceAPS = this;
    vex::task trackingLoop = vex::task(SingleInstanceTrackingLoop);
}





// Single tick to update absolute position and drivetrain velocities
void AbsolutePositioningSystem::Tick() {
    TickTracking();
    if(mDrivingEnabled) TickDriving();
}