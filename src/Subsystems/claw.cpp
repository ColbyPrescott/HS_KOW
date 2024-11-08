#include "vex.h"

using namespace vex;

// #region Runtime variables

// Whether or not the claw is currently opened
bool clawOpen = false;

// #endregion


// #region Claw-specific functions

// Start rotating the claw to the open position
void OpenClaw() {
    clawOpen = true;
    // Stop the spring from closing the claw again
    claw.setStopping(hold);
    claw.spinToPosition(156, degrees, false);
}

// Start rotating the claw to the closed position, grip anything that might be in the claw
void CloseClaw() {
    clawOpen = false;
    // Don't strain the motor when it's doing nothing
    claw.setStopping(coast);
    claw.spinToPosition(0, degrees, false);
}

// Switch the claw between open and closed
void ToggleClaw() {
    clawOpen = !clawOpen;
    if(clawOpen) OpenClaw();
    else CloseClaw();
}

// #endregion


// #region Subsystem template functions

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
    PrimaryController.ButtonB.pressed(ToggleClaw);
}

// Update claw during driver control
void TickClaw() {
    
}

// #endregion