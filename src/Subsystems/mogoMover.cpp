#include "vex.h"

using namespace vex;

// #region MogoMover-specific functions

// Invert state of the mogo mover pneumatic piston
void ToggleMogoMover() {
    // Get current state, invert it, then set the state
    mogoMover.set((!(bool)mogoMover.value()));

    // Slight haptic feedback to better indicate when the mogo was grabbed vs released
    if(mogoMover.value() == 1) PrimaryController.rumble(".");
}

// #endregion


// #region Subsystem template functions

// Initialize mogo mover at the start of the program
void InitMogoMover() {

}

// Initialize mogo mover at the start of driver control
void UserInitMogoMover() {
    // Controls
    // Toggle mogo mover state when Y is pressed
    PrimaryController.ButtonY.pressed(ToggleMogoMover);
}

// Update mogo mover during driver control
void TickMogoMover() {

}

// #endregion