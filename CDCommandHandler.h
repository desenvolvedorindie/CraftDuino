#ifndef CDCOMMANDHANDLER_H
#define	CDCOMMANDHANDLER_H

#include <SFAEventDispatcher.h>
#include <CDState.h>
#include <CDCommandEvent.h>

class CDCommandHandler : public CDState {
private:
    SFAEventDispatcher<CDCommandEvent> dispatcher;

public:

    CDCommandHandler() {
        addListener(CDCommandEvent::NATIVE, &CDCommandHandler::nativeHandler, *this);
    }

    template <typename ListenerT>
    void addListener(const CDCommandEvent::Events type, void (ListenerT::*member)(const CDCommandEvent &), ListenerT &object) {
        dispatcher.addListener(type, member, object);
    };

    void addListener(const CDCommandEvent::Events type, void (*function)(const CDCommandEvent &)) {
        dispatcher.addListener(type, function);
    };

    template <typename ListenerT>
    void removeListener(const CDCommandEvent::Events type, void (ListenerT::*member)(const CDCommandEvent &), ListenerT &object) {
        dispatcher.removeListener(type, member, object);
    };

    template <typename ListenerT>
    void removeListener(const CDCommandEvent::Events type, ListenerT &object) {
        dispatcher.removeListener(type, object);
    };

    void removeListener(const CDCommandEvent::Events type, void (*function)(const CDCommandEvent &)) {
        dispatcher.removeListener(type, function);
    };

    void dispatch(const CDCommandEvent &e) {
        dispatcher.dispatch(e);
    };

    bool hasListener(const CDCommandEvent::Events type) {
        return dispatcher.hasListener(type);
    };

    void nativeHandler(const CDCommandEvent &e) {
        switch (e.ID) {
            case 0: //pinMode
                break;
            case 1: //digitalWrite
                break;
            case 2: //digitalRead
                break;
            case 3: //analogReference
                break;
            case 4: //analogRead
                break;
            case 5: //analogWrite
                break;
            case 6: //tone
                break;
            case 7: //noTone
                break;
            case 8: //shiftOut
                break;
            case 9: //shiftIn
                break;
            case 10: //pulseIn
                break;
            case 11: //micros

                break;
            case 12: //micros
                break;
        };
    };
};

#endif
