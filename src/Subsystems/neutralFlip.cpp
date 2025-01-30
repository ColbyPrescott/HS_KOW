#include "vex.h"

using namespace vex;

#pragma region Quick settings

// Maximum degrees that the neutral flip is allowed to extend
const float neutralFlipExtendedPosition = 100;

#pragma endregion

#pragma region Runtime variables

// Whether or not the neutral flip is extended outward
bool neutralFlipExtended = false;

#pragma endregion

#pragma region NeutralFlip-specific functions

// Toggle the neutral flip between the extended and retracted state
void ToggleNeutralFlip() {
    // Invert the current state 
    neutralFlipExtended = !neutralFlipExtended;
    
    // Spin to the extended or retracted position based on the new state
    if(neutralFlipExtended) {
        neutralFlip.spinToPosition(neutralFlipExtendedPosition, degrees, false);
        neutralFlip.setStopping(hold);
    } else {
        neutralFlip.spinToPosition(0, degrees, false);
        neutralFlip.setStopping(hold);
    }
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize neutral flip at the start of the program
void InitNeutralFlip() {
    // Put max amount of inertia into the ring
    neutralFlip.setVelocity(50, percent);

    // Ensure that the neutral flip can force the ring onto the stake
    neutralFlip.setMaxTorque(100, percent);
}

// Initialize mogo mover at the start of driver control
void UserInitNeutralFlip() {
    // Controls
    PrimaryController.ButtonDown.pressed(ToggleNeutralFlip);
}

// Update mogo mover during driver control
void TickNeutralFlip() {

}

#pragma endregion