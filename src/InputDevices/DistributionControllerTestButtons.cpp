#include "DistributionControllerTestButtons.h"

DistributionControllerTestButtons::DistributionControllerTestButtons(EventDispatcher* eD) {
    eventDispatcher = eD;

    for (int i = 0; i <= 1; i++) {
        button[i] = new Bounce2::Button();
        button[i]->attach(22 + i, INPUT_PULLUP);
        button[i]->interval(10);
        button[i]->setPressedState(LOW);
    }
}

void DistributionControllerTestButtons::update() {
    for (int i = 0; i <= 1; i++) {
        button[i]->update();
        if (button[i]->pressed()) {
            eventDispatcher->dispatch(new Event(EVENT_SOURCE_SWITCH, word(0, 63 + i), 1));
        }
        else if (button[i]->released()) {
            eventDispatcher->dispatch(new Event(EVENT_SOURCE_SWITCH, word(0, 63 + i), 0));
        }
    }
}
