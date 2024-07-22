#include "vex.h"

using namespace vex;

// Invert state of the mogo mover pneumatic piston
void ToggleMogoMover() {
    // Get current state, invert it, then set the state
    mogoMover.set((!(bool)mogoMover.value()));
}


// Initialize mogo mover at the start of the program
void InitMogoMover() {

}

// Initialize mogo mover at the start of driver control
void UserInitMogoMover() {
    // Controls
    // Toggle mogo mover state when L2 is pressed
    PrimaryController.ButtonL2.pressed(ToggleMogoMover);
}

// Update mogo mover during driver control
void TickMogoMover() {

}