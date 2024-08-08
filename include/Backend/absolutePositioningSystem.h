#ifndef ABSOLUTE_POSITIONING_SYSTEM_H
#define ABSOLUTE_POSITIONING_SYSTEM_H

#include "v5.h"
#include "v5_vcs.h"

#include "Backend/dualInertial.h"

class AbsolutePositioningSystem {
    private:
        // Current absolute X coordinate in inches
        double mX = 0;
        // Current absolute Y coordinate in inches
        double mY = 0;
        // Current absolute angle in radians
        double mAngle = 0;

        // A motor on the left side of the tank drivetrain
        vex::motor* mLeftDrivetrainMotor;
        // A motor on the right side of the tank drivetrain
        vex::motor* mRightDrivetrainMotor;
        // Inertial sensors to use to improve tracking
        DualInertial* mInertialSensors;

        // Scale to convert motor encoder rotation to inches that the wheels travel
        double mDegreesToInchesRatio = 1;

        // Previous tick values so they can be compared between ticks
        double mPrevLeftDrivetrainMotorPosition = 0;
        double mPrevRightDrivetrainMotorPosition = 0;
        double mPrevInertialSensorAngle = 0;

    public:
        AbsolutePositioningSystem(vex::motor* leftDrivetrainMotor, vex::motor* rightDrivetrainMotor, DualInertial* inertialSensors, double degreesToInchesRatio) : 
            mLeftDrivetrainMotor(leftDrivetrainMotor),
            mRightDrivetrainMotor(rightDrivetrainMotor),
            mInertialSensors(inertialSensors),
            mDegreesToInchesRatio(degreesToInchesRatio) {}

        void SetPosition(double x, double y);
        void SetAngle(double angle);

        double GetX();
        double GetY();
        double GetAngle();

        void StartTracking(double refreshRate = 50);

        void Tick();
};

#endif