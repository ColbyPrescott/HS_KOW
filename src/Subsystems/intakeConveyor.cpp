#include "vex.h"

using namespace vex;

// Quick settings
// Speed for the intake conveyor motors, 0 - 1
const double intakeConveyorRPM = 200;


// Variables needed for system functionality
// Direction of the intake conveyor motors. -1 is backwards, 0 is stopped, and 1 is forwards
int intakeConveyorDirection = 0;

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


// Initialize intake conveyor at the start of the program
void InitIntakeConveyor() {
    

}

// Initialize intake conveyor at the start of driver control
void UserInitIntakeConveyor() {
    // Controls
    // Start or stop intake conveyor moving forwards when the up arrow button is pressed
    PrimaryController.ButtonUp.pressed([](){
        // If already moving forwards, stop
        if(intakeConveyorDirection == 1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving backwards, spin forwards
        else {intakeConveyor.spin(forward, intakeConveyorRPM, rpm); intakeConveyorDirection = 1;}
    });

    // Start or stop intake conveyor moving backwards when the down arrow button is pressed
    PrimaryController.ButtonDown.pressed([](){
        // If already moving backwards, stop
        if(intakeConveyorDirection == -1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving forwards, spin backwards
        else {intakeConveyor.spin(reverse, intakeConveyorRPM, rpm); intakeConveyorDirection = -1;}
    });

    // TEST Slow down intake conveyor when the left arrow button is pressed
    PrimaryController.ButtonLeft.pressed([](){
        if(intakeConveyorDirection == 1) intakeConveyor.spin(forward, intakeConveyorRPM * 0.5, rpm);
        if(intakeConveyorDirection == -1) intakeConveyor.spin(reverse, intakeConveyorRPM * 0.5, rpm);
    });

    PrimaryController.ButtonRight.pressed([](){
        // Increment to next waypoint
        intakeWaypointIndex++;
        // If after last waypoint, jump back to the first waypoint
        if(intakeWaypointIndex == numIntakeWaypoints) {
            // Reset waypoint index to start
            intakeWaypointIndex = 0;
            // Subtract a full loop from the motor's encoder value
            double oldEncoder = intakeConveyor.position(degrees);
            double fullLoop = (double)IntakeDegreePositions::fullLoop;
            intakeConveyor.setPosition(oldEncoder - fullLoop, degrees);
        }
        
        // Spin to the next waypoint
        intakeConveyor.spinToPosition(intakeWaypoints[intakeWaypointIndex], degrees, intakeConveyorRPM, rpm, false);
    });
}

// Update intake conveyor during driver control
void TickIntakeConveyor() {
    
}