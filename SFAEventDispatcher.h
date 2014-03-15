/*
 *	Copyright (c) 2013 by Welsiton Ferreira, WFCreations (wfcreations@gmail.com)
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without modification,
 *	are permitted provided that the following conditions are met:
 *
 *      Redistributions of source code must retain the above copyright notice, this
 * 	list of conditions and the following disclaimer.
 *
 * 	Redistributions in binary form must reproduce the above copyright notice, this
 *	list of conditions and the following disclaimer in the documentation and/or
 * 	other materials provided with the distribution.
 *
 * 	Neither the name of the {organization} nor the names of its
 *	contributors may be used to endorse or promote products derived from
 * 	this software without specific prior written permission.
 *
 * 	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * 	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * 	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * 	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * 	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * 	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * 	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * 	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * 	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SFA_SFAEVENTDISPATCHER_H
#define SFA_SFAEVENTDISPATCHER_H

#include <stddef.h>

#include <CDEvent.h>
#include <SFACallback.h>
#include <SFAMemberCallback.h>
#include <SFAFunctionCallback.h>
#include <SFALinkedList.h>

template <class EventType = CDEvent>
class SFAEventDispatcher {
private:

    SFALinkedList<SFACallback<void, const EventType&> > callbacks[EventType::SIZE];

public:

    SFAEventDispatcher() {
        CDEvent* test = (EventType *) NULL; // Force SFAEvent sublcass
    };

    template <typename ListenerT>
    void addListener(const typename EventType::Events type, void (ListenerT::*member)(const EventType &), ListenerT &object) {
        if (type < EventType::SIZE) {
            SFACallback<void, const EventType&> myCallback = SFACall::member(object, member);
            callbacks[type].append(myCallback);
        };
    };

    void addListener(const typename EventType::Events type, void (*function)(const EventType &)) {
        if (type < EventType::SIZE) {
            SFACallback<void, const EventType&> myCallback = SFACall::function(function);
            callbacks[type].append(myCallback);
        };
    };

    template <typename ListenerT>
    void removeListener(const typename EventType::Events type, void (ListenerT::*member)(const EventType &), ListenerT &object) {
        if (type < EventType::SIZE) {
            typedef void (ListenerT::*MethodPointer)(const EventType &);
            typename SFALinkedList<SFACallback<void, const EventType&> >::iterator iter = callbacks[type].begin();
            for (; iter.hasNext(); iter.next()) {
                MethodPointer method = *reinterpret_cast<const MethodPointer*> (&iter.current().method);
                ListenerT *obj = (ListenerT*) iter.current().object;
                if (method == member && (obj == &object)) {
                    callbacks[type].remove(iter);
                };
            };
        };
    };

    template <typename ListenerT>
    void removeListener(const typename EventType::Events type, ListenerT &object) {
        if (type < EventType::SIZE) {
            typename SFALinkedList<SFACallback<void, const EventType&> >::iterator iter = callbacks[type].begin();
            for (; iter.hasNext(); iter.next()) {
                ListenerT *obj = (ListenerT*) iter.current().object;
                if (obj == &object) {
                    callbacks[type].remove(iter);
                };
            };
        };
    };

    void removeListener(const typename EventType::Events type, void (*function)(const EventType &)) {
        if (type < EventType::SIZE) {
            typename SFALinkedList<SFACallback<void, const EventType&> >::iterator iter = callbacks[type].begin();
            for (; iter.hasNext(); iter.next()) {
                if (iter.current().getFunction() == function) {
                    callbacks[type].remove(iter);
                };
            };
        };
    };

    void dispatch(const EventType &e) {
        if (e.type < EventType::SIZE) {
            typename SFALinkedList<SFACallback<void, const EventType&> >::iterator iter = callbacks[e.type].begin();
            for (; iter.hasNext(); iter.next()) {
                iter.current()(e);
            };
        };
    };

    bool hasListener(const typename EventType::Events type) {
        if (type < EventType::SIZE) {
            return !callbacks[type].empty();
        };
        return false;
    };
};

#endif
