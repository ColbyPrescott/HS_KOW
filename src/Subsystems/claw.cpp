#include "vex.h"

using namespace vex;

#pragma region Quick settings

const double clawClosedPosition = -33;
const double clawOpenedPosition = 0;

#pragma endregion

#pragma region Runtime variables

// Whether or not the claw is currently opened
bool clawOpen = false;

#pragma endregion

#pragma region Claw-specific functions

// Start rotating the claw to the open position
void OpenClaw() {
    clawOpen = true;
    // Stop the spring from closing the claw again
    claw.setStopping(hold);
    claw.spinToPosition(clawOpenedPosition, degrees, false);
}

// Start rotating the claw to the closed position, grip anything that might be in the claw
void CloseClaw() {
    clawOpen = false;
    // Don't strain the motor when it's doing nothing
    claw.setStopping(coast);
    claw.spinToPosition(clawClosedPosition, degrees, false);
}

// Switch the claw between open and closed
void ToggleClaw() {
    clawOpen = !clawOpen;
    if(clawOpen) OpenClaw();
    else CloseClaw();
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize claw at the start of the program
void InitClaw() {
    // Grip opjects at max strength
    claw.setMaxTorque(100, percent);

    // Don't strain the motor too much
    claw.setVelocity(60, percent);
}

// Initialize claw at the start of driver control
void UserInitClaw() {
    // Controls
    PrimaryController.ButtonY.pressed(ToggleClaw);
}

// Update claw during driver control
void TickClaw() {
    
}

#pragma endregion