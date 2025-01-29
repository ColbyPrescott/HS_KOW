#ifndef ABSOLUTE_POSITIONING_SYSTEM_H
#define ABSOLUTE_POSITIONING_SYSTEM_H

#include "v5.h"
#include "v5_vcs.h"

#include "Backend/dualInertial.h"

#include <vector>

struct PathSection {
    // Four points that make up a cubic Bézier curve
    double p0x;
    double p0y;
    double p1x;
    double p1y;
    double p2x;
    double p2y;
    double p3x;
    double p3y;

    // What percentage speed to drive at the start of the curve
    double startSpeed;
    // What percentage speed to drive at by the end of the curve
    double endSpeed;

    PathSection(double _p0x, double _p0y, double _p1x, double _p1y, double _p2x, double _p2y, double _p3x, double _p3y, double _startSpeed, double _endSpeed) :
        p0x(_p0x),
        p0y(_p0y),
        p1x(_p1x),
        p1y(_p1y),
        p2x(_p2x),
        p2y(_p2y),
        p3x(_p3x),
        p3y(_p3y),
        startSpeed(_startSpeed),
        endSpeed(_endSpeed) {}
    
    double GetX(double t);
    double GetY(double t);
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
        // GPS sensor to occasionally calibrate tracking position
        vex::gps* mGPSSensor;

        // Whether or not to use values from the GPS sensor to update the position
        bool mEnableGPS = false;

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
        std::vector<PathSection> mPath;
        // How far along the robot is on the current PathSection
        double mPathSectionProgress = 0;

        void TickDriving();

    public:
        AbsolutePositioningSystem(vex::motor_group* leftDrivetrainMotors, vex::motor_group* rightDrivetrainMotors, DualInertial* inertialSensors, vex::gps* gpsSensor, double degreesToInchesRatio) : 
            mLeftDrivetrainMotors(leftDrivetrainMotors),
            mRightDrivetrainMotors(rightDrivetrainMotors),
            mInertialSensors(inertialSensors),
            mGPSSensor(gpsSensor),
            mDegreesToInchesRatio(degreesToInchesRatio) {}

        void SetPosition(double x, double y);
        void SetRotation(double rotation);

        double GetX();
        double GetY();
        double GetRotation();

        void StartTicking(double refreshRate = 50);


        void SetDriving(bool driving);
        void SetMirrored(bool mirrored);
        void AddPathSection(PathSection pathSection);
        void AddPathSection(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double startSpeed, double endSpeed);
        void EndPath();
        

        void Tick();
};

#endif