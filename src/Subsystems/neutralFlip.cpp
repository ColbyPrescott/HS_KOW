#include "vex.h"

using namespace vex;

#pragma region Quick settings

// Maximum degrees that the neutral flip is allowed to extend
const float neutralFlipExtendedPosition = 100;
const float neutralFlipRetractedPosition = -10;

#pragma endregion

#pragma region Runtime variables

// Whether or not the neutral flip is extended outward
bool neutralFlipExtended = false;

#pragma endregion

#pragma region NeutralFlip-specific functions

// Move the neutral flip to the extended position
void ExtendNeutralFlip() {
    neutralFlipExtended = true;

    neutralFlip.setVelocity(40, percent);
    neutralFlip.spinToPosition(neutralFlipExtendedPosition, degrees, false);
    neutralFlip.setStopping(hold);
}

// Move the neutral flip to the retracted position
void RetractNeutralFlip() {
    neutralFlipExtended = false;
    
    neutralFlip.setVelocity(80, percent);
    neutralFlip.spinToPosition(neutralFlipRetractedPosition, degrees, false);
    neutralFlip.setStopping(hold);
}

// Toggle the neutral flip between the extended and retracted state
void ToggleNeutralFlip() {
    // Invert the current state 
    neutralFlipExtended = !neutralFlipExtended;
    
    // Spin to the extended or retracted position based on the new state
    if(neutralFlipExtended) ExtendNeutralFlip();
    else RetractNeutralFlip();
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize neutral flip at the start of the program
void InitNeutralFlip() {
    // Put max amount of inertia into the ring
    neutralFlip.setVelocity(40, percent);

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