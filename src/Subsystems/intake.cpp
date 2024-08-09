#include "vex.h"

using namespace vex;

// Quick settings
// Speed for the intake motor, 0 - 1
const double intakeRPM = 200;


// Variables needed for system functionality
// Direction of the intake motor. -1 is backwards, 0 is stopped, and 1 is forwards
int intakeDirection = 0;

// Record of motor encoder values of different significant positions
enum class IntakeDegreePositions {
    lowest = 0, // Start encoder with standoffs at lowest possible position
    highest = 2500, // Standoffs at highest possible position
    startHorizontal = 2583, // Standoffs round the corner and now face perfectly horizontal
    endHorizontal = 2800, // Last point where standoffs are horizontal
    startPlexiglass = 3720, // Standoffs have rounded the corner and now start to touch the plexiglass
    endPlexiglass = 4400, // Standoffs cleared the plexiglass and are now back to normal orientation
    readyForDisk = 4600, // Standoff is at a good position to quickly pick up the next disk
    fullLoop = 5040, // Standoff is at the lowest point again, having traveled a full entire loop
};

// Waypoints to stop at
int intakeWaypoints[] = {
    (int)IntakeDegreePositions::lowest,
    (int)IntakeDegreePositions::highest,
    (int)IntakeDegreePositions::startHorizontal,
    (int)IntakeDegreePositions::endHorizontal,
    (int)IntakeDegreePositions::startPlexiglass,
    (int)IntakeDegreePositions::endPlexiglass,
    (int)IntakeDegreePositions::readyForDisk,
};
// Current waypoint
int intakeWaypointIndex = 0;
// Total number of waypoints
const int numIntakeWaypoints = 7;


// Initialize intake at the start of the program
void InitIntake() {
    

}

// Initialize intake at the start of driver control
void UserInitIntake() {
    // Controls
    // Start or stop intake moving forwards when the up arrow button is pressed
    PrimaryController.ButtonUp.pressed([](){
        // If already moving forwards, stop
        if(intakeDirection == 1) {intake.stop(); intakeDirection = 0;}
        // If stopped or moving backwards, spin forwards
        else {intake.spin(forward, intakeRPM, rpm); intakeDirection = 1;}
    });

    // Start or stop intake moving backwards when the down arrow button is pressed
    PrimaryController.ButtonDown.pressed([](){
        // If already moving backwards, stop
        if(intakeDirection == -1) {intake.stop(); intakeDirection = 0;}
        // If stopped or moving forwards, spin backwards
        else {intake.spin(reverse, intakeRPM, rpm); intakeDirection = -1;}
    });

    // TEST Slow down intake when the left arrow button is pressed
    PrimaryController.ButtonLeft.pressed([](){
        if(intakeDirection == 1) intake.spin(forward, intakeRPM * 0.5, rpm);
        if(intakeDirection == -1) intake.spin(reverse, intakeRPM * 0.5, rpm);
    });

    PrimaryController.ButtonRight.pressed([](){
        // Increment to next waypoint
        intakeWaypointIndex++;
        // If after last waypoint, jump back to the first waypoint
        if(intakeWaypointIndex == numIntakeWaypoints) {
            // Reset waypoint index to start
            intakeWaypointIndex = 0;
            // Subtract a full loop from the motor's encoder value
            double oldEncoder = intake.position(degrees);
            double fullLoop = (double)IntakeDegreePositions::fullLoop;
            intake.setPosition(oldEncoder - fullLoop, degrees);
        }
        
        // Spin to the next waypoint
        intake.spinToPosition(intakeWaypoints[intakeWaypointIndex], degrees, intakeRPM, rpm, false);
    });
}

// Update intake during driver control
void TickIntake() {
    
}