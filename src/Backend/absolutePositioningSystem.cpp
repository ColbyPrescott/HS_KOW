#include "Backend/absolutePositioningSystem.h"

#include "vex.h"
#include "Backend/utilityMath.h"

#pragma region PathSection functions

// Get the X coordinate of a point along the curve at fractional time t
double PathSection::GetX(double t) {
    double q0x = Lerp(p0x, p1x, t);
    double q1x = Lerp(p1x, p2x, t);
    double q2x = Lerp(p2x, p3x, t);

    double r0x = Lerp(q0x, q1x, t);
    double r1x = Lerp(q1x, q2x, t);

    return Lerp(r0x, r1x, t);
}

// Get the Y coordinate of a point along the curve at fractional time t
double PathSection::GetY(double t) {
    double q0y = Lerp(p0y, p1y, t);
    double q1y = Lerp(p1y, p2y, t);
    double q2y = Lerp(p2y, p3y, t);

    double r0y = Lerp(q0y, q1y, t);
    double r1y = Lerp(q1y, q2y, t);

    return Lerp(r0y, r1y, t);
}

#pragma endregion

#pragma region Main tick functions

// Update the absolute position
void AbsolutePositioningSystem::TickTracking() {
    // Calculate forwards travel from the drivetrain encoders
    double leftMotorPosition = mLeftDrivetrainMotors->position(vex::degrees);
    double rightMotorPosition = mRightDrivetrainMotors->position(vex::degrees);
    
    double leftMotorTravel = (leftMotorPosition - mPrevLeftDrivetrainMotorPosition) * mDrivetrainDegreesToInchesRatio;
    double rightMotorTravel = (rightMotorPosition - mPrevRightDrivetrainMotorPosition) * mDrivetrainDegreesToInchesRatio;
    
    double forwardTravel = (leftMotorTravel + rightMotorTravel) / 2.0;


    // Calculate rightward travel from the unpowered wheel
    double unpoweredWheelRotation = mUnpoweredWheel->rotation(vex::degrees);

    double inertialSensorsRotation = mInertialSensors->GetRotation();
    double inertialSensorsDifference = (inertialSensorsRotation - mPrevInertialSensorsRotation);
    double unpoweredWheelExpectedRotation = inertialSensorsDifference * mUnpoweredWheelRobot360ToDegreesRatio;

    double rightwardTravel = (unpoweredWheelRotation - mPrevUnpoweredWheelRotation - unpoweredWheelExpectedRotation) * mUnpoweredWheelDegreesToInchesRatio;


    // Use calculated travel to update internal tracked coordinate
    mX += cos(mPrevInertialSensorsRotation) * forwardTravel;
    mY += sin(mPrevInertialSensorsRotation) * forwardTravel;

    mX += sin(mPrevInertialSensorsRotation) * rightwardTravel;
    mY -= cos(mPrevInertialSensorsRotation) * rightwardTravel;

    mRotation = mInertialSensors->GetRotation();

    
    // Update previous tick values
    mPrevLeftDrivetrainMotorPosition = leftMotorPosition;
    mPrevRightDrivetrainMotorPosition = rightMotorPosition;
    mPrevUnpoweredWheelRotation = unpoweredWheelRotation;
    mPrevInertialSensorsRotation = inertialSensorsRotation;


    // // Make sure the GPS is providing accurate data
    // if(mGPSSensor->quality() != 100) mEnableGPS = true;
    // // If GPS can see the strips, override the drivetrain data
    // if(!mEnableGPS || mGPSSensor->quality() != 100) return;
    // mX = mGPSSensor->xPosition(vex::inches) + 24 * 3;
    // mY = mGPSSensor->yPosition(vex::inches) + 24 * 3;
}

// Update the wheel velocities
void AbsolutePositioningSystem::TickDriving() {
    // Don't continue if no PathSections are buffered
    if(mPath.empty()) return;

    // Start reading the next PathSection if at the end of the current one
    if(mPathSectionProgress >= 1 && mPath.size() >= 2) {
        mPath.erase(mPath.begin());
        mPathSectionProgress = 0;
    }

    // Get the current PathSection to drive along
    PathSection targetPathSection = mPath.front();

    // Move mPathSectionProgress as far along the path that's within a distance
    const double lookaheadInches = 12;
    while(pow(GetX() - targetPathSection.GetX(mPathSectionProgress), 2) + pow(GetY() - targetPathSection.GetY(mPathSectionProgress), 2) < pow(lookaheadInches, 2) && mPathSectionProgress < 1) {
        mPathSectionProgress += 0.01;
    }

    // Test if the end of the buffered path has been reached already
    const double endInches = 2;
    if(mPath.size() == 1 && lookaheadInches >= 1 && pow(GetX() - targetPathSection.GetX(mPathSectionProgress), 2) + pow(GetY() - targetPathSection.GetY(mPathSectionProgress), 2) < pow(endInches, 2)) {
        mPath.erase(mPath.begin());
        mPathSectionProgress = 0;

        mLeftDrivetrainMotors->stop();
        mRightDrivetrainMotors->stop();

        return;
    }

    // Get the point to drive towards
    double targetX = targetPathSection.GetX(mPathSectionProgress);
    double targetY = targetPathSection.GetY(mPathSectionProgress);

    // Transform to local position
    targetX -= GetX();
    targetY -= GetY();
    // Transform to local rotation
    double tmpX = targetX;
    double tmpY = targetY;
    targetX = tmpX * cos(-GetRotation()) - tmpY * sin(-GetRotation());
    targetY = tmpX * sin(-GetRotation()) + tmpY * cos(-GetRotation());


    // Calculate how fast to drive towards target point
    double targetSpeed = Lerp(targetPathSection.startSpeed, targetPathSection.endSpeed, mPathSectionProgress) / 100;
    double forwardInput = targetSpeed;

    // Calculate how fast to turn towards target point
    // Get direction to target
    double targetHeading = -atan2(targetY, targetX);
    // Flip target heading 180 degrees if driving backwards
    if(targetSpeed < 0) targetHeading = atan2(targetY, -targetX);
    // Convert to speed
    double rightwardInput = targetHeading;
    // Max turning is 90 degrees away TODO Calibrate
    rightwardInput /= M_2_PI; 
    // Don't turn too much if position is super close TODO Calibrate
    if(targetX * targetX + targetY * targetY < 2 * 2) rightwardInput = Clamp(rightwardInput, -0.1, 0.1);
    

    // Increase / decrease voltage of one side to help correct drifting caused by drivetrain friction or center of mass
    double signedRightWheelsVoltageBias = forwardInput >= 0 ? -rightWheelsVoltageBias : rightWheelsVoltageBias; // TODO This runs even if there's no input, causing the right side to lock up when controls stop

    // Set motor velocities
    leftWheels.spin(vex::forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), vex::volt);
    rightWheels.spin(vex::forward, fmin(fmax((forwardInput - rightwardInput + signedRightWheelsVoltageBias) * 12, -12), 12), vex::volt);
}

#pragma endregion

#pragma region Tracking setters and getters

// Manually set the absolute position in inches
void AbsolutePositioningSystem::SetPosition(double x, double y) {
    // Mirror if enabled
    if(mMirrorPath) x = MirrorX(x);

    // Set internal position
    mX = x;
    mY = y;

    // Set sensor position
    mGPSSensor->setLocation(x, y, vex::inches, (-mRotation / M_PI * 180) + 90);
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

// Add a section to the drive path
void AbsolutePositioningSystem::AddPathSection(PathSection pathSection) {
    // Mirror if enabled
    if(mMirrorPath) {
        pathSection.p0x = MirrorX(pathSection.p0x);
        pathSection.p1x = MirrorX(pathSection.p1x);
        pathSection.p2x = MirrorX(pathSection.p2x);
        pathSection.p3x = MirrorX(pathSection.p3x);
    }

    // Add pathSection to the buffered path
    mPath.push_back(pathSection);
}

// Add a section to the drive path
void AbsolutePositioningSystem::AddPathSection(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double startSpeed, double endSpeed) {
    AddPathSection(PathSection(p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y, startSpeed, endSpeed));
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