#ifndef ABSOLUTE_POSITIONING_SYSTEM_H
#define ABSOLUTE_POSITIONING_SYSTEM_H

#include "v5.h"
#include "v5_vcs.h"

#include "Backend/dualInertial.h"

#include <vector>

struct PathPoint {
    // X coordinate in inches
    double x;
    // Y coordinate in inches
    double y;
    // Whether or not to drive backwards towards the point
    bool driveBackwards;
    // Maximum forwards input allowed
    double maxDriveSpeed;
    // Maximum turning input allowed
    double maxTurnSpeed;
    // How close the robot has to be in inches in order to jump to the next point
    double distanceThreshold;
    // Direction to face once distance threshold was reached
    const static double noTargetHeading = -1000;
    double targetHeading = noTargetHeading;

    PathPoint(double _x, double _y, bool _driveBackwards = false, double _maxDriveSpeed = 0.3, double _maxTurnSpeed = 0.3, double _distanceThreshold = 10, double _targetHeading = noTargetHeading) : 
        x(_x),
        y(_y),
        driveBackwards(_driveBackwards),
        maxDriveSpeed(_maxDriveSpeed),
        maxTurnSpeed(_maxTurnSpeed),
        distanceThreshold(_distanceThreshold),
        targetHeading(_targetHeading) {}
};

class AbsolutePositioningSystem {
    private:
        // Current absolute X coordinate in inches
        double mX = 0;
        // Current absolute Y coordinate in inches
        double mY = 0;
        // Current absolute yaw angle in radians
        double mRotation = 0;

        // A motor on the left side of the tank drivetrain
        vex::motor_group* mLeftDrivetrainMotors;
        // A motor on the right side of the tank drivetrain
        vex::motor_group* mRightDrivetrainMotors;
        // Inertial sensors to use to improve tracking
        DualInertial* mInertialSensors;

        // Scale to convert motor encoder rotation to inches that the wheels travel
        double mDegreesToInchesRatio = 1;

        // Previous tick values so they can be compared between ticks
        double mPrevLeftDrivetrainMotorPosition = 0;
        double mPrevRightDrivetrainMotorPosition = 0;
        double mPrevInertialSensorAngle = 0;

        void TickTracking();

        
        // Whether or not the APS is allowed to control the drivetrain
        bool mDrivingEnabled = false;

        // Whether or not to flip coordinates and angles to the opposite side of the field
        bool mMirrorPath = false;

        // Buffered path to follow
        std::vector<PathPoint> mPath;

        void TickDriving();

    public:
        AbsolutePositioningSystem(vex::motor_group* leftDrivetrainMotors, vex::motor_group* rightDrivetrainMotors, DualInertial* inertialSensors, double degreesToInchesRatio) : 
            mLeftDrivetrainMotors(leftDrivetrainMotors),
            mRightDrivetrainMotors(rightDrivetrainMotors),
            mInertialSensors(inertialSensors),
            mDegreesToInchesRatio(degreesToInchesRatio) {}

        void SetPosition(double x, double y);
        void SetRotation(double rotation);

        double GetX();
        double GetY();
        double GetRotation();

        void StartTicking(double refreshRate = 50);


        void SetDriving(bool driving);
        void SetMirrored(bool mirrored);
        void AddPathPoint(PathPoint pathPoint);
        void AddPathPoint(double xInches, double yInches, bool driveBackwards = false, double maxDriveSpeed = 0.3, double maxTurnSpeed = 0.3, double distanceThreshold = 10, double targetHeading = PathPoint::noTargetHeading);
        void EndPath();
        

        void Tick();
};

#endif