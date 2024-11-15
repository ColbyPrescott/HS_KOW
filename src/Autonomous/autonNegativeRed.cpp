#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"
#include "Subsystems/claw.h"

using namespace vex;

void AutonNegativeRed() {
    // 1 Set up robot in top left of field facing into west wall
    aps.SetPosition(0.5*tiles, 4*tiles);
    aps.SetRotation(DegreesToRadians(180));
    storingRing = true;

    // 1 Give drivetrain control to the APS
    aps.SetDriving(true);
    // 1 Move claw and arm off of the wheels, slowly so it also doesn't hit the field wall before starting to drive
    arm.spinToPosition(100, degrees, 250, rpm, false);
    clawPivot.spinToPosition(-200, degrees, 100, rpm, false);
    // Take preload off of the claw it's resting on top of
    hooks.spinFor(270, degrees, 200, rpm, false);
    // But spin them back after a second so the bottom hook doesn't get caught on the arm
    task([](){task::sleep(1000); hooks.spinFor(-270, degrees); return 0;});
    task([](){task::sleep(2000); arm.spinToPosition(2166, degrees, 200, rpm, false); return 0;});

    // 2 Drive over to the mogo in the top left and grab it
    mogoMover.open();
    aps.AddPathPoint(1.25*tiles, 4*tiles + 5, true, 0.4, 0.4, 5); // Arc to help get better angle on mogo
    aps.AddPathPoint(2*tiles, 4*tiles, true, 0.4, 0.4, 2);
    aps.EndPath();
    mogoMover.close();

    // 2 Deposit preload onto held mogo
    // hooks.spinFor(-360, degrees, 200, rpm, true); // Move hooks back so AutoHooks detects it as the waitForMogo hook
    task([](){TriggerAutoHooks(); return 0;});
    wait(1, seconds);

    // 3 Drive into a stack of rings and pick up the lower red one onto the held mogo
    aps.AddPathPoint(2*tiles + 3, 5*tiles + 3, false, 0.4, 0.4, 2);
    aps.EndPath();
    task([](){TriggerAutoHooks(); return 0;});
    wait(3.5, seconds);

    // Running out of time!! Just drive to the ladder for now and hope that the other robot can get the last ring

    // Drive to touch ladder
    aps.AddPathPoint(2.5*tiles, 3.5*tiles, true, 0.5, 0.5, 2);
    aps.EndPath();



    // // 4 Lower and open claw
    // arm.spinToPosition(0, degrees, 200, rpm, true); // Arm needs to go first to stay in size
    // clawPivot.spinToPosition(-500, degrees, 200, rpm, false);
    // OpenClaw();

    // // 4 Drive into stack rings next to the autonomous line and pick up a bottom red one
    // aps.AddPathPoint(1*tiles, 5*tiles - 4, true, 0.5, 0.5, 10); // Arc to help path of claw
    // aps.AddPathPoint(3*tiles - 8, 5*tiles + 3, false, 0.4, 0.4, 2);
    // aps.EndPath();
    // CloseClaw();

    // // Somehow get the ring from the claw onto the held mogo

    // // Move claw and arm to be off of the wheels
    // clawPivot.spinToPosition(-381, degrees, 20, rpm, true);
    // arm.spinToPosition(2166, degrees, 20, rpm, false);

    // // Drive to touch ladder
    // aps.AddPathPoint(2.5*tiles, 3.5*tiles, true, 0.3, 0.3, 3);
    // aps.EndPath();
}