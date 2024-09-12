#include "vex.h"

#include "Subsystems/intake.h"
#include "Backend/utilityMath.h"

using namespace vex;

void AutonTopRed() {
    aps.SetPosition(14, 96);
    aps.SetRotation(DegreesToRadians(270));
    intake.spinToPosition(600, degrees, false);
    storingRing = true;
    mogoMover.open();

    // Give drivetrain control to the APS
    aps.SetDriving(true);

    // Drive up to stack of rings
    aps.AddPathPoint(19, 81, false, 0.3, 0.3, 1);
    aps.EndPath();
    // Clamp down onto the red ring that's at the top of the stack
    intake.spinToPosition(-50, degrees, false);
    wait(0.5, seconds);
    // Back up to pull in red ring and line up for pushing blue rings
    aps.AddPathPoint(15, 90, true, 0.3, 0.3, 4);
    // Push blue rings out of the way
    aps.AddPathPoint(19, 63, false, 0.3, 0.3, 1);
    // Back up into red alliance stake
    aps.AddPathPoint(8, 72, true, 0.2, 0.3, 3, DegreesToRadians(0)); 
    aps.EndPath();
    // Put red pre load onto alliance stake
    MoveClosestHookToWaypoint(IWPs::waitForMogo, IWPs::depositRing);
    // Wait for red ring to get onto red alliance stake
    wait(0.5, seconds);
    // Back up hook to make sure it isn't caught while driving away
    intake.spinFor(-400, degrees, true);
    intake.spinFor(600, degrees, true);
    intake.spinFor(-600, degrees, true);

    // While driving, move the stored ring closer to the top of the intake
    vex::task([](){
        wait(0.5, seconds);
        MoveClosestHookToWaypoint(IWPs::waitForMogo, IWPs::waitForMogo);
        return 0;
    });

    // Drive to and pick up mogo
    aps.AddPathPoint(aps.GetX() - 5, aps.GetY(), true, 0.2, 0.3, 3); // Push into alliance stake
    aps.AddPathPoint(48, 96, true, 0.3, 0.3, 1);
    aps.EndPath();
    mogoMover.close();

    // Put ring onto mogo
    MoveClosestHookToWaypoint(IWPs::waitForMogo, IWPs::depositRing);
    wait(1, seconds);

    // Drop mogo
    mogoMover.open();

    // // Drive to stack
    // aps.AddPathPoint(48, 120, false, 0.3, 0.3, 1);
    // aps.EndPath();

    // Drive to ladder
    aps.AddPathPoint(35, 95, false, 0.3, 0.3, 5);
    aps.AddPathPoint(58, 86, true, 0.3, 0.3, 1);
    aps.EndPath();

}