#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/hooks.h"
#include "Subsystems/wing.h"
#include "Subsystems/neutralFlip.h"

#include "Autonomous/autonSequences.h"

#include "Displays/screenManager.h"
#include "Displays/autonSelector.h"
#include "Displays/controllerMonitors.h"
#include "Displays/timeWarnings.h"

using namespace vex;

// Called at program start
void pre_auton(void) {
    InitScreens();
    ShowScreen(screens.autonSelector);

    // Call the program initialization of each subsystem
    InitDrivetrain();
    InitMogoMover();
    InitHooks();
    InitWing();
    InitNeutralFlip();
}

// Called at start of autonomous
void autonomous(void) {
    // Start tracking and driving with APS
    aps.StartTicking(100);
    aps.SetMirrored(false); // DEBUG Does this fix the APS being haunted?

    // Call the autonomous initialization of each subsystem
    AutonInitNeutralFlip();

    // Call the autonomous function that was selected
    if(selectedAutonSequence != nullptr) selectedAutonSequence();
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitHooks();
    UserInitWing();
    UserInitNeutralFlip();

    UserInitTimeWarnings();

    // Update each subsystem continuously during driver control
    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickHooks();
        TickWing();
        TickNeutralFlip();
        
        wait(20, msec);
    }
}

int main() {
    printf("Confirming console\n");
    // Set up callbacks for autonomous and driver control periods.
    Competition.drivercontrol(usercontrol);
    Competition.autonomous(autonomous);

    // Run the pre-autonomous function.
    pre_auton();

    // Keep track of current screen frame number for screen related timing
    int frameNum = 0;
    // Prevent main from exiting with an infinite loop.
    while(true) {
        frameNum++;

        // Draw important information to the controller screen for easy monitoring
        // Don't call every frame so that the radio link isn't overloaded
        if(frameNum % 5 == 0) DrawControllerMonitors();

        // Render the next frame on the brain's screen with KOWGUI
        gui.Tick();

        wait(20, msec);
    }
}
