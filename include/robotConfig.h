#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller PrimaryController;

extern AbsolutePositioningSystem aps;

extern vex::motor leftWheelsPrimary;
extern vex::motor leftWheelsSecondary;
extern vex::motor_group leftWheels;

extern vex::motor rightWheelsPrimary;
extern vex::motor rightWheelsSecondary;
extern vex::motor_group rightWheels;

extern vex::motor intake;

extern vex::pneumatics mogoMover;

extern DualInertial dualInertial;

#endif