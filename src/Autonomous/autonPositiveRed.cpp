#include "vex.h"

#include "Backend/utilityMath.h"
#include "Subsystems/hooks.h"

using namespace vex;

void AutonPositiveRed() {
    storingRing = true;
    mogoMover.open();

    aps.SetPosition(13.5, 48);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 48, 10.5, 48, 16.39, 49.17, 19.96, 44.79, -40, -40);
    aps.AddPathSection(19.96, 44.79, 23.53, 40.41, 29.39, 37.22, 34.13, 37.43, -40, -50);
    aps.AddPathSection(34.13, 37.43, 38.87, 37.64, 45.7, 45.85, 45.33, 45.64, -50, -30);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(45.33, 45.64, 44.96, 45.43, 44.54, 42.82, 45.14, 35.27, 60, 60);
    aps.AddPathSection(45.14, 35.27, 45.74, 27.72, 47.76, 20.38, 48.17, 20.27, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(48.17, 20.27, 48.58, 20.16, 43.61, 38.46, 43.61, 38.46, -40, -60);
    aps.AddPathSection(43.61, 38.46, 43.61, 38.46, 38.3, 51.78, 37.89, 51.38, -60, -30);
    aps.AddPathSection(37.89, 51.38, 37.48, 50.98, 47.22, 49.55, 54.57, 55.78, 40, 60);
    aps.EndPath();
}