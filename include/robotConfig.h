#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller PrimaryController;
extern KOWGUI::GUI gui;

extern vex::motor leftWheelsPrimary;
extern vex::motor leftWheelsSecondary;
extern vex::motor_group leftWheels;

extern vex::motor rightWheelsPrimary;
extern vex::motor rightWheelsSecondary;
extern vex::motor_group rightWheels;
extern double rightWheelsVoltageBias;

extern vex::motor leftHooks;
extern vex::motor rightHooks;
extern vex::motor_group hooks;

extern vex::motor leftNeutralFlip;
extern vex::motor rightNeutralFlip;
extern vex::motor_group neutralFlip;

extern vex::pneumatics mogoMover;

extern vex::pneumatics wing;

extern DualInertial dualInertial;
extern vex::inertial singleInertial;
extern vex::encoder unpoweredWheel;
extern vex::gps gpsSensor;

extern AbsolutePositioningSystem aps;
extern vex::drivetrain basicDrive;
extern vex::smartdrive basicInertialDrive;

#endif