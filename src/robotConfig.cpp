#include "vex.h"

#include "Backend/absolutePositioningSystem.h"

using namespace vex;
using namespace KOWGUI;

// VEX related global variables
// I would love to use camelCase here like all of my other variables, but 
// VEX uses a different naming convention that would create naming conflicts
competition Competition;
brain Brain;
controller PrimaryController;
GUI gui = GUI(Brain);


// Other global variables
// Push number of inches / Output degrees: 160 / 2646
// Circumference per degree * gear ratio: (2*pi*2)/360*(60/36)
AbsolutePositioningSystem aps = AbsolutePositioningSystem(&leftWheels, &rightWheels, &dualInertial, 160.0 / 2646.0);


// Motors
motor leftWheelsPrimary = motor(PORT14, ratio36_1, false);
motor leftWheelsSecondary = motor(PORT20, ratio36_1, true);
motor_group leftWheels = motor_group(leftWheelsPrimary, leftWheelsSecondary);

motor rightWheelsPrimary = motor(PORT5, ratio36_1, true);
motor rightWheelsSecondary = motor(PORT9, ratio36_1, false);
motor_group rightWheels = motor_group(rightWheelsPrimary, rightWheelsSecondary);

motor hooks = motor(PORT3, ratio18_1, false);

motor neutralFlip = motor(PORT18, ratio36_1, false);

motor leftWinch = motor(PORT8, ratio36_1, false);
motor rightWinch = motor(PORT6, ratio36_1, false);
motor_group winch = motor_group(leftWinch, rightWinch);


// Pneumatics
pneumatics mogoMover = pneumatics(Brain.ThreeWirePort.C);

pneumatics leftElevationPiston = pneumatics(Brain.ThreeWirePort.A);
pneumatics rightElevationPiston = pneumatics(Brain.ThreeWirePort.B);


// Sensors
DualInertial dualInertial = DualInertial(InertialIntercept(PORT12, left, 18000.0 / 18099.0), InertialIntercept(PORT6, left, 18000.0 / 17935.0));
gps gpsSensor = gps(PORT17, 0, 0, inches, 0, left);