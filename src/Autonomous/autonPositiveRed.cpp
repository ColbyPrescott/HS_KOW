#include "vex.h"

#include "Backend/utilityMath.h"
#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":48},"p1":{"x":10.5,"y":48},"p2":{"x":16.39,"y":49.17},"p3":{"x":19.96,"y":44.79},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":19.96,"y":44.79},"p1":{"x":23.53,"y":40.41},"p2":{"x":29.39,"y":37.22},"p3":{"x":34.13,"y":37.43},"startSpeed":-40,"endSpeed":-50,"code":""},{"p0":{"x":34.13,"y":37.43},"p1":{"x":38.87,"y":37.64},"p2":{"x":45.7,"y":45.85},"p3":{"x":45.33,"y":45.64},"startSpeed":-50,"endSpeed":-30,"code":"ExtendNeutralFlip();\nmogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":45.33,"y":45.64},"p1":{"x":44.96,"y":45.43},"p2":{"x":41.36,"y":43.81},"p3":{"x":41.96,"y":36.26},"startSpeed":60,"endSpeed":60,"code":""},{"p0":{"x":41.96,"y":36.26},"p1":{"x":42.56,"y":28.71},"p2":{"x":48.75,"y":20.18},"p3":{"x":49.16,"y":20.07},"startSpeed":60,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":49.16,"y":20.07},"p1":{"x":49.57,"y":19.96},"p2":{"x":44.05,"y":29.18},"p3":{"x":44.64,"y":37.31},"startSpeed":-40,"endSpeed":-60,"code":""},{"p0":{"x":44.64,"y":37.31},"p1":{"x":45.23,"y":45.44},"p2":{"x":48.61,"y":52.13},"p3":{"x":55.96,"y":58.36},"startSpeed":-40,"endSpeed":-60,"code":""}]

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
    ExtendNeutralFlip();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(45.33, 45.64, 44.96, 45.43, 41.36, 43.81, 41.96, 36.26, 60, 60);
    aps.AddPathSection(41.96, 36.26, 42.56, 28.71, 48.75, 20.18, 49.16, 20.07, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(49.16, 20.07, 49.57, 19.96, 44.05, 29.18, 44.64, 37.31, -40, -60);
    aps.AddPathSection(44.64, 37.31, 45.23, 45.44, 48.61, 52.13, 55.96, 58.36, -40, -60);
    aps.EndPath();
}