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

// Motors
motor leftWheelsPrimary = motor(PORT14, ratio18_1, false);
motor leftWheelsSecondary = motor(PORT20, ratio18_1, true);
motor_group leftWheels = motor_group(leftWheelsPrimary, leftWheelsSecondary);

motor rightWheelsPrimary = motor(PORT5, ratio18_1, true);
motor rightWheelsSecondary = motor(PORT9, ratio18_1, false);
motor_group rightWheels = motor_group(rightWheelsPrimary, rightWheelsSecondary);
double rightWheelsVoltageBias = 0;

motor leftHooks = motor(PORT3, ratio18_1, false);
motor rightHooks = motor(PORT8, ratio18_1, true);
motor_group hooks = motor_group(leftHooks, rightHooks);

motor leftNeutralFlip = motor(PORT18, ratio36_1, true);
motor rightNeutralFlip = motor(PORT12, ratio36_1, false);
motor_group neutralFlip = motor_group(leftNeutralFlip, rightNeutralFlip);

// Pneumatics
pneumatics mogoMover = pneumatics(Brain.ThreeWirePort.C);

pneumatics wing = pneumatics(Brain.ThreeWirePort.A);


// Sensors
DualInertial dualInertial = DualInertial(InertialIntercept(PORT16, left, 18000.0 / 18099.0), InertialIntercept(PORT19, left, 18000.0 / 17935.0));
inertial singleInertial = inertial(PORT16, right);
encoder unpoweredWheel = encoder(Brain.ThreeWirePort.E);
gps gpsSensor = gps(PORT19, 5.2, 9, inches, 0, left);


// Autonomous
// Push number of inches / Output degrees: 160 / 2646
// Circumference per degree * gear ratio: (2*pi*2)/360*(60/36)
AbsolutePositioningSystem aps = AbsolutePositioningSystem(leftWheels, rightWheels, dualInertial, unpoweredWheel, gpsSensor, 160.0 / 2646.0,  96.0 / 2592.0,  20.0 / 11846.0, Brain.SDcard);
drivetrain basicDrive = drivetrain(leftWheels, rightWheels, 12.8, 10.0, 7.3, inches, 60.0/36.0);
smartdrive basicInertialDrive = smartdrive(leftWheels, rightWheels, singleInertial, 12.8, 10.0, 7.3, inches, 60.0/36.0);