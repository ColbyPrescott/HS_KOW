#include "vex.h"

using namespace vex;

// Quick settings
// Drivetrain motor speed going forwards and backwards, 0 - 1
const double driveSpeed = 1;
// Drivetrain motor speed turning left and right, 0 - 1
const double turnSpeed = 0.5;
// Value that controller joystick axes must exceed to avoid being considered joystick drift, 0 - 1
const double driftThreshold = 0.08;


// Initialize drivetrain at the start of the program
void InitDrivetrain() {

}

// Initialize drivetrain at the start of driver control
void UserInitDrivetrain() {
    // Ensure the APS isn't still trying to control the drivetrain
    aps.SetDriving(false);  
}

// Update drivetrain during driver control
void TickDrivetrain() {
    // Get controller input
    double forwardInput = PrimaryController.Axis3.value() / 127.0;
    double rightwardInput = PrimaryController.Axis1.value() / 127.0;

    // Nullify input if it could be drifting
    if(fabs(forwardInput) < driftThreshold) forwardInput = 0;
    if(fabs(rightwardInput) < driftThreshold) rightwardInput = 0; 

    // Apply speed
    forwardInput *= driveSpeed;
    rightwardInput *= turnSpeed;

    // Increase / decrease voltage of one side to help correct drifting caused by drivetrain friction or center of mass
    double rightWheelsVoltageBias = forwardInput >= 0 ? -0.03 : 0.03; // TODO This runs even if there's no user input, causing the right side to lock up when controls stop

    // Set motor velocities
    leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), volt);
    rightWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput + rightWheelsVoltageBias) * 12, -12), 12), volt);
}