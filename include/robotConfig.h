#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller PrimaryController;

extern vex::motor leftWheelsPrimary;
extern vex::motor leftWheelsSecondary;
extern vex::motor_group leftWheels;

extern vex::motor rightWheelsPrimary;
extern vex::motor rightWheelsSecondary;
extern vex::motor_group rightWheels;

extern vex::motor intakeConveyorTop;
extern vex::motor intakeConveyorBottom;
extern vex::motor_group intakeConveyor;

extern vex::pneumatics mogoMover;
extern vex::pneumatics intakeProp;

#endif