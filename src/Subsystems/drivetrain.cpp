#include "vex.h"

using namespace vex;

// Quick settings
// Drivetrain motor speed going forwards and backwards, 0 - 1
const double driveSpeed = 1;
// Drivetrain motor speed turning left and right, 0 - 1
const double turnSpeed = 0.4;
// Value that controller joystick axes must exceed to avoid being considered joystick drift, 0 - 1
const double driftThreshold = 0.08;

// DEBUG Target voltages
double leftWheelsInstruction = 0;
double rightWheelsInstruction = 0;


// Initialize drivetrain at the start of the program
void InitDrivetrain() {

}

// Initialize drivetrain at the start of driver control
void UserInitDrivetrain() {

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

    // DEBUG Set a variable to the calculated target voltage
    leftWheelsInstruction = fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12);
    rightWheelsInstruction = fmin(fmax((forwardInput - rightwardInput) * 12, -12), 12);

    // Set motor velocities
    leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), volt);
    rightWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput) * 12, -12), 12), volt);
}