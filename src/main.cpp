#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"
#include "Subsystems/elevation.h"

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
    InitNeutralFlip();
    InitElevation();
}

// Called at start of autonomous
void autonomous(void) {
    // Start tracking and driving with APS
    aps.StartTicking(100);
    aps.SetMirrored(false); // DEBUG Does this fix the APS being haunted?

    // Call the autonomous function that was selected
    if(selectedAutonSequence != nullptr) selectedAutonSequence();
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitHooks();
    UserInitNeutralFlip();
    UserInitElevation();

    UserInitTimeWarnings();

    // Update each subsystem continuously during driver control
    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickHooks();
        TickNeutralFlip();
        TickElevation();
        
        wait(20, msec);
    }
}

int main() {
    printf("Confirming console\n");
    // Set up callbacks for autonomous and driver control periods.
    Competition.drivercontrol(usercontrol);
    Competition.autonomous(autonomous);

    // Make sure the program can start up
    wait(0.5, seconds);

    // Run the pre-autonomous function.
    pre_auton();

    // // DEBUG
    // Brain.Screen.clearScreen();
    // aps.StartTicking(100);
    // aps.SetPosition(24 * 3, 24 * 3);
    // Brain.Screen.pressed([](){Brain.Screen.clearScreen();});

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

        // // DEBUG
        // Brain.Screen.setPenColor(white);
        // Brain.Screen.drawPixel(Map(aps.GetX(), 0, 24 * 6, 240 - 120, 240 + 120), Map(aps.GetY(), 0, 24 * 6, 240, 0));
        // Brain.Screen.setPenColor(gpsSensor.quality() == 100 ? color(0, 255, 0) : color(50, 0, 0));
        // Brain.Screen.drawPixel(Map(gpsSensor.xPosition(inches), -24 * 3, 24 * 3, 240 - 120, 240 + 120), Map(gpsSensor.yPosition(inches), -24 * 3, 24 * 3, 240, 0));

        wait(20, msec);
    }
}
