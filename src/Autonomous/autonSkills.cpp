#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":72},"p1":{"x":10.5,"y":72},"p2":{"x":19.17,"y":73.68},"p3":{"x":21.95,"y":67.14},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":21.95,"y":67.14},"p1":{"x":24.73,"y":60.6},"p2":{"x":23.47,"y":57.34},"p3":{"x":23.7,"y":49.21},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.close();"},{"p0":{"x":23.7,"y":49.21},"p1":{"x":23.78,"y":46.21},"p2":{"x":24.14,"y":59.1},"p3":{"x":32.47,"y":58.7},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":32.47,"y":58.7},"p1":{"x":40.8,"y":58.3},"p2":{"x":45.29,"y":49.17},"p3":{"x":50.13,"y":44.98},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":50.13,"y":44.98},"p1":{"x":52.4,"y":43.02},"p2":{"x":65.44,"y":37.97},"p3":{"x":65.44,"y":33.01},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":65.44,"y":33.01},"p1":{"x":65.44,"y":28.05},"p2":{"x":58.25,"y":24.78},"p3":{"x":47.02,"y":25.21},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":47.02,"y":25.21},"p1":{"x":35.79,"y":25.64},"p2":{"x":22.36,"y":26.95},"p3":{"x":21.94,"y":26.82},"startSpeed":100,"endSpeed":100,"code":"TriggerAutoHooks();"},{"p0":{"x":21.94,"y":26.82},"p1":{"x":21.52,"y":26.69},"p2":{"x":26.48,"y":27.55},"p3":{"x":34.41,"y":20.21},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":34.41,"y":20.21},"p1":{"x":42.34,"y":12.87},"p2":{"x":46.79,"y":13.49},"p3":{"x":47.06,"y":13.35},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":47.06,"y":13.35},"p1":{"x":47.33,"y":13.21},"p2":{"x":22.23,"y":12.49},"p3":{"x":21.9,"y":12.55},"startSpeed":100,"endSpeed":100,"code":"TriggerAutoHooks();"},{"p0":{"x":21.9,"y":12.55},"p1":{"x":18.95,"y":13.09},"p2":{"x":61.42,"y":15.42},"p3":{"x":51.73,"y":31.22},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":51.73,"y":31.22},"p1":{"x":42.04,"y":47.02},"p2":{"x":17,"y":17},"p3":{"x":13,"y":13},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.open();"},{"p0":{"x":13,"y":13},"p1":{"x":10.88,"y":10.88},"p2":{"x":26.15,"y":27.06},"p3":{"x":26.35,"y":45.11},"startSpeed":100,"endSpeed":100,"code":""},{"p0":{"x":26.35,"y":45.11},"p1":{"x":26.55,"y":63.16},"p2":{"x":28.41,"y":69.6},"p3":{"x":30.98,"y":77.73},"startSpeed":100,"endSpeed":100,"code":""},{"p0":{"x":30.98,"y":77.73},"p1":{"x":33.55,"y":85.86},"p2":{"x":52.93,"y":102.73},"p3":{"x":53.65,"y":102.85},"startSpeed":100,"endSpeed":100,"code":"TriggerAutoHooks();"},{"p0":{"x":53.65,"y":102.85},"p1":{"x":54.37,"y":102.97},"p2":{"x":44.04,"y":92.75},"p3":{"x":40.07,"y":91.16},"startSpeed":100,"endSpeed":100,"code":""},{"p0":{"x":40.07,"y":91.16},"p1":{"x":36.1,"y":89.57},"p2":{"x":30.72,"y":90.8},"p3":{"x":25.09,"y":94.69},"startSpeed":100,"endSpeed":100,"code":""}]

*/

void AutonSkills() {
    // // 1 Setup robot next to alliance stake facing away from wall
    // aps.SetPosition(8, 72);
    // aps.SetRotation(DegreesToRadians(0));
    // storingRing = true;
    // mogoMover.open();

    // // 1 Give drivetrain control to the APS
    // aps.SetDriving(true);

    // // 2 Put preload onto alliance stake
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 3 Drive to bottom left mogo
    // aps.AddPathPoint(1.5*tiles, 3.5*tiles, false, 0.3, 0.3, 3);
    // aps.AddPathPoint(1*tiles, 3*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 2*tiles - 5, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 3 Pickup mogo
    // mogoMover.close();

    // // 4 Drive to the ring in the bottom left corner
    // aps.AddPathPoint(2*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 1*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 4 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 5 Drive mogo into the bottom left corner
    // aps.AddPathPoint(1*tiles, 1*tiles, true, 0.35, 0.35, 10, DegreesToRadians(45));
    // aps.AddPathPoint(0.5*tiles, 0.5*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 5 Drop mogo in the bottom left corner
    // mogoMover.open();


    // // 6 Drive to ring in the bottom left quadrant
    // aps.AddPathPoint(2*tiles, 1*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 6 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::waitForMogo);

    // // 7 Drive to top left mogo
    // aps.AddPathPoint(1*tiles, 2*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 4*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 7 Pickup mogo
    // mogoMover.close();
    // // 7 Deposit stored ring onto mogo
    // MoveClosestHookToWaypoint(HWPs::waitForMogo, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 8 Drive to the ring in the top left corner
    // aps.AddPathPoint(2*tiles, 4*tiles, true, 0.35, 0.35, 3);
    // aps.AddPathPoint(1*tiles, 5*tiles, false, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 8 Pick up the ring
    // MoveClosestHookToWaypoint(HWPs::waitForRing, HWPs::depositRingOnMogo);
    // hooks.spinFor(-300, degrees);

    // // 9 Drive mogo into the top left corner
    // aps.AddPathPoint(1*tiles, 5*tiles, false, 0.35, 0.35, 10, DegreesToRadians(315));
    // aps.AddPathPoint(0.5*tiles, 5.5*tiles, true, 0.35, 0.35, 3);
    // aps.EndPath();
    // // 9 Drop mogo in the top left corner
    // mogoMover.open();

}