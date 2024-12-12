#include "Subsystems/clawLift.h"

#include "vex.h"

using namespace vex;

#pragma region Quick settings

// Default speed that the clawLift moves at
const double clawLiftRPM = 100;

const double manualRightClawLiftRPM = 30;

#pragma endregion

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
    clawLift.setVelocity(clawLiftRPM, rpm);

    // Raising the claw directly against gravity, use all power available
    clawLift.setMaxTorque(100, percent);

    // Preserve temperature. Lift already has enough friction to keep its place
    clawLift.setStopping(coast);
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
    // Get the position of the controller axis last and this tick
    static int prevAxisPosition = 0;
    static int axisPosition = 0;
    prevAxisPosition = axisPosition;
    axisPosition = PrimaryController.Axis2.position(percent);

    // Position that the axis must cross to consider 
    const int axisThreshold = 80;

    // Start or stop rightClawLift if the axis crosses a threshold
    if(prevAxisPosition < axisThreshold && axisPosition >= axisThreshold)        {rightClawLift.setVelocity(manualRightClawLiftRPM, rpm); rightClawLift.spin(forward);}
    else if(prevAxisPosition >= axisThreshold && axisPosition < axisThreshold)   {rightClawLift.setVelocity(clawLiftRPM, rpm);            rightClawLift.stop();}
    else if(prevAxisPosition > -axisThreshold && axisPosition <= -axisThreshold) {rightClawLift.setVelocity(manualRightClawLiftRPM, rpm); rightClawLift.spin(reverse);}
    else if(prevAxisPosition <= -axisThreshold && axisPosition > -axisThreshold) {rightClawLift.setVelocity(clawLiftRPM, rpm);            rightClawLift.stop();}
}

#pragma endregion