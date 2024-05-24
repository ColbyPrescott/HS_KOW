#include "vex.h"

using namespace vex;

float driveSpeed = 1;
float turnSpeed = 0.4;

float driftThreshold = 0.08;

void InitDrivetrain() {

}

void UserInitDrivetrain() {

}

void TickDrivetrain() {
    // Get controller input
    float forwardInput = PrimaryController.Axis3.value() / 127;
    float rightwardInput = PrimaryController.Axis1.value() / 127;

    // Nullify input if it could be drifting
    if(fabs(forwardInput) < driftThreshold) forwardInput = 0;
    if(fabs(rightwardInput) < driftThreshold) rightwardInput = 0; 

    // Apply speed
    forwardInput *= driveSpeed;
    rightwardInput *= turnSpeed;

    // Set motor velocities
    leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), volt);
    leftWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput) * 12, -12), 12), volt);
}