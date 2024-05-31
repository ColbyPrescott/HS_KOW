#include "vex.h"

using namespace vex;

const double driveSpeed = 1;
const double turnSpeed = 0.4;

const double driftThreshold = 0.08;

void InitDrivetrain() {

}

void UserInitDrivetrain() {

}

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

    // Set motor velocities
    leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), volt);
    rightWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput) * 12, -12), 12), volt);
}