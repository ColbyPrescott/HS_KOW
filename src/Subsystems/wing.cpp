#include "vex.h"

using namespace vex;

#pragma region Wing-specific functions

// Switch the wing between the extended and retracted state
void ToggleWing() {
    wing.set(!wing.value());
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize wing at the start of the program
void InitWing() {
    
}

// Initialize wing at the start of driver control
void UserInitWing() {
    // Controls
    PrimaryController.ButtonDown.pressed(ToggleWing);
}

// Update wing during driver control
void TickWing() {

}

#pragma endregion