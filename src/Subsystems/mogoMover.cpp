#include "vex.h"

using namespace vex;

void ToggleMogoMover() {
    mogoMover.set((!(bool)mogoMover.value()));
}


void InitMogoMover() {

}

void UserInitMogoMover() {
    PrimaryController.ButtonL2.pressed(ToggleMogoMover);
}

void TickMogoMover() {

}