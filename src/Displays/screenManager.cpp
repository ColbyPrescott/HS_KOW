#include "Displays/screenManager.h"

#include "vex.h"
#include "KOWGUI/kowgui.h"

#include <vector>

using namespace KOWGUI;

// Struct with each screen
Screens screens;
// Vector with pointers to every screen node
std::vector<Group*> screensVector;

void InitScreens() {
    // Macro function to put each screen into screensVector, gui.root, and call the UI initialization function
    void (*InitScreen)(Group*, void (*)()) = [](Group* screenNode, void (*initScreenFunc)()){
        screensVector.push_back(screenNode);
        gui.root->AddChild(screenNode);
        initScreenFunc();
    };

    InitScreen(screens.autonSelector, InitScreenAutonSelector);
}

// Show one screen and hide all others
void ShowScreen(Group* screen) {
    // Disable each screen
    for(int i = 0; i < screensVector.size(); i++) screensVector[i]->SetDisabled(true);
    // Enable the one wanted
    screen->SetDisabled(false);
}