#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/hooks.h"
#include "Subsystems/lift.h"
#include "Subsystems/clawPivot.h"
#include "Subsystems/claw.h"

#include "Autonomous/autonSequences.h"

#include "Displays/screenManager.h"
#include "Displays/autonSelector.h"
#include "Displays/controllerMonitors.h"

using namespace vex;

// Called at program start
void pre_auton(void) {
    // Calibrate inertial sensor
    // dualInertial.Calibrate();
    // while(dualInertial.GetCalibrating()) wait(0.2, seconds);
    // wait(2.2, seconds);
    // PrimaryController.rumble(".");

    InitScreens();
    ShowScreen(screens.autonSelector);

    // Call the program initialization of each subsystem
    InitDrivetrain();
    InitMogoMover();
    InitHooks();
    InitLift();
    InitClawPivot();
    InitClaw();

    // Start APS
    // aps.StartTicking(200);
}

// Called at start of autonomous
void autonomous(void) {
    // Start tracking and driving with APS
    aps.StartTicking(200);

    // Call the autonomous function that was selected
    selectedAutonSequence();
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitHooks();
    UserInitLift();
    UserInitClawPivot();
    UserInitClaw();

    // Update each subsystem continuously during driver control
    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickHooks();
        TickLift();
        TickClawPivot();
        TickClaw();
        
        wait(20, msec);
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.drivercontrol(usercontrol);
    Competition.autonomous(autonomous);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    int frameNum = 0;
    while(true) {
        frameNum++;

        // Draw important information to the controller screen for easy monitoring
        if(frameNum % 5 == 0) DrawControllerMonitors();

        gui.Tick();

        // // Plot APS to screen
        // const double scale = 0.95;
        // Brain.Screen.setPenColor(white);
        // Brain.Screen.drawPixel(480.0 / 2.0 + aps.GetX() * scale, 
        //                         240.0 / 2.0 - aps.GetY() * scale);

        wait(20, msec);
    }
}
