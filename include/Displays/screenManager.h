#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "KOWGUI/Nodes/Basic/group.h"

struct Screens {
    KOWGUI::Group* autonSelector = new KOWGUI::Group;
};
extern Screens screens;

void InitScreenAutonSelector();


void InitScreens();

void ShowScreen(KOWGUI::Group* screen);

#endif