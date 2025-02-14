#ifndef KOWGUI_KEYBOARD_PREFAB_H
#define KOWGUI_KEYBOARD_PREFAB_H

#include "KOWGUI/Nodes/Basic/group.h"
#include "KOWGUI/General/color.h"

#include <string>

namespace KOWGUI {
    namespace Keyboard {

        Group* CreateKeyboard(std::shared_ptr<Color> customBackgroundColor = nullptr, std::shared_ptr<Color> customButtonNFocusedColor = nullptr, std::shared_ptr<Color> customButtonFocusedColor = nullptr, std::shared_ptr<Color> customHighlightColor = nullptr);
        Group* CreateNumpad(int x = 10, int y = 10, int width = 100, int height = 150, bool movable = true, bool resizable = false, std::shared_ptr<Color> customWindowBarColor = nullptr, std::shared_ptr<Color> customButtonNFocusedColor = nullptr, std::shared_ptr<Color> customButtonFocusedColor = nullptr, std::shared_ptr<Color> customHighlightColor = nullptr);

        void Open(Group* keyboard, std::string& str);
        void Open(Group* keyboard, std::string startStr, void (*closeCallback)(std::string));
        void Open(Group* numpad, int startNum, void (*updateCallback)(int), bool liveUpdate = false);
        void Open(Group* numpad, double startNum, void (*updateCallback)(double), bool liveUpdate = false);

    }
}

#endif