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
DualInertial dualInertial = DualInertial(InertialIntercept(PORT3, vex::left), InertialIntercept(PORT6, vex::left), 1.0, 1.0);

// Inertial A
// Room temperature: 74 degrees fahrenheit
// Time seconds, Expected degrees, Measured degrees, Temperature celsius
// 3.432, 0, 0, 30.77
// 24.232, 1800, 1814, 35.93
// 44.032, 3600, 3628, 38.19
// 64.962, 5400, 5442, 39.73
// 85.322, 7200, 7256, 40.72
// 108.172, 9000, 9070, 41.53
// 131.792, 10800, 10884, 42.12
// 152.372, 12600, 12698, 42.53
// 172.872, 14400, 14512, 42.85
// 193.092, 16200, 16326, 43.09
// 214.742, 18000, 18140, 43.32
// 236.807, 19800, 19955, 43.50
// 257.602, 21600, 21769, 43.64
// 277.807, 23400, 23583, 43.75
// 299.082, 25200, 25397, 43.85
// 320.557, 27000, 27211, 43.93
// 342.402, 28800, 29026, 44.01
// 364.732, 30600, 30840, 44.11
// 384.682, 32400, 32654, 44.12
// 405.032, 34200, 34468, 44.18
// 427.392, 36000, 36282, 44.20

// Graphed in Desmos: https://www.desmos.com/calculator/iyn2oyvjvo