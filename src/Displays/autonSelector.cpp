#include "vex.h"

#include "Autonomous/autonSequences.h"
#include "Displays/screenManager.h"

using namespace KOWGUI;

// Current auton function to run when autonomous starts
void (*selectedAutonSequence)() = AutonPositiveRedBasic;

// Initialize the UI for the autonomous selection screen
void InitScreenAutonSelector() {
    screens.autonSelector->AddChildren({
        (new Column)->SetPosition(30, 50)->SetSize(480 - 60, 240 - 50 - 30)->SetScaleToFit(true)->SetSpacing(10)->AddChildren({
            (new Row)->SetScaleToFit(true)->SetSpacing(15)->AddChildren({
                // Button to select AutonNegativeRed
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonNegativeRed;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::red)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkRed)}),
                    (new Text)->SetText("- Red")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
                // Button to select AutonNegativeBlue
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonNegativeBlue;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::blue)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkBlue)}),
                    (new Text)->SetText("- Blue")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
            }),
            (new Row)->SetScaleToFit(true)->SetSpacing(15)->AddChildren({
                // Button to select AutonPositiveRed
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonPositiveRedBasic;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::red)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkRed)}),
                    (new Text)->SetText("+ Red B")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
                // Button to select AutonPositiveBlue
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonPositiveBlueBasic;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::blue)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::darkBlue)}),
                    (new Text)->SetText("+ Blue B")->SetFontSize(30)->SetColor(Color::white)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
            }),
            (new Row)->SetScaleToFit(true)->SetSpacing(15)->AddChildren({
                // Button to select AutonDriveForward
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonDriveForward;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::white)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::gray)}),
                    (new Text)->SetText("Drv Frd")->SetFontSize(30)->SetColor(Color::black)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
                // Button to select AutonSkills
                (new Clickable)->SetRelease([](BaseNode* self){selectedAutonSequence = AutonSkills;})->AddChildren({
                    (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::white)}),
                    (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::gray)}),
                    (new Text)->SetText("Skills")->SetFontSize(30)->SetColor(Color::black)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
                }),
            }),
        }),

        // Text to show the current selection
        (new Text)->SetID("selectedAutonText")->SetPosition(240, 0)->SetSize(50, 50)->SetFontSize(35)->SetFont(Text::fontProportional)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::visible)->SetPreTick([](BaseNode* self){
            Text* textSelf = (Text*)self;
            if(selectedAutonSequence == nullptr) textSelf->SetText("Selected: None");
            else if(selectedAutonSequence == AutonNegativeRed) textSelf->SetText("Selected: - Red");
            else if(selectedAutonSequence == AutonNegativeBlue) textSelf->SetText("Selected: - Blue");
            else if(selectedAutonSequence == AutonPositiveRedBasic) textSelf->SetText("Selected: + Red B");
            else if(selectedAutonSequence == AutonPositiveBlueBasic) textSelf->SetText("Selected: + Blue B");
            else if(selectedAutonSequence == AutonDriveForward) textSelf->SetText("Selected: Drv Frd");
            else if(selectedAutonSequence == AutonSkills) textSelf->SetText("Selected: Skills");
            else textSelf->SetText("Selected: ERROR");
        }),

        // Button to save the APS drive log
        (new Clickable)->SetPosition(0, 240 - 30)->SetSize(30, 30)->SetPress([](BaseNode* self){aps.SaveDriveLog();})->AddChildren({
            (new NFocused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::white)}),
            (new Focused)->AddChildren({(new RoundedRectangle)->SetOutlineRadius(30)->SetFillColor(Color::gray)}),
            (new Text)->SetText("Log")->SetFontSize(13)->SetColor(Color::black)->SetAlignments(Text::HorizontalAlign::center, Text::VerticalAlign::middle)->SetOverflow(Text::Overflow::wrap),
        }),
    });
}