#ifndef HOOKS_H
#define HOOKS_H

// List of motor encoder values where the reset hook is at significant positions
enum class HookWaypointPositions {
    waitForMogo = 1800, // Reset hook is at a position to store the ring, waiting to deposit it onto a mogo
    depositRing = 2630, // Reset hook went around the top of the intake mechanism and is now completely horizontal
    waitForRing = 4600  // Reset hook is a little above the tiles, almost about to pick up a ring
};
// Abbreviate name because it's long and repeated many times
#define IWPs HookWaypointPositions

extern bool storingRing;

void MoveClosestHookToWaypoint(IWPs hook, IWPs waypoint);

void MoveStoredRingToClaw();
void MoveStoredRingToMogo();

void InitHooks();
void UserInitHooks();
void TickHooks();

#endif