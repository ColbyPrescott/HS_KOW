#include "vex.h"

using namespace vex;

// VEX related global variables
competition Competition;
brain Brain;
controller PrimaryController;


// Motors
motor leftWheelsPrimary = motor(PORT5, ratio18_1, false);
motor leftWheelsSecondary = motor(PORT6, ratio18_1, true);
motor_group leftWheels = motor_group(leftWheelsPrimary, leftWheelsSecondary);

motor rightWheelsPrimary = motor(PORT14, ratio18_1, true);
motor rightWheelsSecondary = motor(PORT16, ratio18_1, false);
motor_group rightWheels = motor_group(rightWheelsPrimary, rightWheelsSecondary);

motor intakeConveyorTop = motor(PORT1, ratio18_1, false);
motor intakeConveyorBottom = motor(PORT2, true);
motor_group intakeConveyor = motor_group(intakeConveyorTop, intakeConveyorBottom);


// Pneumatics
pneumatics mogoMover = pneumatics(Brain.ThreeWirePort.A);
pneumatics intakeProp = pneumatics(Brain.ThreeWirePort.B);


// Sensors