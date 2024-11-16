#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonSkills() {
    aps.SetPosition(8, 72);
    aps.SetRotation(DegreesToRadians(0));
    storingRing = true;
    mogoMover.open();

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

    wait(5, seconds);

    // Put preload onto alliance stake
    // TriggerIntake();
    MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    hooks.spinFor(-600, degrees);

    // Drive to mogo
    aps.AddPathPoint(24, 5*tiles, false, 0.3, 0.3, 3);
    aps.AddPathPoint(24, 48, true, 0.3, 0.3, 3);
    aps.EndPath();
    // Pickup mogo
    mogoMover.close();
    
    // Drive mogo to the bottom left corner
    aps.AddPathPoint(10, 10, true, 0.7, 0.7, 5);
    aps.EndPath();
    // Drop mogo
    mogoMover.open();

    // Drive a bit away
    aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
    aps.EndPath();

    // RAM!
    aps.AddPathPoint(10, 10, false, 1, 1, 5);
    aps.EndPath();

    // Drive a bit away
    aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
    aps.EndPath();

    // RAM!
    aps.AddPathPoint(10, 10, false, 1, 1, 5);
    aps.EndPath();

    // Drive a bit away
    aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
    aps.EndPath();

    // RAM!
    aps.AddPathPoint(10, 10, false, 1, 1, 5);
    aps.EndPath();

    // Drive a bit away
    aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
    aps.EndPath();

    

    
}