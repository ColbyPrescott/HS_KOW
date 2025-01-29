#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonSkills() {
    // // 1 Setup robot next to alliance stake facing away from wall
    // aps.SetPosition(8, 72);
    // aps.SetRotation(DegreesToRadians(0));
    // storingRing = true;
    // mogoMover.open();

    // // 1 Give drivetrain control to the APS
    // aps.SetDriving(true);

    // // 2 Put preload onto alliance stake
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 3 Drive to bottom left mogo
    // aps.AddPathPoint(1.5*tiles, 3.5*tiles, false, 0.3, 0.3, 3);
    // aps.AddPathPoint(1*tiles, 3*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 2*tiles - 5, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 3 Pickup mogo
    // mogoMover.close();

    // // 4 Drive to the ring in the bottom left corner
    // aps.AddPathPoint(2*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 1*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 4 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 5 Drive mogo into the bottom left corner
    // aps.AddPathPoint(1*tiles, 1*tiles, true, 0.35, 0.35, 10, DegreesToRadians(45));
    // aps.AddPathPoint(0.5*tiles, 0.5*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 5 Drop mogo in the bottom left corner
    // mogoMover.open();


    // // 6 Drive to ring in the bottom left quadrant
    // aps.AddPathPoint(2*tiles, 1*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 6 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForMogo);

    // // 7 Drive to top left mogo
    // aps.AddPathPoint(1*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 4*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 7 Pickup mogo
    // mogoMover.close();
    // // 7 Deposit stored ring onto mogo
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 8 Drive to the ring in the top left corner
    // aps.AddPathPoint(2*tiles, 4*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 5*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 8 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 9 Drive mogo into the top left corner
    // aps.AddPathPoint(1*tiles, 5*tiles, false, 0.35, 0.35, 10, DegreesToRadians(315));
    // aps.AddPathPoint(0.5*tiles, 5.5*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 9 Drop mogo in the top left corner
    // mogoMover.open();

}