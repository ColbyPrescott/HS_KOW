#include "vex.h"

using namespace vex;

#pragma region Runtime variables

// Current state of whether the elevation arm is pivoted forwards or backwards
bool elevationArmExtended = false;

#pragma endregion

#pragma region Elevation-specific functions

// Move the elevation arm forwards
void ExtendElevationArm() {
    elevationArmExtended = true;
    elevationArm.spinToPosition(115, degrees, false);
}

// Move the elevation arm backwards
void RetractElevationArm() {
    elevationArmExtended = false;
    elevationArm.spinToPosition(0, degrees, false);
}

// Switch the elevation arm between the forwards and backwards state
void ToggleElevationArm() {
    elevationArmExtended = !elevationArmExtended;

    if(elevationArmExtended) ExtendElevationArm();
    else RetractElevationArm();
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize elevation at the start of the program
void InitElevation() {
    // Elevation should happen as quickly as possible
    elevationWinch.setVelocity(100, percent);
    elevationArm.setVelocity(100, percent);

    // Make sure the motors can still move under the load of the entire robot's weight
    elevationWinch.setMaxTorque(100, percent);
    elevationArm.setMaxTorque(100, percent);

    // Ensure the motors hold their position even when they aren't actively spinning
    elevationWinch.setStopping(hold);
    elevationArm.setStopping(hold);
}

// Initialize elevation at the start of driver control
void UserInitElevation() {
    // Controls
    PrimaryController.ButtonY.pressed(ToggleElevationArm);
    
    PrimaryController.ButtonL1.pressed([](){elevationWinch.spin(forward);});
    PrimaryController.ButtonL2.pressed([](){elevationWinch.spin(reverse);});
    PrimaryController.ButtonL1.released([](){elevationWinch.stop();});
    PrimaryController.ButtonL2.released([](){elevationWinch.stop();});
}

// Update elevation during driver control
void TickElevation() {

}

#pragma endregion