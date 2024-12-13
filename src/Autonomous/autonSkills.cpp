#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonSkills() {
    // Setup robot next to alliance stake facing away from wall
    aps.SetPosition(8, 72);
    aps.SetRotation(DegreesToRadians(0));
    storingRing = true;
    mogoMover.open();

    // Give drivetrain control to the APS
    aps.SetDriving(true);

    // Put preload onto alliance stake
    MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    hooks.spinFor(-600, degrees);

    // Drive to bottom left mogo
    aps.AddPathPoint(1.5*tiles, 3.5*tiles, false, 0.3, 0.3, 3);
    aps.AddPathPoint(1*tiles, 3*tiles, true, 0.3, 0.3, 3);
    aps.AddPathPoint(1*tiles, 2*tiles, true, 0.3, 0.3, 3);
    aps.EndPath();
    // Pickup mogo
    mogoMover.close();

    // Drive to the ring in the bottom left corner
    aps.AddPathPoint(2*tiles, 2*tiles, true, 0.3, 0.3, 3);
    aps.AddPathPoint(1*tiles, 1*tiles, false, 0.3, 0.3, 3);
    aps.EndPath();

    // Pick up the ring
    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    hooks.spinFor(-600, degrees);

    // Drive mogo into the bottom left corner
    aps.AddPathPoint(1*tiles, 1*tiles, true, 0.3, 0.3, 10, DegreesToRadians(45));
    aps.AddPathPoint(0.5*tiles, 0.5*tiles, true, 0.3, 0.3, 3);
    aps.EndPath();
    // Drop mogo in the bottom left corner
    mogoMover.open();


    // Drive to top left mogo
    aps.AddPathPoint(2*tiles, 1*tiles, false, 0.3, 0.3, 3);
    aps.AddPathPoint(1*tiles, 4*tiles, true, 0.3, 0.3, 3);
    aps.EndPath();
    // Pickup mogo
    mogoMover.close();

    // Drive to the ring in the top left corner
    aps.AddPathPoint(2*tiles, 4*tiles, true, 0.3, 0.3, 3);
    aps.AddPathPoint(1*tiles, 5*tiles, false, 0.3, 0.3, 3);
    aps.EndPath();

    // Pick up the ring
    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    hooks.spinFor(-600, degrees);

    // Drive mogo into the top left corner
    aps.AddPathPoint(1*tiles, 5*tiles, false, 0.3, 0.3, 10, DegreesToRadians(315));
    aps.AddPathPoint(0.5*tiles, 5.5*tiles, true, 0.3, 0.3, 3);
    aps.EndPath();
    // Drop mogo in the top left corner
    mogoMover.open();

}