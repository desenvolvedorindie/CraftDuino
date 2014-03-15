#ifndef CDCOMMANDEVENT_H
#define	CDCOMMANDEVENT_H

#include <CDEvent.h>

#include "CDIType.h"

class CDCommandEvent : public CDEvent {
public:

    enum Events {
        NATIVE,
        CUSTOM,
        NR_EVENTS,
    };

    static const uint8_t SIZE = NR_EVENTS;
    
    const int ID;
    
    //SFALinkedList<CDIType> params;

    CDCommandEvent(const CDCommandEvent::Events type, const int id) : CDEvent(type), ID(id) {
    };
};

#endif

