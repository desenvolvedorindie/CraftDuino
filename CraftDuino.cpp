#include <CraftDuino.h>

CraftDuino_ CraftDuino;

CraftDuino_::CraftDuino_() : currentState(NULL) {
};

void CraftDuino_::init(CDCommandHandler* state) {
    if(currentState != NULL) {
        currentState = state;
        currentState->onCreate();        
    }
};

void CraftDuino_::loop() {    
    if(currentState != NULL) {
        currentState->dispatch(CDCommandEvent(CDCommandEvent::NATIVE, 0));
        currentState->onLoop();
    }
};