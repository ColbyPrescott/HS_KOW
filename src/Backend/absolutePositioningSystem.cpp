#include "Backend/absolutePositioningSystem.h"

#include "vex.h"
#include "Backend/utilityMath.h"

#pragma region Main tick functions

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
    static bool doneDrivingToTarget = false;
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

    // Logic figuring out the current driving stage
    // Update static doneDrivingToTarget if within distance threshold
    if(targetPoint.x * targetPoint.x + targetPoint.y * targetPoint.y < targetPoint.distanceThreshold * targetPoint.distanceThreshold) doneDrivingToTarget = true;
    // Determing if the robot should now be turning to face a specific heading
    bool rotatingToHeading = doneDrivingToTarget && targetPoint.targetHeading != PathPoint::noTargetHeading && fabs(DifferenceBetweenHeadings(targetPoint.targetHeading, GetRotation())) > DegreesToRadians(10.0);
    // Jump to next path point if there is nothing left to do for this one
    if(doneDrivingToTarget && !rotatingToHeading) {
        // Move to next path point
        mPath.erase(mPath.begin());
        doneDrivingToTarget = false;

        // Stop wheels if the end of the buffered path was reached
        if(mPath.empty()) {
            leftWheels.stop();
            rightWheels.stop();
        }

        // Skip rest of function to recalculate targetPoint
        return;
    }


    double forwardInput;
    double rightwardInput;
    if(!rotatingToHeading) {
        // Calculate how fast to drive towards targetPoint
        // Get distance to target
        forwardInput = targetPoint.x;
        // 10 inches away is max speed TODO Calibrate
        forwardInput /= 10.0;
        // Clamp forward input depending on path point settings
        forwardInput = Clamp(forwardInput, -targetPoint.maxDriveSpeed, targetPoint.maxDriveSpeed);

        // Calculate how fast to turn towards targetPoint
        // Get direction to target
        double targetHeading = -atan2(targetPoint.y, targetPoint.x);
        // Flip target heading 180 degrees if driving backwards
        if(targetPoint.driveBackwards) targetHeading = atan2(targetPoint.y, -targetPoint.x);
        // Convert to speed
        rightwardInput = targetHeading;
        // Max turning is 90 degrees away TODO Calibrate
        rightwardInput /= M_2_PI; 
        // Don't turn too much if position is super close TODO Calibrate
        if(targetPoint.x * targetPoint.x + targetPoint.y * targetPoint.y < 2 * 2) rightwardInput = Clamp(rightwardInput, -0.1, 0.1);
        // Clamp turning input depending on path point settings
        rightwardInput = Clamp(rightwardInput, -targetPoint.maxTurnSpeed, targetPoint.maxTurnSpeed);
    } else {
        // Don't drive, just turn in place
        forwardInput = 0;

        // Convert direction and distance to target heading to speed
        rightwardInput = DifferenceBetweenHeadings(targetPoint.targetHeading, GetRotation());
        // Max turning is 90 degrees away TODO Calibrate
        rightwardInput /= DegreesToRadians(30);
        // Clamp turning input to stop sliding TODO Calibrate
        rightwardInput = Clamp(rightwardInput, -0.3, 0.3);
    }
    

    // Increase / decrease voltage of one side to help correct drifting caused by drivetrain friction or center of mass
    double rightWheelsVoltageBias = forwardInput >= 0 ? -0.025 : 0.025; // TODO This runs even if there's no input, causing the right side to lock up when controls stop

    // Set motor velocities
    leftWheels.spin(vex::forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), vex::volt);
    rightWheels.spin(vex::forward, fmin(fmax((forwardInput - rightwardInput + rightWheelsVoltageBias) * 12, -12), 12), vex::volt);
}

#pragma endregion

#pragma region Tracking setters and getters

// Manually set the absolute position in inches
void AbsolutePositioningSystem::SetPosition(double x, double y) {
    // Mirror if enabled
    if(mMirrorPath) x = MirrorX(x);

    mX = x;
    mY = y;
}

// Manually set the absolute angle in radians
void AbsolutePositioningSystem::SetRotation(double rotation) {
    // Mirror if enabled
    if(mMirrorPath) rotation = MirrorHeading(rotation);
    
    mRotation = rotation;
    mInertialSensors->SetRotation(rotation);
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

#pragma endregion

#pragma region Driving setters, getters, and other functions

// Set whether or not the APS is allowed to control the drivetrain
void AbsolutePositioningSystem::SetDriving(bool driving) {
    mDrivingEnabled = driving;
}

// Set whether or not coordinates and angles are flipped to the opposite side of the field
void AbsolutePositioningSystem::SetMirrored(bool mirrored) {
    mMirrorPath = mirrored;
}

// Add a point to the drive path
void AbsolutePositioningSystem::AddPathPoint(PathPoint pathPoint) {
    // Mirror if enabled
    if(mMirrorPath) {
        pathPoint.x = MirrorX(pathPoint.x);
        if(pathPoint.targetHeading != PathPoint::noTargetHeading) pathPoint.targetHeading = MirrorHeading(pathPoint.targetHeading);
    }

    // Add pathPoint to the buffered path
    mPath.push_back(pathPoint);
}

// Add a point to the drive path
void AbsolutePositioningSystem::AddPathPoint(double xInches, double yInches, bool driveBackwards, double maxDriveSpeed, double maxTurnSpeed, double distanceThreshold, double targetHeading) {
    AddPathPoint(PathPoint(xInches, yInches, driveBackwards, maxDriveSpeed, maxTurnSpeed, distanceThreshold, targetHeading));
}

// Wait until the buffered path has been driven
void AbsolutePositioningSystem::EndPath() {
    while(!mPath.empty()) wait(50, vex::msec);
}

#pragma endregion

#pragma region Ticking setup

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

#pragma endregion