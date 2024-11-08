#include "vex.h"

#include "Subsystems/lift.h"

using namespace vex;

// #region Lift-specific functions

// Move lift into a known location and reset the encoder
void ResetLift() {
    // Don't break gears or excessively bend metal
    lift.setMaxTorque(10, percent);
    lift.setStopping(coast);
    lift.setVelocity(60, percent);

    // Curl up against hooks
    lift.spin(reverse);
    wait(3.5, seconds);
    lift.stop();

    // Reset encoders
    lift.setPosition(0, degrees);

    // Reset stopping, speed, and torque to normal
    InitLift();
}

// #endregion


// #region Subsystem template functions

// Initialize lift at the start of the program
void InitLift() {
    // Don't let lift fall down when not being actively moved
    lift.setStopping(hold);

    // Use all possible force to lift the claw and ring
    lift.setMaxTorque(100, percent);

    // Reduce speed so it's easier to control and less likely to break something
    lift.setVelocity(60, percent);
}

// Initialize lift at the start of driver control
void UserInitLift() {
    // Controls
    PrimaryController.ButtonL1.pressed([](){lift.spin(forward);});
    PrimaryController.ButtonL1.released([](){lift.stop();});
    PrimaryController.ButtonL2.pressed([](){lift.spin(reverse);});
    PrimaryController.ButtonL2.released([](){lift.stop();});

    PrimaryController.ButtonA.released(ResetLift);
}

// Update lift during driver control
void TickLift() {
    
}

// #endregion