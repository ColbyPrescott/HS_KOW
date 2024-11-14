#include "vex.h"

#include "Subsystems/clawArm.h"

using namespace vex;

// #region Quick settings

const double clawArmExtensionSpeed = 25; // Percent per second

const double clawPivotManualRPM = 60;

// Break the extension into several different segments that move the arm and clawPivot at different speeds
struct ClawArmExtensionSegment {
    const double percent;
    const double armPositionDegrees;
    const double clawPivotPositionDegrees;
};
std::vector<ClawArmExtensionSegment> clawArmExtensionSegments = {
    {  0,  200,  -800},
    { 25,  200,  -381},
    { 50, 2166,  -511},
    {100, 4325, -950}
};

// #endregion


// #region Runtime variables

// Progress of the clawArm between the floor and the height to put a ring onto the high wall stake
double clawArmExtendedPercent = 0;

// #endregion


// #region ClawArm-specific functions

void MoveClawArmToExtensionSegment(ClawArmExtensionSegment target) {
    // Determine how many times each motor needs to rotate
    double armRevolutionsToMove = fabs(target.armPositionDegrees - arm.position(degrees)) / 360.0;
    double clawPivotRevolutionsToMove = fabs(target.clawPivotPositionDegrees - clawPivot.position(degrees)) / 360.0;
    // Determine how many minutes it should take to make those rotations. Calculated as percent to travel * how many seconds it takes to travel 100% / 60 seconds in a minute
    double minutesToMove = (fabs(target.percent - clawArmExtendedPercent) / 100.0) * (100.0 / clawArmExtensionSpeed) / 60.0;
    // Spin by revolutions to move / minutes to move so that motors will land at their targets after x minutes
    arm.spinToPosition(target.armPositionDegrees, degrees, armRevolutionsToMove / minutesToMove, rpm, false);
    clawPivot.spinToPosition(target.clawPivotPositionDegrees, degrees, clawPivotRevolutionsToMove / minutesToMove, rpm, false);

    // printf("%.0f, Moving to %.0f, armRevs: %.1f, clawPivot: %.1f, mins: %.2f\n", clawArmExtendedPercent, target.percent, armRevolutionsToMove, clawPivotRevolutionsToMove, minutesToMove);
}

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

    // // Spin claw back outwards
    // clawPivot.setVelocity(40, percent);
    // clawPivot.spinToPosition(groundPositionDegrees, degrees, false);

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
    PrimaryController.ButtonL1.released([](){arm.stop(); clawPivot.stop();});
    PrimaryController.ButtonL2.released([](){arm.stop(); clawPivot.stop();});
    PrimaryController.ButtonL1.pressed([](){
        // Find which two extension regions the armClaw is currently in the middle of, then start moving towards the higher percentage one
        for(int i = 0; i < clawArmExtensionSegments.size(); i++) {
            if(clawArmExtendedPercent >= clawArmExtensionSegments[i].percent && clawArmExtendedPercent < clawArmExtensionSegments[i + 1].percent) MoveClawArmToExtensionSegment(clawArmExtensionSegments[i + 1]);
        }
    });
    PrimaryController.ButtonL2.pressed([](){
        // Find which two extension regions the armClaw is currently in the middle of, then start moving towards the lower percentage one
        for(int i = 0; i < clawArmExtensionSegments.size(); i++) {
            if(clawArmExtendedPercent > clawArmExtensionSegments[i].percent && clawArmExtendedPercent <= clawArmExtensionSegments[i + 1].percent) MoveClawArmToExtensionSegment(clawArmExtensionSegments[i]);
        }
    });

    // Manual controls
    // PrimaryController.ButtonR1.pressed([](){clawPivot.setVelocity(clawPivotManualRPM, rpm); clawPivot.spin(forward);});
    // PrimaryController.ButtonR2.pressed([](){clawPivot.setVelocity(clawPivotManualRPM, rpm); clawPivot.spin(reverse);});
    // PrimaryController.ButtonR1.released([](){clawPivot.stop();});
    // PrimaryController.ButtonR2.released([](){clawPivot.stop();});

    // Other controls
    PrimaryController.ButtonA.released(ResetClawArm);

    // // Debug code to measure the degree positions for each extension segment
    // PrimaryController.ButtonX.pressed([](){
    //     arm.setStopping(coast);
    //     clawPivot.setStopping(coast);
    //     printf("arm: %.0f, clawPivot: %.0f\n", arm.position(degrees), clawPivot.position(degrees));
    // });
}

// Update clawArm during driver control
void TickClawArm() {
    // Calculate deltaTime, the number of seconds between now and the last time this function was called
    static uint32_t lastSystemTime = Brain.Timer.system() - 20;
    uint32_t systemTime = Brain.Timer.system();
    double deltaTime = (systemTime - lastSystemTime) / 1000.0;
    lastSystemTime = systemTime;

    // Store the extended percent from the previous tick so it can later be compared with the current extended percent
    static double prevClawArmExtendedPercent;
    prevClawArmExtendedPercent = clawArmExtendedPercent;

    // Change progress of extension in the direction of the held controls
    clawArmExtendedPercent += (PrimaryController.ButtonL1.pressing() - PrimaryController.ButtonL2.pressing()) * clawArmExtensionSpeed * deltaTime;
    // Make sure that the percentage is between 0 and 100
    clawArmExtendedPercent = fmin(fmax(clawArmExtendedPercent, 0), 100);

    // Loop through all extension segments excluding first and last. If the current extended percent crossed one of these markers, start moving to the next extension segment that's in the direction of travel
    for(int i = 1; i < clawArmExtensionSegments.size() - 1; i++) {
        if(     prevClawArmExtendedPercent < clawArmExtensionSegments[i].percent && clawArmExtendedPercent >= clawArmExtensionSegments[i].percent) MoveClawArmToExtensionSegment(clawArmExtensionSegments[i + 1]);
        else if(prevClawArmExtendedPercent > clawArmExtensionSegments[i].percent && clawArmExtendedPercent <= clawArmExtensionSegments[i].percent) MoveClawArmToExtensionSegment(clawArmExtensionSegments[i - 1]);
    }
}

// #endregion