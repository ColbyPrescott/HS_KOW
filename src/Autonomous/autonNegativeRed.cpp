#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":96},"p1":{"x":10.5,"y":96},"p2":{"x":16.59,"y":95.26},"p3":{"x":19.96,"y":99.21},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":19.96,"y":99.21},"p1":{"x":23.33,"y":103.16},"p2":{"x":27.01,"y":107.56},"p3":{"x":31.75,"y":107.37},"startSpeed":-40,"endSpeed":-50,"code":""},{"p0":{"x":31.75,"y":107.37},"p1":{"x":36.49,"y":107.18},"p2":{"x":47.88,"y":96.98},"p3":{"x":47.51,"y":96.77},"startSpeed":-50,"endSpeed":-30,"code":"mogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":47.51,"y":96.77},"p1":{"x":47.14,"y":96.56},"p2":{"x":43.74,"y":101.6},"p3":{"x":45.14,"y":108.73},"startSpeed":60,"endSpeed":60,"code":""},{"p0":{"x":45.14,"y":108.73},"p1":{"x":46.54,"y":115.86},"p2":{"x":47.76,"y":123.47},"p3":{"x":48.17,"y":123.36},"startSpeed":60,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":48.17,"y":123.36},"p1":{"x":48.58,"y":123.25},"p2":{"x":43.61,"y":105.54},"p3":{"x":43.61,"y":105.54},"startSpeed":-40,"endSpeed":-60,"code":""},{"p0":{"x":43.61,"y":105.54},"p1":{"x":43.61,"y":105.54},"p2":{"x":38.3,"y":93.02},"p3":{"x":37.89,"y":92.62},"startSpeed":-60,"endSpeed":-30,"code":""},{"p0":{"x":37.89,"y":92.62},"p1":{"x":37.48,"y":92.22},"p2":{"x":47.42,"y":96.07},"p3":{"x":54.57,"y":88.22},"startSpeed":40,"endSpeed":60,"code":""}]

*/

void AutonNegativeRed() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 96);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 96, 10.5, 96, 16.59, 95.26, 19.96, 99.21, -40, -40);
    aps.AddPathSection(19.96, 99.21, 23.33, 103.16, 27.01, 107.56, 31.75, 107.37, -40, -50);
    aps.AddPathSection(31.75, 107.37, 36.49, 107.18, 47.88, 96.98, 47.51, 96.77, -50, -30);
    aps.EndPath();
    // ExtendNeutralFlip();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(47.51, 96.77, 47.14, 96.56, 40.37, 102.19, 41.77, 109.32, 60, 60);
    aps.AddPathSection(41.77, 109.32, 43.17, 116.45, 48.75, 124.46, 49.16, 124.35, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    // RetractNeutralFlip();
    aps.AddPathSection(49.16, 124.35, 49.57, 124.24, 43.61, 105.54, 43.61, 105.54, -40, -60);
    aps.AddPathSection(43.61, 105.54, 43.61, 105.54, 38.3, 93.02, 37.89, 92.62, -60, -30);
    aps.AddPathSection(37.89, 92.62, 37.48, 92.22, 48.81, 95.28, 55.96, 87.43, 40, 60);
    aps.EndPath();
}