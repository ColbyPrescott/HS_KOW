#ifndef KOWGUI_KOWGUI_H
#define KOWGUI_KOWGUI_H

#include "KOWGUI/General/globalSystems.h"
#include "KOWGUI/General/color.h"
#include "KOWGUI/General/gui.h"

#include "KOWGUI/BaseNodes/baseNode.h"
#include "KOWGUI/BaseNodes/visibleBaseNode.h"
#include "KOWGUI/BaseNodes/interactableBaseNode.h"
#include "KOWGUI/BaseNodes/feedbackBaseNode.h"

#include "KOWGUI/Nodes/Basic/group.h"
#include "KOWGUI/Nodes/Basic/data.h"
#include "KOWGUI/Nodes/Basic/row.h"
#include "KOWGUI/Nodes/Basic/column.h"
#include "KOWGUI/Nodes/Visible/rectangle.h"
#include "KOWGUI/Nodes/Visible/roundedRectangle.h"
#include "KOWGUI/Nodes/Visible/circle.h"
#include "KOWGUI/Nodes/Visible/line.h"
#include "KOWGUI/Nodes/Visible/text.h"
#include "KOWGUI/Nodes/Visible/image.h"
#include "KOWGUI/Nodes/Interactable/clickable.h"
#include "KOWGUI/Nodes/Interactable/draggable.h"
#include "KOWGUI/Nodes/Interactable/toggleable.h"
#include "KOWGUI/Nodes/Feedback/selected.h"
#include "KOWGUI/Nodes/Feedback/focused.h"
#include "KOWGUI/Nodes/Feedback/activated.h"
#include "KOWGUI/Nodes/Feedback/looped.h"
#include "KOWGUI/Nodes/Feedback/Negated/nSelected.h"
#include "KOWGUI/Nodes/Feedback/Negated/nFocused.h"
#include "KOWGUI/Nodes/Feedback/Negated/nActivated.h"

#include "KOWGUI/Prefabs/keyboard.h"
#include "KOWGUI/Prefabs/graph.h"

#endif