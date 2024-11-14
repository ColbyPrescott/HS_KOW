#include "vex.h"

#include "Backend/utilityMath.h"

using namespace vex;

void AutonNegativeBlue() {
    // aps.SetPosition(MirrorX(14), 96);
    // aps.SetRotation(DegreesToRadians(270));
    // intake.spinToPosition(600, degrees, false);
    // storingRing = true;
    // mogoMover.open();

    // // Give drivetrain control to the APS
    // aps.SetDriving(true);

    // // Drive up to stack of rings
    // aps.AddPathPoint(MirrorX(19), 81, false, 0.3, 0.3, 1);
    // aps.EndPath();
    // // Clamp down onto the red ring that's at the top of the stack
    // intake.spinToPosition(-50, degrees, false);
    // wait(0.5, seconds);

    // // While driving, move the stored ring closer to the top of the intake
    // vex::task([](){
    //     wait(1, seconds);
    //     MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::waitForMogo);
    //     return 0;
    // });

    // // Back up to pull in red ring and line up for pushing blue rings
    // aps.AddPathPoint(MirrorX(15), 90, true, 0.3, 0.3, 4);
    // // Push blue rings out of the way
    // aps.AddPathPoint(MirrorX(19), 63, false, 0.3, 0.3, 1);
    // // Back up into red alliance stake
    // aps.AddPathPoint(MirrorX(8), 72, true, 0.2, 0.3, 3, DegreesToRadians(180)); // TODO MirrorDegrees(...)
    // aps.EndPath();
    // // Put red pre load onto alliance stake
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRing);
    // // Wait for red ring to get onto red alliance stake
    // wait(0.5, seconds);
    // // Back up hook to make sure it isn't caught while driving away
    // intake.spinFor(-400, degrees, true);
    // intake.spinFor(600, degrees, true);
    // intake.spinFor(-600, degrees, true);

    // // While driving, move the stored ring closer to the top of the intake
    // vex::task([](){
    //     wait(0.5, seconds);
    //     MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::waitForMogo);
    //     return 0;
    // });

    // // Drive to and pick up mogo
    // // aps.AddPathPoint(MirrorX(MirrorX(aps.GetX()) - 5), aps.GetY(), true, 0.2, 0.3, 3); // Push into alliance stake
    // aps.AddPathPoint(MirrorX(48), 96, true, 0.3, 0.3, 1);
    // aps.EndPath();
    // mogoMover.close();

    // // Put ring onto mogo
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRing);
    // wait(1, seconds);

    // // Drop mogo
    // mogoMover.open();

    // // // Drive to stack
    // // aps.AddPathPoint(48, 120, false, 0.3, 0.3, 1);
    // // aps.EndPath();

    // // Drive to ladder
    // aps.AddPathPoint(MirrorX(35), 95, false, 0.3, 0.3, 5);
    // aps.AddPathPoint(MirrorX(58), 86, true, 0.3, 0.3, 1);
    // aps.EndPath();

}