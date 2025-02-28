#include "vex.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

void AutonPositiveRed() {
    storingRing = true;

    // Prepare hooks for ring
    task([](){MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForRing); return 0;});
    // Start picking up ring
    task([](){task::sleep(1200); 
        ExtendNeutralFlip();
        MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::grabbedRing);
    return 0;});

    aps.SetPosition(13.5, 48);
    aps.SetRotation(0);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 48, 16.5, 48, 29.99, 32.27, 34.33, 28.12, 100, 100);
    aps.AddPathSection(34.33, 28.12, 38.67, 23.97, 44.86, 23.12, 49.62, 22.92, 100, 40);
    aps.AddPathSection(49.62, 22.92, 54.38, 22.72, 65.33, 24.14, 64.92, 24.05, 50, 20);
    aps.EndPath();
    
    // Grab mogo on auton line
    wing.set(true);
    task([](){task::sleep(1000);
        wing.set(false);
    return 0;});
    
    // Grab mogo near ladder
    mogoMover.open();
    aps.AddPathSection(64.92, 24.05, 64.51, 23.96, 49.03, 26.36, 48.65, 32.3, -40, -40);
    aps.AddPathSection(48.65, 32.3, 48.27, 38.24, 47.05, 46.37, 47.72, 46.28, -40, -40);
    aps.EndPath();
    mogoMover.close();
    
    // Put all the stored rings onto the mogo
    MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
}