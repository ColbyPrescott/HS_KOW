#include "Subsystems/clawLift.h"

#include "vex.h"

using namespace vex;

#pragma region clawLift-specific functions

// Invert the state of the clawLift pneumatic pistons
void ToggleClawLiftPistons() {
    // Get current extended / retracted state of the pistons, then invert it
    bool newState = !(bool)leftClawLiftPiston.value();

    // Set each piston to the new state
    leftClawLiftPiston.set(newState);
    rightClawLiftPiston.set(newState);
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize clawLift at the start of the program
void InitClawLift() {
    // Slow motor with slow gear needs to travel a large distance, do it as fast as possible
    clawLift.setVelocity(100, rpm);

    // Raising the claw directly against gravity, use all power available
    clawLift.setMaxTorque(100, percent);

    // Stop gravity from pulling the claw back down when the clawLift motors stop
    clawLift.setStopping(hold);
}

// Initialize clawLift at the start of driver control
void UserInitClawLift() {
    // Controls
    PrimaryController.ButtonL1.pressed([](){clawLift.spin(forward);});
    PrimaryController.ButtonL2.pressed([](){clawLift.spin(reverse);});
    PrimaryController.ButtonL1.released([](){clawLift.stop();});
    PrimaryController.ButtonL2.released([](){clawLift.stop();});

    PrimaryController.ButtonA.pressed(ToggleClawLiftPistons);
}

// Update clawLift during driver control
void TickClawLift() {
    
}

#pragma endregion