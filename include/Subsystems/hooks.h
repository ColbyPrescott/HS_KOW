#ifndef HOOKS_H
#define HOOKS_H

// List of motor encoder values where the reset hook is at significant positions
enum class HookWaypointPositions {
    aboveTrapdoor = 1100, // Reset hook is holding a ring high enough for the trapdoor to fall back down
    despositMogo = 1456, // Reset hook went around the top of the hook mechanism and is now completely horizontal
    belowStoredRing = 2600, // Reset hook is about to pick up the stored ring
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