#ifndef AUTONOMOUS_SELECTOR_H
#define AUTONOMOUS_SELECTOR_H

#include "KOWGUI/kowgui.h"

extern KOWGUI::Group* autonomousSelectorUI;
extern void (*selectedAutonSequence)();

void InitAutonomousSelector();

#endif