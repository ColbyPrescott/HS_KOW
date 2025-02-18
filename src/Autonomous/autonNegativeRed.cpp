#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonNegativeRed() {
    storingRing = true;
    mogoMover.open();

    aps.SetPosition(13.5, 96);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 96, 10.5, 96, 16.59, 95.26, 19.96, 99.21, -40, -40);
    aps.AddPathSection(19.96, 99.21, 23.33, 103.16, 27.01, 107.56, 31.75, 107.37, -40, -50);
    aps.AddPathSection(31.75, 107.37, 36.49, 107.18, 47.88, 96.98, 47.51, 96.77, -50, -30);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(47.51, 96.77, 47.14, 96.56, 40.37, 102.19, 41.77, 109.32, 60, 60);
    aps.AddPathSection(41.77, 109.32, 43.17, 116.45, 48.75, 124.46, 49.16, 124.35, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(49.16, 124.35, 49.57, 124.24, 43.61, 105.54, 43.61, 105.54, -40, -60);
    aps.AddPathSection(43.61, 105.54, 43.61, 105.54, 38.3, 93.02, 37.89, 92.62, -60, -30);
    aps.AddPathSection(37.89, 92.62, 37.48, 92.22, 48.81, 95.28, 55.96, 87.43, 40, 60);
    aps.EndPath();
}