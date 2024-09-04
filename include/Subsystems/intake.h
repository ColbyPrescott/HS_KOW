#ifndef INTAKE_H
#define INTAKE_H

// List of motor encoder values where the reset hook is at significant positions
enum class IntakeWaypointPositions {
    waitForMogo = 1800, // Reset hook is at a position to store the ring, waiting to deposit it onto a mogo
    depositRing = 2630, // Reset hook went around the top of the intake mechanism and is now completely horizontal
    waitForRing = 4600  // Reset hook is a little above the tiles, almost about to pick up a ring
};
// Abbreviate name because it's long and repeated many times
#define IWPs IntakeWaypointPositions

extern bool storingRing;

void MoveClosestHookToWaypoint(IWPs hook, IWPs waypoint);
void TriggerIntake();

void InitIntake();
void UserInitIntake();
void TickIntake();

#endif