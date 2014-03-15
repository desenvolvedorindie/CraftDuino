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

#ifndef SFA_SFALINKEDLIST_H
#define SFA_SFALINKEDLIST_H

#include <stddef.h>
#include <data/SFALinkedListIterator.h>
#include <data/SFALinkedListElement.h>

template <typename ElementT>
class SFALinkedList {
private:
    SFALinkedListElement<ElementT>* first;

    SFALinkedListElement<ElementT>* last;

    unsigned int _count;

public:
    typedef SFALinkedListIterator<SFALinkedListElement<ElementT> > iterator;

    typedef ElementT valueType;

    SFALinkedList() : first(NULL), last(NULL), _count(0) {
    };

    ~SFALinkedList() {
        removeAll();
    };

    void append(ElementT const &data) {
        SFALinkedListElement<ElementT> *tmp = new SFALinkedListElement<ElementT>(data);
        if (last) {
            tmp->prev = last;
            last->next = tmp;
            last = tmp;
        } else {
            first = tmp;
            last = first;
        };
        _count++;
    };

    void prepend(ElementT const &data) {
        SFALinkedListElement<ElementT> *tmp = new SFALinkedListElement<ElementT>(data);
        if (first) {
            tmp->next = first;
            first->prev = tmp;
            first = tmp;
        } else {
            first = tmp;
            last = first;
        };
        _count++;
    };

    bool addAfter(iterator& iteratorElement, ElementT const &data) {
        if (iteratorElement.element || iteratorElement.linkedList == this) {
            SFALinkedListElement<ElementT> *tmp = new SFALinkedListElement<ElementT>(data);
            if (iteratorElement.element == last) {
                last = tmp;
            } else {
                iteratorElement.element->next->prev = tmp;
            };
            tmp->next = iteratorElement.element->next;
            tmp->prev = iteratorElement.element;
            iteratorElement.element->next = tmp;
            _count++;
            return true;
        };
        return false;
    };

    bool addBefore(iterator& iteratorElement, ElementT const &data) {
        if (iteratorElement.element || iteratorElement.linkedList == this) {
            SFALinkedListElement<ElementT> *tmp = new SFALinkedListElement<ElementT>(data);
            if (iteratorElement.element == first) {
                first = tmp;
            } else {
                iteratorElement.element->prev->next = tmp;
            };
            tmp->next = iteratorElement.element;
            tmp->prev = iteratorElement.element->prev;
            iteratorElement.element->prev = tmp;
            _count++;
            return true;
        };
        return false;
    };

    ElementT const &operator[](unsigned int index) const {
        SFALinkedListElement<ElementT> *tmp = first;
        for (unsigned int idx = 0; tmp; tmp = tmp->next, idx++) {
            if (idx == index) {
                return tmp->data;
            };
        };
        return NULL;
    };

    ElementT &operator[](unsigned int index) {
        SFALinkedListElement<ElementT> *tmp = first;
        for (unsigned int idx = 0; tmp; tmp = tmp->next, idx++) {
            if (idx == index) {
                return tmp->data;
            };
        };
    };

    bool has(ElementT const &data) const {
        SFALinkedListElement<ElementT> *tmp = first;
        while (tmp) {
            if (tmp->data == data) {
                return true;
            };
            tmp = tmp->next;
        };
        return false;
    };

    iterator begin() const {
        return iterator(first, this);
    };

    iterator end() const {
        return iterator(last, this);
    };

    bool empty() const {
        return !first;
    };

    unsigned int size() const {
        return _count;
    };

    unsigned int remove(ElementT const &data) {
        unsigned int count = _count;
        SFALinkedListElement<ElementT> *tmp = first;
        SFALinkedListElement<ElementT> *tmp2;
        while (tmp) {
            if (tmp->data == data) {
                if (tmp == first) {
                    first = tmp->next;
                } else {
                    tmp->prev->next = tmp->next;
                };
                if (tmp == last) {
                    last = tmp->prev;
                } else {
                    tmp->next->prev = tmp->prev;
                };
                tmp2 = tmp->next;
                delete tmp;
                tmp = tmp2;
                _count--;
                continue;
            };
            tmp = tmp->next;
        };
        return count - _count;
    };

    bool remove(iterator& iteratorElement) {
        if (iteratorElement.element || iteratorElement.linkedList == this) {
            if (iteratorElement.element == first) {
                first = iteratorElement.element->next;
            } else {
                iteratorElement.element->prev->next = iteratorElement.element->next;
            };
            if (iteratorElement.element == last) {
                last = iteratorElement.element->prev;
            } else {
                iteratorElement.element->next->prev = iteratorElement.element->prev;
            };
            _count--;
            delete iteratorElement.element;
            return 1;
        };
        return 0;
    };

    void removeAll() {
        if (first) {
            SFALinkedListElement<ElementT> *iter = first;
            SFALinkedListElement<ElementT> *tmp;
            while (iter) {
                tmp = iter;
                iter = iter->next;
                delete tmp;
            };
        };
        first = NULL;
        last = first;
        _count = 0;
    };
};

#endif
