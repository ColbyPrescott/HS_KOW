#include "vex.h"

#include "Autonomous/autonSequences.h"
#include "Displays/screenManager.h"

using namespace KOWGUI;

// Current auton function to run when autonomous starts
void (*selectedAutonSequence)() = AutonTopRed;

// Initialize the UI for the autonomous selection screen
void InitScreenAutonSelector() {
    screens.autonSelector->AddChildren({
        (new Clickable)->SetPosition(30, 50)->SetSize(200, 100)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonTopRed;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::red)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkRed)}),
            (new Text)->SetText("Top Red")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
        (new Clickable)->SetPosition(250, 50)->SetSize(200, 100)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonTopBlue;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::blue)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkBlue)}),
            (new Text)->SetText("Top Blue")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
    });
}