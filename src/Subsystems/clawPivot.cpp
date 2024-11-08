#include "vex.h"

#include "Subsystems/clawPivot.h"

using namespace vex;

// #region Quick settings

// Where the clawPivot tries to rotate to when picking up a ring
const double groundPositionDegrees = -876.0;

// Where the clawPivot tries to rotate to when depositing a ring onto a high wall stake
const double wallStakePositionDegrees = -1034.0;

// #endregion


// #region ClawPivot-specific functions

// Move claw into a known location and reset the encoder
void ResetClawPivot() {
    // Don't break gears
    clawPivot.setMaxTorque(60, percent);
    clawPivot.setStopping(coast);
    clawPivot.setVelocity(40, percent);

    // Curl up against hooks
    clawPivot.spin(forward);
    wait(3.5, seconds);
    clawPivot.stop();

    // Reset encoders
    clawPivot.setPosition(0, degrees);

    // Spin claw back outwards
    clawPivot.setVelocity(40, percent);
    clawPivot.spinToPosition(groundPositionDegrees, degrees, false);

    // Reset stopping, speed, and torque to normal
    InitClawPivot();

    // Vibrate controller to signify that the reset process finished and motors can be controlled again
    PrimaryController.rumble(".");
}

// #endregion


// #region Subsystem template functions

// Initialize claw pivot at the start of the program
void InitClawPivot() {
    // Don't let claw fall down when not being actively moved
    clawPivot.setStopping(hold);

    // Use all possible force to lift the ring
    clawPivot.setMaxTorque(100, percent);

    // Rotate at a speed where the clawPivot goes from ground to wallStakePositionDegrees in slightly less time than it takes the lift to travel
    clawPivot.setVelocity(13, percent);
}

// Initialize claw pivot at the start of driver control
void UserInitClawPivot() {
    // Controls
    PrimaryController.ButtonL1.pressed([](){clawPivot.spinToPosition(wallStakePositionDegrees, degrees, false);});
    PrimaryController.ButtonL2.pressed([](){clawPivot.spinToPosition(groundPositionDegrees, degrees, false);});
    PrimaryController.ButtonL1.released([](){clawPivot.stop();});
    PrimaryController.ButtonL2.released([](){clawPivot.stop();});

    PrimaryController.ButtonA.released(ResetClawPivot);
}

// Update claw pivot during driver control
void TickClawPivot() {
    
}

// #endregion