#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/intake.h"

#include "Displays/controllerMonitors.h"

using namespace vex;

// Called at program start
void pre_auton(void) {
    // Calibrate inertial sensor
    dualInertial.Calibrate();
    while(dualInertial.GetCalibrating()) wait(0.2, seconds);
    PrimaryController.rumble(".");

    // Call the program initialization of each subsystem
    InitDrivetrain();
    InitMogoMover();
    // InitIntake();

    // Start APS
    aps.StartTicking(200);


    // #region Test autonomous
    // Start one tile in from the center of a side
    // Clockwise loop around field
    aps.AddPathPoint({24 * 2    , 24 * 0});
    aps.AddPathPoint({24 * 2    , 24 * -4});
    aps.AddPathPoint({24 * -0.5 , 24 * -4});
    aps.AddPathPoint({24 * -2   , 24 * -2});
    aps.AddPathPoint({24 * -2   , 24 * -1});
    aps.AddPathPoint({24 * 0    , 24 * 0});

    // Turn around
    aps.AddPathPoint({24 * 2    , 24 * -1});
    aps.AddPathPoint({24 * 2    , 24 * 0});
    aps.AddPathPoint({24 * 0    , 24 * 0});

    // Counterclockwise loop around field
    aps.AddPathPoint({24 * -2   , 24 * -1});
    aps.AddPathPoint({24 * -2   , 24 * -2});
    aps.AddPathPoint({24 * -0.5 , 24 * -4});
    aps.AddPathPoint({24 * 2    , 24 * -4});
    aps.AddPathPoint({24 * 2    , 24 * 0});
    aps.AddPathPoint({24 * 0    , 24 * 0});

    // Start
    aps.SetDriving(true);
    // #endregion
}

// Called at start of autonomous
void autonomous(void) {
    
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitIntake();

    // Update each subsystem continuously during driver control
    while(true) {
        // TickDrivetrain();
        TickMogoMover();
        TickIntake();
        
        wait(20, msec);
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while(true) {

        // Draw important information to the controller screen for easy monitoring
        DrawControllerMonitors();

        // Plot APS to screen
        const double scale = 0.95;
        Brain.Screen.setPenColor(white);
        Brain.Screen.drawPixel(480.0 / 2.0 + aps.GetX() * scale, 
                                240.0 / 2.0 - aps.GetY() * scale);

        wait(100, msec);
    }
}
