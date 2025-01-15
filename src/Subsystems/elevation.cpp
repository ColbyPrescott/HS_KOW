#include "vex.h"

using namespace vex;

#pragma region Elevation-specific functions

void ToggleElevationPistons() {
    // Get the state of one piston, that way the two sides can't ever desync
    bool elevationPistonState = leftElevationPiston.value();

    // Invert the state for the new value
    elevationPistonState = !elevationPistonState;

    // Update each piston to the new, inverted extended state
    leftElevationPiston.set(elevationPistonState);
    rightElevationPiston.set(elevationPistonState);
}

#pragma endregion

#pragma region Subsystem template functions

// Initialize neutral flip at the start of the program
void InitElevation() {
    // Red motors are slow, use as much speed as they have
    winch.setVelocity(100, percent);

    // Hold the weight of the entire robot
    winch.setMaxTorque(100, percent);
    winch.setStopping(hold);
}

// Initialize mogo mover at the start of driver control
void UserInitElevation() {
    // Controls
    PrimaryController.ButtonY.pressed(ToggleElevationPistons);
    
    PrimaryController.ButtonL1.pressed([](){winch.spin(forward);});
    PrimaryController.ButtonL2.pressed([](){winch.spin(reverse);});
    PrimaryController.ButtonL1.released([](){winch.stop();});
    PrimaryController.ButtonL2.released([](){winch.stop();});
}

// Update mogo mover during driver control
void TickElevation() {

}

#pragma endregion