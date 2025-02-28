#include "vex.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

void AutonPositiveBlueBasic() {
    storingRing = true;

    basicDrive.setStopping(brake);

    // Prepare hooks for ring
    task([](){MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForRing); return 0;});
    // Start picking up ring
    task([](){task::sleep(1200); 
        ExtendNeutralFlip();
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::grabbedRing);
    return 0;});
    // Drive towards ring
    basicDrive.driveFor(47, inches, 180, rpm, true);
    wait(1, seconds);
    // Drive towards mogo on line
    basicDrive.turnFor(50, degrees, 100, rpm, true);
    basicDrive.driveFor(1.4, inches, 100, rpm, true);
    // Grab mogo
    wing.set(true);
    task([](){task::sleep(1000);
        wing.set(false);
    return 0;});
    wait(0.8, seconds);
    // Drive away from line
    basicDrive.driveFor(-5, inches, 180, rpm, true);
    // Pickup mogo
    // basicDrive.turnFor(102, degrees, 180, rpm, true);
    basicInertialDrive.setTurnVelocityMin(20.0);
    basicInertialDrive.turnToHeading(-42, degrees, 180, rpm, true);
    mogoMover.open();
    basicDrive.driveFor(-35, inches, 100, rpm, true);
    mogoMover.close();

    // Put all the stored rings onto the mogo
    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);

    // Drive to touch the ladder
    basicDrive.turnFor(90, degrees, 180, rpm, true);
    basicDrive.driveFor(10, inches, 180, rpm, false);

    // Might as well try putting the stored rings onto the mogo again
    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
}