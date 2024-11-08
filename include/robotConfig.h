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

extern vex::motor leftLift;
extern vex::motor rightLift;
extern vex::motor_group lift;

extern vex::motor clawPivot;
extern vex::motor claw;

extern vex::motor hooks;

extern vex::pneumatics mogoMover;

extern DualInertial dualInertial;

#endif