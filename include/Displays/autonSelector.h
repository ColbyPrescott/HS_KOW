#ifndef AUTONOMOUS_SELECTOR_H
#define AUTONOMOUS_SELECTOR_H

#include "KOWGUI/kowgui.h"

extern KOWGUI::Group* autonSelectorUI;
extern void (*selectedAutonSequence)();

void InitAutonSelector();

#endif