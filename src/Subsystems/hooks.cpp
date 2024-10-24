#include "Subsystems/hooks.h"

#include "vex.h"

#include <vector>
#include "Backend/utilityMath.h"

using namespace vex;


// #region Quick settings

// Speed for the hook motor
const double hookRPM = 200;

// IntakeWaypointPositions defined in intake.h

// Motor encoder values where hooks will be in the reset position
const std::vector<double> hookPositions = {
    0,
    1147,
    2408,
    3722
};

// Encoder position where the reset hook will make a full loop back to the reset position
const double hookResetPosition = 5040.2;

// #endregion


// #region Runtime variables

// Whether or not a ring is waiting to be deposited on a mogo or the claw
bool storingRing = false;

// #endregion


// #region Special hook functions

// Rotate hooks to position, temporarily reversing direction if it gets stuck
void HooksSpinForwardTo(double targetDegrees) {
    // Start spinning to position
    hooks.spinFor(targetDegrees - hooks.position(degrees), degrees, false);

    // Wait for hooks to accelerate
    wait(0.2, seconds);

    // Lock execution in this function until the hooks finish spinning
    while(hooks.isSpinning() && (targetDegrees - hooks.position(degrees)) > 360) {
        // Pause to let other threads run
        wait(0.1, seconds);
        // Continue spinning normally if not stuck
        if(hooks.velocity(rpm) >= 5) continue;

        // If stuck, reverse direction for a short distance
        hooks.spinFor(reverse, 1000, degrees, true);
        wait(0.3, seconds);
        // Start spinning to the target position again
        hooks.spinFor(targetDegrees - hooks.position(degrees), degrees, false);
        // Wait for hooks to accelerate
        wait(0.2, seconds);
    }
}

// Move a hook a little ahead or closest behind one waypoint and move it forwards to a different target waypoint
void MoveClosestHookToWaypoint(IWPs hook, IWPs waypoint) {
    // How far forwards to look for a hook before looking backwards
    const double lookAheadDegrees = 30;

    // Find closest hook to requested hook
    // Calculate distance on each hook and update least distance and index if lower
    int closestHookIndex = 0;
    int closestHookDistance = hookResetPosition;
    for(int i = 0; i < hookPositions.size(); i++) {
        // Get distance from this hook to desired hook. FixedFMod ensures that distance must be positive. Going past the target hook position will wrap to max distance
        double hookDistance = FixedFMod((double)hook - FixedFMod(intake.position(degrees) - hookPositions[i] - lookAheadDegrees, hookResetPosition), hookResetPosition);
        // Update closest hook if closer
        if(hookDistance > closestHookDistance) continue;
        closestHookDistance = hookDistance;
        closestHookIndex = i;
    }

    // Spin hooks to align closest hook with waypoint
    int hookToWaypointDistance = FixedFMod((double)waypoint - FixedFMod(intake.position(degrees) - hookPositions[closestHookIndex], hookResetPosition), hookResetPosition);
    HooksSpinForwardTo(hooks.position(degrees) + hookToWaypointDistance);
}

void MoveStoredRingToMogo() {

}

void MoveStoredRingToClaw() {
    
}

// #endregion


// #region Subsystem template functions

// Initialize hooks at the start of the program
void InitHooks() {
    // Set motor speeds
    hooks.setVelocity(hookRPM, rpm);

    // Set motor brakings
    hooks.setStopping(brake);
}

// Initialize hooks at the start of driver control
void UserInitHooks() {
    // Controls
    PrimaryController.ButtonB.pressed(MoveStoredRingToMogo);
    PrimaryController.ButtonDown.pressed(MoveStoredRingToClaw);

    PrimaryController.ButtonUp.pressed([](){hooks.spin(forward);});
    PrimaryController.ButtonUp.released([](){hooks.stop();});
    PrimaryController.ButtonLeft.pressed([](){hooks.spin(reverse);});
    PrimaryController.ButtonLeft.released([](){hooks.stop();});
}

// Update hooks during driver control
void TickHooks() {
    
}

// #endregion