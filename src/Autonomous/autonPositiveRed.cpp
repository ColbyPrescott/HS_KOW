#include "vex.h"

#include "Backend/utilityMath.h"
#include "Subsystems/hooks.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":48},"p1":{"x":10.5,"y":48},"p2":{"x":16.39,"y":49.17},"p3":{"x":19.96,"y":44.79},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":19.96,"y":44.79},"p1":{"x":23.53,"y":40.41},"p2":{"x":29.39,"y":37.22},"p3":{"x":34.13,"y":37.43},"startSpeed":-40,"endSpeed":-50,"code":""},{"p0":{"x":34.13,"y":37.43},"p1":{"x":38.87,"y":37.64},"p2":{"x":45.7,"y":45.85},"p3":{"x":45.33,"y":45.64},"startSpeed":-50,"endSpeed":-30,"code":"mogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":45.33,"y":45.64},"p1":{"x":44.96,"y":45.43},"p2":{"x":44.54,"y":42.82},"p3":{"x":45.14,"y":35.27},"startSpeed":60,"endSpeed":60,"code":""},{"p0":{"x":45.14,"y":35.27},"p1":{"x":45.74,"y":27.72},"p2":{"x":47.76,"y":20.38},"p3":{"x":48.17,"y":20.27},"startSpeed":60,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":48.17,"y":20.27},"p1":{"x":48.58,"y":20.16},"p2":{"x":43.61,"y":38.46},"p3":{"x":43.61,"y":38.46},"startSpeed":-40,"endSpeed":-60,"code":""},{"p0":{"x":43.61,"y":38.46},"p1":{"x":43.61,"y":38.46},"p2":{"x":38.3,"y":51.78},"p3":{"x":37.89,"y":51.38},"startSpeed":-60,"endSpeed":-30,"code":""},{"p0":{"x":37.89,"y":51.38},"p1":{"x":37.48,"y":50.98},"p2":{"x":47.22,"y":49.55},"p3":{"x":54.57,"y":55.78},"startSpeed":40,"endSpeed":60,"code":""}]

*/

void AutonPositiveRed() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 48);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 48, 10.5, 48, 16.39, 49.17, 19.96, 44.79, -40, -40);
    aps.AddPathSection(19.96, 44.79, 23.53, 40.41, 29.39, 37.22, 34.13, 37.43, -40, -50);
    aps.AddPathSection(34.13, 37.43, 38.87, 37.64, 45.7, 45.85, 45.33, 45.64, -50, -30);
    aps.EndPath();
    // ExtendNeutralFlip();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(45.33, 45.64, 44.96, 45.43, 44.54, 42.82, 45.14, 35.27, 60, 60);
    aps.AddPathSection(45.14, 35.27, 45.74, 27.72, 47.76, 20.38, 48.17, 20.27, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    // RetractNeutralFlip();
    aps.AddPathSection(48.17, 20.27, 48.58, 20.16, 43.61, 38.46, 43.61, 38.46, -40, -60);
    aps.AddPathSection(43.61, 38.46, 43.61, 38.46, 38.3, 51.78, 37.89, 51.38, -60, -30);
    aps.AddPathSection(37.89, 51.38, 37.48, 50.98, 47.22, 49.55, 54.57, 55.78, 40, 60);
    aps.EndPath();
}