#ifndef CLAW_H
#define CLAW_H

extern bool clawOpen;

void OpenClaw();
void CloseClaw();
void ToggleClaw();

void InitClaw();
void UserInitClaw();
void TickClaw();

#endif