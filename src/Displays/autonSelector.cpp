#include "vex.h"

#include "Autonomous/autonSequences.h"
#include "Displays/screenManager.h"

using namespace KOWGUI;

// Current auton function to run when autonomous starts
void (*selectedAutonSequence)() = AutonNegativeRed;

// Initialize the UI for the autonomous selection screen
void InitScreenAutonSelector() {
    screens.autonSelector->AddChildren({
        // Button to select AutonNegativeRed
        (new Clickable)->SetPosition(30, 50)->SetSize(200, 50)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonNegativeRed;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::red)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkRed)}),
            (new Text)->SetText("- Red")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
        // Button to select AutonNegativeBlue
        (new Clickable)->SetPosition(250, 50)->SetSize(200, 50)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonNegativeBlue;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::blue)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkBlue)}),
            (new Text)->SetText("- Blue")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
        // Button to select AutonPositiveRed
        (new Clickable)->SetPosition(30, 130)->SetSize(200, 50)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonPositiveRed;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::red)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkRed)}),
            (new Text)->SetText("+ Red")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
        // Button to select AutonPositiveBlue
        (new Clickable)->SetPosition(250, 130)->SetSize(200, 50)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonPositiveBlue;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::blue)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkBlue)}),
            (new Text)->SetText("+ Blue")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),

        // Button to select AutonSkills
        (new Clickable)->SetPosition(0, 0)->SetSize(40, 40)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonSkills;})->AddChildren({
            (new NSelected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::white)}),
            (new Selected)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::gray)}),
            (new Text)->SetText("S")->SetFontSize(30)->SetColor(Color::black)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
    });
}