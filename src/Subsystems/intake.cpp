#include "vex.h"

#include <vector>
#include "Backend/utilityMath.h"

using namespace vex;


// #region Quick settings

// Speed for the intake motor
const double intakeRPM = 200;

// How long to pause the intake at the depositRing position. 
// This gives more time for the ring to fall onto the stake
const double depositPauseMilliseconds = 1000;

// List of motor encoder values where the reset hook is at significant positions
enum class IntakeWaypointPositions {
    waitForMogo = 1800, // Reset hook is at a position to store the ring, waiting to deposit it onto a mogo
    depositRing = 2630, // Reset hook went around the top of the intake mechanism and is now completely horizontal
    waitForRing = 4600  // Reset hook is a little above the tiles, almost about to pick up a ring
};
// Abbreviate name because it's long and repeated many times
#define IWPs IntakeWaypointPositions

// Motor encoder values where hooks will be in the reset position
const std::vector<double> intakeHookPositions = {
    0,
    1147,
    2408,
    3722
};

// Encoder position where the reset hook will make a full loop back to the reset position
const double intakeResetPosition = 5040.2;

// #endregion


// #region Runtime variables

// Whether or not a ring is waiting to be deposited on a mogo
bool storingRing = false;

// #endregion


// #region Special intake functions

// Rotate intake to position, temporarily reversing direction if it gets stuck
void IntakeSpinForwardTo(double targetDegrees) {
    // Start spinning to position
    intake.spinFor(targetDegrees - intake.position(degrees), degrees, false);

    // Wait for intake to accelerate
    wait(0.2, seconds);

    // Lock execution in this function until the intake finishes spinning
    while(intake.isSpinning()) {
        // Pause to let other threads run
        wait(0.1, seconds);
        // Continue spinning normally if not stuck
        if(intake.velocity(rpm) >= 10) continue;

        // If stuck, reverse direction for a short duration of time
        intake.spinFor(reverse, 1, seconds);
        // Start spinning to the target position again
        intake.spinFor(targetDegrees - intake.position(degrees), degrees, false);
        // Wait for intake to accelerate
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
    IntakeSpinForwardTo(intake.position(degrees) + hookToWaypointDistance);
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
        wait(depositPauseMilliseconds, msec);
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);
    // A ring is not stored, nor is the mogo ready. Pick up and store a ring
    } else { 
        MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForMogo);
        storingRing = true;
    }
}

// #endregion


// #region Intake align button functions

// Function called when intakeAlignButton is pressed.
// On first click, spin intake forwards until let go. On second click, set the zero position
void PressIntakeAlign() {
    // Keep track of which press this is
    static int pressNum = -1;
    pressNum++;

    // If first press, spin forwards and return
    if(pressNum % 2 == 0) {
        intake.spin(forward);
        return;
    }

    // Reset encoder position
    intake.setPosition(0, degrees);
    // Reset braking
    intake.setStopping(brake);
    // Rotate intake from the reset position to be ready for a ring
    MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);
}

// Function called when intakeAlignButton is released.
// On first release, stop the intake motor. On second click, do nothing
void ReleaseIntakeAlign() {
    // Keep track of which release this is
    static int releaseNum = -1;
    releaseNum++;

    //  If first release, stop and let the motor be adjusted freely
    if(releaseNum % 2 == 0) {
        intake.setStopping(coast);
        intake.stop();
    }
}

// #endregion


// #region Subsystem template functions

// Initialize intake at the start of the program
void InitIntake() {
    // Set motor speeds
    intake.setVelocity(intakeRPM, rpm);

    // Set motor brakings
    intake.setStopping(brake);

    // Rotate intake from the reset position to be ready for a ring
    MoveClosestHookToWaypoint(IWPs::waitForRing, IWPs::waitForRing);

    // Set up functions to help align the intake when a bumper button is pressed
    intakeAlignButton.pressed(PressIntakeAlign);
    intakeAlignButton.released(ReleaseIntakeAlign);
}

// Initialize intake at the start of driver control
void UserInitIntake() {
    // Controls
    PrimaryController.ButtonL1.pressed(TriggerIntake);
}

// Update intake during driver control
void TickIntake() {
    
}

// #endregion