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
    arm.spinToPosition(2166, degrees, 100, rpm, false);
    clawPivot.spinToPosition(-511, degrees, 20, rpm, false);

    // 2 Drive over to the mogo in the top left and grab it
    mogoMover.open();
    aps.AddPathPoint(1.25*tiles, 4*tiles + 8, true, 0.3, 0.3, 5); // Arc to help get better angle
    aps.AddPathPoint(2*tiles, 4*tiles, true, 0.3, 0.3, 2);
    aps.EndPath();
    mogoMover.close();

    // 2 Deposit preload onto held mogo
    vex::task([](){TriggerAutoHooks(); return 0;});
    wait(1, seconds);

    // 3 Drive into a stack of rings and pick up the lower red one onto the held mogo
    aps.AddPathPoint(2*tiles, 5*tiles, false, 0.3, 0.3, 2);
    aps.EndPath();
    vex::task([](){TriggerAutoHooks(); return 0;});
    wait(1, seconds);

    // return; // DEBUG break point

    // 4 Lower and open claw
    arm.spinToPosition(0, degrees, 100, rpm, true); // Arm needs to go first to stay in size
    clawPivot.spinToPosition(-600, degrees, 100, rpm, true);
    OpenClaw();

    // 4 Drive into stack rings next to the autonomous line and pick up a bottom red one
    aps.AddPathPoint(3*tiles - 8, 5*tiles + 3, false, 0.3, 0.3, 2);
    aps.EndPath();
    CloseClaw();

    // Somehow get the ring from the claw onto the held mogo

    // Move claw and arm to be off of the wheels
    clawPivot.spinToPosition(-381, degrees, 20, rpm, true);
    arm.spinToPosition(2166, degrees, 20, rpm, false);

    // Drive to touch ladder
    aps.AddPathPoint(2.5*tiles, 3.5*tiles, true, 0.3, 0.3, 3);
    aps.EndPath();
}

// void AutonNegativeRed() {
    // aps.SetPosition(14, 96);
    // aps.SetRotation(DegreesToRadians(270));
    // intake.spinToPosition(600, degrees, false);
    // storingRing = true;
    // mogoMover.open();

    // // Give drivetrain control to the APS
    // aps.SetDriving(true);

    // // Drive up to stack of rings
    // aps.AddPathPoint(19, 81, false, 0.3, 0.3, 1);
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
    // aps.AddPathPoint(15, 90, true, 0.3, 0.3, 4);
    // // Push blue rings out of the way
    // aps.AddPathPoint(19, 63, false, 0.3, 0.3, 1);
    // // Back up into red alliance stake
    // aps.AddPathPoint(8, 72, true, 0.2, 0.3, 3, DegreesToRadians(0)); 
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
    // // aps.AddPathPoint(aps.GetX() - 5, aps.GetY(), true, 0.2, 0.3, 3); // Push into alliance stake
    // aps.AddPathPoint(48, 96, true, 0.3, 0.3, 1);
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
    // aps.AddPathPoint(35, 95, false, 0.3, 0.3, 5);
    // aps.AddPathPoint(58, 86, true, 0.3, 0.3, 1);
    // aps.EndPath();

// }