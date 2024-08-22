#include "vex.h"

#include "Backend/absolutePositioningSystem.h"

using namespace vex;

// VEX related global variables
// I would love to use camelCase here like all of my other variables, but 
// VEX uses a different naming convention that would create naming conflicts
competition Competition;
brain Brain;
controller PrimaryController;


// Other global variables
// Push number of inches / Output degrees: 160 / 2646
// Circumference per degree * gear ratio: (2*pi*2)/360*(60/36)
AbsolutePositioningSystem aps = AbsolutePositioningSystem(&leftWheels, &rightWheels, &dualInertial, 160.0 / 2646.0);


// Motors
motor leftWheelsPrimary = motor(PORT14, ratio18_1, false);
motor leftWheelsSecondary = motor(PORT20, ratio18_1, true);
motor_group leftWheels = motor_group(leftWheelsPrimary, leftWheelsSecondary);

motor rightWheelsPrimary = motor(PORT5, ratio18_1, true);
motor rightWheelsSecondary = motor(PORT9, ratio18_1, false);
motor_group rightWheels = motor_group(rightWheelsPrimary, rightWheelsSecondary);

motor intake = motor(PORT8, ratio6_1, true);


// Pneumatics
pneumatics mogoMover = pneumatics(Brain.ThreeWirePort.H);


// Sensors
bumper intakeAlignButton = bumper(Brain.ThreeWirePort.A);
DualInertial dualInertial = DualInertial(InertialIntercept(PORT3, vex::left, 18000.0 / 18099.0), InertialIntercept(PORT6, vex::left, 18000.0 / 17935));