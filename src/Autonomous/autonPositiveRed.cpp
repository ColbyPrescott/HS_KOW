#include "vex.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

void AutonPositiveRed() {
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
    basicDrive.turnFor(-50, degrees, 100, rpm, true);
    basicDrive.driveFor(1.8, inches, 100, rpm, true);
    // Grab mogo
    wing.set(true);
    task([](){task::sleep(1000);
        wing.set(false);
    return 0;});
    wait(0.8, seconds);
    // Drive away from line
    basicDrive.driveFor(-3, inches, 180, rpm, true);
    basicDrive.turnFor(100, degrees, 180, rpm, true);
    mogoMover.open();
    basicDrive.driveFor(-35, inches, 100, rpm, true);
    mogoMover.close();

    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);

    basicDrive.turnFor(-135, degrees, 180, rpm, true);
    basicDrive.driveFor(10, inches, 180, rpm, false);
}








// #include "vex.h"

// #include "Subsystems/hooks.h"

// using namespace vex;

// void AutonPositiveRed() {
//     storingRing = true;
//     task([](){MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForRing); return 0;});

//     aps.SetPosition(13.5, 48);
//     aps.SetRotation(3.141592653589793);
//     aps.SetDriving(true);
//     aps.AddPathSection(13.5, 48, 10.5, 48, 29.99, 32.27, 34.33, 28.12, 100, 100);
//     aps.AddPathSection(34.33, 28.12, 38.67, 23.97, 44.86, 23.12, 49.62, 22.92, 100, 40);
//     aps.EndPath();
//     MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::grabbedRing);
//     aps.AddPathSection(49.62, 22.92, 54.38, 22.72, 65.33, 24.14, 64.92, 24.05, 50, 20);
//     aps.EndPath();
//     wing.set(true);
//     aps.AddPathSection(64.92, 24.05, 64.51, 23.96, 49.03, 26.36, 48.65, 32.3, -40, -40);
//     aps.AddPathSection(48.65, 32.3, 48.27, 38.24, 47.05, 46.37, 47.72, 46.28, -40, -40);
//     aps.EndPath();
//     mogoMover.close();
//     TriggerAutoHooks();
//     mogoMover.open();
//     aps.AddPathSection(47.72, 46.28, 50.69, 45.88, 8.49, 53.01, 7.9, 64.89, 100, 60);
//     aps.AddPathSection(7.9, 64.89, 7.31, 76.77, 31.65, 71.63, 32.05, 71.83, 40, 40);
//     aps.EndPath();
//     TriggerAutoHooks();
//     aps.AddPathSection(32.05, 71.83, 32.45, 72.03, 9.78, 71.63, 9.95, 71.83, -40, -20);
//     aps.EndPath();
//     TriggerAutoHooks();
//     aps.AddPathSection(9.95, 71.83, 10.12, 72.03, 39.64, 71.04, 43.41, 71.24, 40, 40);
//     aps.EndPath();
// }