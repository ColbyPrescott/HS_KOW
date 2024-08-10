#include "vex.h"

#include <vector>
#include "Backend/utilityMath.h"

using namespace vex;

// Quick settings

// Speed for the intake motor
const double intakeRPM = 200;

// How long to pause the intake at the depositRing position. 
// This gives more time for the ring to fall onto the stake
const double depositPauseMilliseconds = 1000;

// List of motor encoder values where the reset hook is at significant positions
enum class IntakeWaypointPositions {
    waitForMogo = 1965, // Reset hook is at a position to store the ring, waiting to deposit it onto a mogo
    depositRing = 2642, // Reset hook went around the top of the intake mechanism and is now completely horizontal
    waitForRing = 4647  // Reset hook is a little above the tiles, almost about to pick up a ring
};
// Abbreviate name because it's long and repeated many times
#define IWPs IntakeWaypointPositions

// Motor encoder values where hooks will be in the reset position
const std::vector<double> intakeHookPositions = {
    0,
    1136,
    2460,
    3783 
};

// Encoder position where the reset hook will make a full loop back to the reset position
const double intakeResetPosition = 5099;


// Variables needed for system functionality

// Whether or not a ring is waiting to be deposited on a mogo
bool storingRing = false;



// Move a hook a little ahead or closest behind one waypoint and move it forwards to a different target waypoint
void MoveClosestHookToWaypoint(IWPs hook, IWPs waypoint) {
    // How far forwards to look for a hook before looking backwards
    const double lookAheadDegrees = 30;

    // Find closest hook to requested hook
    // Calculate distance on each hook and update least distance and index if lower
    int closestHookIndex = 0;
    int closestHookDistance = intakeResetPosition;
    for(int i = 0; i < intakeHookPositions.size(); i++) {
        // Get distance from this hook to desired hook. FixedFMod ensures that distance must be positive. Going past the target hook position will wrap to max distance
        double hookDistance = FixedFMod((double)hook - FixedFMod(intake.position(degrees) + intakeHookPositions[i] - lookAheadDegrees, intakeResetPosition), intakeResetPosition);
        // Update closest hook if closer
        if(hookDistance > closestHookDistance) continue;
        closestHookDistance = hookDistance;
        closestHookIndex = i;
    }

    // Spin intake to align hook with waypoint
    int hookToWaypointDistance = FixedFMod((double)waypoint - FixedFMod(intakeHookPositions[closestHookIndex] + intake.position(degrees), intakeResetPosition), intakeResetPosition);
    intake.spinFor(hookToWaypointDistance, degrees, true);
}

// Move the intake. Decide exactly how it will move
void TriggerIntake() {
    // If a ring is currently stored, deposit it, then wait for next ring
    if(storingRing) {
        MoveClosestHookToWaypoint(IWPs::waitForMogo, IWPs::depositRing);
        wait(depositPauseMilliseconds, msec);
        storingRing = false;
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);
        return;
    }
    
    // A ring is not stored. If the mogo is ready, pick up and deposit a ring
    if(mogoMover.value() == 0) {
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::depositRing);
        wait(depositPauseMilliseconds, vex::seconds);
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);
    // A ring is not stored, nor is the mogo ready. Pick up and store a ring
    } else { 
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForMogo);
        storingRing = true;
    }
}



// Initialize intake at the start of the program
void InitIntake() {
    // Set motor speeds
    intake.setVelocity(intakeRPM, rpm);

    // Rotate intake from the reset position to be ready for a ring
    MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);
}

// Initialize intake at the start of driver control
void UserInitIntake() {
    // Controls
    PrimaryController.ButtonL1.pressed(TriggerIntake);
}

// Update intake during driver control
void TickIntake() {
    
}