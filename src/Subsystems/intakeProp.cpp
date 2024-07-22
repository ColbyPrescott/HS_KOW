#include "vex.h"

using namespace vex;

// Invert state of the intake prop pneumatic piston
void ToggleIntakeProp() {
    // Get current state, invert it, then set the state
    intakeProp.set((!(bool)intakeProp.value()));
}

// Initialize intake prop at the start of the program
void InitIntakeProp() {
    // intakeProp.open(); // Activate piston. Currently needs to be rewired opposite
}

// Initialize intake prop at the start of driver control
void UserInitIntakeProp() {
    PrimaryController.ButtonR2.pressed(ToggleIntakeProp); // DEBUG
}

// Update intake prop during driver control
void TickIntakeProp() {

}