#include "vex.h"

#include "Subsystems/clawArm.h"

using namespace vex;

// #region Quick settings

// Where the clawPivot tries to rotate to when picking up a ring
const double groundPositionDegrees = -876.0;
// Where the clawPivot tries to rotate to when depositing a ring onto a high wall stake
const double wallStakePositionDegrees = -1034.0;
// Speed of the clawPivot as it moves with the arm
const double moveWithArmRPM = 26;

// Speed of the clawPivot as it's moved with manual controls
const double manualRPM = 60;

// #endregion


// #region ClawArm-specific functions

// Move claw into a known location and reset the encoder
void ResetClawArm() {
    // Don't break gears or excessively bend metal
    arm.setMaxTorque(10, percent);
    arm.setStopping(coast);
    arm.setVelocity(60, percent);
    clawPivot.setMaxTorque(60, percent);
    clawPivot.setStopping(coast);
    clawPivot.setVelocity(40, percent);

    // Curl up against hooks
    arm.spin(reverse);
    clawPivot.spin(forward);
    wait(3.5, seconds);
    arm.stop();
    clawPivot.stop();

    // Reset encoders
    arm.setPosition(0, degrees);
    clawPivot.setPosition(0, degrees);

    // Spin claw back outwards
    clawPivot.setVelocity(40, percent);
    clawPivot.spinToPosition(groundPositionDegrees, degrees, false);

    // Reset stopping, speed, and torque to normal
    InitClawArm();

    // Vibrate controller to signify that the reset process finished and motors can be controlled again
    PrimaryController.rumble(".");
}

// #endregion


// #region Subsystem template functions

// Initialize clawArm at the start of the program
void InitClawArm() {
    // Don't let claw fall down when not being actively moved
    arm.setStopping(hold);
    clawPivot.setStopping(hold);

    // Use all possible force to arm the claw and ring
    arm.setMaxTorque(100, percent);
    clawPivot.setMaxTorque(100, percent);

    // Reduce speed so it's easier to control and less likely to break something
    arm.setVelocity(60, percent);
}

// Initialize clawArm at the start of driver control
void UserInitClawArm() {
    // Controls for arm
    PrimaryController.ButtonL1.pressed([](){arm.spin(forward);});
    PrimaryController.ButtonL1.released([](){arm.stop();});
    PrimaryController.ButtonL2.pressed([](){arm.spin(reverse);});
    PrimaryController.ButtonL2.released([](){arm.stop();});
    
    // Controls linked with arm
    PrimaryController.ButtonL1.pressed([](){clawPivot.setVelocity(moveWithArmRPM, rpm); clawPivot.spinToPosition(wallStakePositionDegrees, degrees, false);});
    PrimaryController.ButtonL2.pressed([](){clawPivot.setVelocity(moveWithArmRPM, rpm); clawPivot.spinToPosition(groundPositionDegrees, degrees, false);});
    PrimaryController.ButtonL1.released([](){clawPivot.stop();});
    PrimaryController.ButtonL2.released([](){clawPivot.stop();});

    // Manual controls
    PrimaryController.ButtonR1.pressed([](){clawPivot.setVelocity(manualRPM, rpm); clawPivot.spin(forward);});
    PrimaryController.ButtonR2.pressed([](){clawPivot.setVelocity(manualRPM, rpm); clawPivot.spin(reverse);});
    PrimaryController.ButtonR1.released([](){clawPivot.stop();});
    PrimaryController.ButtonR2.released([](){clawPivot.stop();});

    // Other controls
    PrimaryController.ButtonA.released(ResetClawArm);
}

// Update clawArm during driver control
void TickClawArm() {
    
}

// #endregion