#include "Subsystems/hooks.h"

#include "vex.h"

#include <vector>
#include "Backend/utilityMath.h"

using namespace vex;

// #region Quick settings

// Speed for the hook motor
const double hookMainRPM = 150;
const double hookFloorRPM = 100;

// How long to pause the intake at the depositRing position. 
// This gives more time for the ring to fall onto the stake
const double depositPauseMilliseconds = 1000;

// HookWaypointPositions defined in hooks.h

// Motor encoder values where hooks will be in the reset position
const std::vector<double> hookPositions = {
    0,
    928,
    1748
};

// Encoder position where the reset hook will make a full loop back to the reset position
const double hookResetPosition = 2610.72;

// #endregion


// #region Runtime variables

// Whether or not a ring is waiting to be deposited on a mogo or the claw
bool storingRing = false;

// #endregion


// #region Hook-specific functions

// Rotate hooks to position, temporarily reversing direction if it gets stuck
void HooksSpinForwardTo(double targetDegrees) {
    // Start spinning to position
    hooks.spinFor(targetDegrees - hooks.position(degrees), degrees, false);

    // Wait for hooks to accelerate
    wait(0.2, seconds);

    // Lock execution in this function until the hooks finish spinning
    while(hooks.isSpinning()) {
        // Pause to let other threads run
        wait(0.1, seconds);
        // Continue spinning normally if not stuck
        if(hooks.velocity(rpm) >= 5) continue;
        // Continue spinning normally is simply slowing down because it's almost at the target
        if((targetDegrees - hooks.position(degrees)) < 360) continue;

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
void MoveClosestHookToWaypoint(HWPs hook, HWPs waypoint) {
    // How far forwards to look for a hook before looking backwards
    const double lookAheadDegrees = 30;

    // Find closest hook to requested hook
    // Calculate distance on each hook and update least distance and index if lower
    int closestHookIndex = 0;
    int closestHookDistance = hookResetPosition;
    for(int i = 0; i < hookPositions.size(); i++) {
        // Get distance from this hook to desired hook. FixedFMod ensures that distance must be positive. Going past the target hook position will wrap to max distance
        double hookDistance = FixedFMod((double)hook - FixedFMod(hooks.position(degrees) - hookPositions[i] - lookAheadDegrees, hookResetPosition), hookResetPosition);
        // Update closest hook if closer
        if(hookDistance > closestHookDistance) continue;
        closestHookDistance = hookDistance;
        closestHookIndex = i;
    }

    // Spin hooks to align closest hook with waypoint
    int hookToWaypointDistance = FixedFMod((double)waypoint - FixedFMod(hooks.position(degrees) - hookPositions[closestHookIndex], hookResetPosition), hookResetPosition);
    HooksSpinForwardTo(hooks.position(degrees) + hookToWaypointDistance);
}

// Move the hooks based on some simple logic
void TriggerAutoHooks() {
    // If a ring is currently stored, deposit it, then wait for next ring
    if(storingRing) {
        hooks.setVelocity(hookMainRPM, rpm);
        MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
        wait(depositPauseMilliseconds, msec);
        storingRing = false;
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForRing);
        return;
    }
    
    // A ring is not stored. If the mogo is ready, pick up and deposit a ring
    if(mogoMover.value() == 0) {
        hooks.setVelocity(hookFloorRPM, rpm);
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::grabbedRing);
        hooks.setVelocity(hookMainRPM, rpm);
        MoveClosestHookToWaypoint(HWPs::grabbedRing, HWPs::depositRingOnMogo);
        wait(depositPauseMilliseconds, msec);
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForRing);
    // A ring is not stored, nor is the mogo ready. Pick up and store a ring
    } else { 
        hooks.setVelocity(hookFloorRPM, rpm);
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::grabbedRing);
        hooks.setVelocity(hookMainRPM, rpm);
        MoveClosestHookToWaypoint(HWPs::grabbedRing, HWPs::waitForMogo);
        storingRing = true;
    }
}

// #endregion


// #region Subsystem template functions

// Initialize hooks at the start of the program
void InitHooks() {
    // Set motor speeds
    hooks.setVelocity(hookMainRPM, rpm);

    // Set motor brakings
    hooks.setStopping(brake);
}

// Initialize hooks at the start of driver control
void UserInitHooks() {
    // Controls
    PrimaryController.ButtonRight.pressed(TriggerAutoHooks);

    PrimaryController.ButtonUp.pressed([](){hooks.setVelocity(hookMainRPM, rpm); hooks.spin(forward);});
    PrimaryController.ButtonUp.released([](){hooks.stop();});
    PrimaryController.ButtonLeft.pressed([](){hooks.setVelocity(hookMainRPM, rpm); hooks.spin(reverse);});
    PrimaryController.ButtonLeft.released([](){hooks.stop();});
}

// Update hooks during driver control
void TickHooks() {
    
}

// #endregion