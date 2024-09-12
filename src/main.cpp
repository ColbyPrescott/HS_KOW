#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/intake.h"

#include "Autonomous/autonomousSequences.h"
#include "Autonomous/autonomousSelector.h"

#include "Displays/controllerMonitors.h"

using namespace vex;

// Called at program start
void pre_auton(void) {
    // Calibrate inertial sensor
    dualInertial.Calibrate();
    while(dualInertial.GetCalibrating()) wait(0.2, seconds);
    // PrimaryController.rumble(".");

    // Call the program initialization of each subsystem
    InitDrivetrain();
    InitMogoMover();
    InitIntake();

    // Start APS
    aps.StartTicking(200);
}

// Called at start of autonomous
void autonomous(void) {
    // AutonTopRed();
    selectedAutonSequence();

    // // Force enable user control
    // aps.SetDriving(false);
    // Competition.test_driver();
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitIntake();

    // Update each subsystem continuously during driver control
    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickIntake();
        
        wait(20, msec);
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.drivercontrol(usercontrol);
    Competition.autonomous(autonomous);

    InitAutonomousSelector();

    // Run the pre-autonomous function.
    pre_auton();

    // // DEBUG
    // PrimaryController.ButtonA.pressed([](){
    //     Competition.test_auton();
    // });

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
