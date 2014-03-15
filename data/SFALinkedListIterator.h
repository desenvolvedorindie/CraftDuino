/*
 *	Copyright (c) 2013 by Welsiton Ferreira, WFCreations (wfcreations@gmail.com)
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without modification,
 *	are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this
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

#ifndef _SFA_SFALINKEDLISTINTERATOR_H_
#define _SFA_SFALINKEDLISTINTERATOR_H_

#include <stddef.h>
#include <SFALinkedList.h>

template <typename ElementT>
class SFALinkedList;

template <class ElementT>
class SFALinkedListIterator {
    friend class SFALinkedList<typename ElementT::valueType>;

    ElementT* element;

    const SFALinkedList<typename ElementT::valueType> * const linkedList;

    SFALinkedListIterator(ElementT* element, SFALinkedList<typename ElementT::valueType> const *linkedList) : element(element), linkedList(linkedList) {
    };

public:

    bool operator!=(SFALinkedListIterator<ElementT> value) const {
        return !(element == value.element);
    };

    bool operator==(SFALinkedListIterator<ElementT> value) const {
        return element == value.element;
    };

    void next() {
        if (element) {
            element = element->next;
        };
    };

    void prev() {
        if (element) {
            element = element->prev;
        };
    };

    bool hasNext() const {
        return element != NULL;
    };

    bool hasPrev() const {
        return element != NULL;
    };

    typename ElementT::valueType current() const {
        return element->data;
    };
};

#endif
