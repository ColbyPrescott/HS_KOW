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
AbsolutePositioningSystem aps = AbsolutePositioningSystem(&leftWheelsPrimary, &rightWheelsPrimary, &dualInertial);


// Motors
motor leftWheelsPrimary = motor(PORT14, ratio18_1, false);
motor leftWheelsSecondary = motor(PORT20, ratio18_1, true);
motor_group leftWheels = motor_group(leftWheelsPrimary, leftWheelsSecondary);

motor rightWheelsPrimary = motor(PORT5, ratio18_1, true);
motor rightWheelsSecondary = motor(PORT9, ratio18_1, false);
motor_group rightWheels = motor_group(rightWheelsPrimary, rightWheelsSecondary);

motor intakeConveyor = motor(PORT8, ratio18_1, true);


// Pneumatics
pneumatics mogoMover = pneumatics(Brain.ThreeWirePort.H);


// Sensors
DualInertial dualInertial = DualInertial(inertial(PORT3, vex::left), inertial(PORT6, vex::left), 1.0, 1.0);

// 18081
// 18111 Ran over a screw at one point
// 18089 Near full battery, cool

// 17925
// 17942 Near full battery, cool