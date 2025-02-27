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

extern vex::drivetrain basicDrive;

extern vex::motor hooks;

extern vex::motor neutralFlip;

extern vex::pneumatics mogoMover;

extern vex::pneumatics wing;

extern DualInertial dualInertial;
extern vex::encoder unpoweredWheel;
extern vex::gps gpsSensor;

#endif