#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller PrimaryController;
extern KOWGUI::GUI gui;

extern AbsolutePositioningSystem aps;

extern vex::motor leftWheelsPrimary;
extern vex::motor leftWheelsSecondary;
extern vex::motor_group leftWheels;

extern vex::motor rightWheelsPrimary;
extern vex::motor rightWheelsSecondary;
extern vex::motor_group rightWheels;
extern double rightWheelsVoltageBias;

extern vex::motor hooks;

extern vex::motor neutralFlip;

extern vex::motor leftElevationWinch;
extern vex::motor rightElevationWinch;
extern vex::motor_group elevationWinch;
extern vex::motor leftElevationArm;
extern vex::motor rightElevationArm;
extern vex::motor_group elevationArm;

extern vex::pneumatics mogoMover;

extern DualInertial dualInertial;
extern vex::encoder unpoweredWheel;
extern vex::gps gpsSensor;

#endif