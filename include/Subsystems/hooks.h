#ifndef HOOKS_H
#define HOOKS_H

// List of motor encoder values where the reset hook is at significant positions
enum class HookWaypointPositions {
    grabbedRing = 360, // Reset hook went around the first gear and is ready to speed up
    waitForMogo = 800, // Reset hook is at a position to store the ring, waiting to deposit it onto a mogo
    depositRingOnMogo = 1379, // Reset hook went around the top of the hook mechanism and is now completely horizontal
    waitForRing = 2270  // Reset hook is a little above the tiles, almost about to pick up a ring
};
// Abbreviate name because it's long and repeated many times
#define HWPs HookWaypointPositions

extern bool storingRing;

void HooksSpinForwardTo(double targetDegrees);
void MoveClosestHookToWaypoint(HWPs hook, HWPs waypoint);

void TriggerAutoHooks();

void InitHooks();
void UserInitHooks();
void TickHooks();

#endif