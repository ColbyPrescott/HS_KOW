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

    for(int i = 0; i < 3; i++) {
        // Drive a bit away
        aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
        aps.EndPath();

        // RAM!
        aps.AddPathPoint(10, 10, false, 1, 1, 5);
        aps.EndPath();
    }

    // Drive a bit away
    aps.AddPathPoint(40, 40, true, 0.3, 0.3, 5);
    aps.EndPath();
}