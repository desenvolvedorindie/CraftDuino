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

#ifndef _SFA_SFAMEMBERCALLBACK_H_
#define _SFA_SFAMEMBERCALLBACK_H_

#include <SFACallback.h>

template <class Class, class ReturnT = void, class ParamT = SFACall::Void>
class SFAMemberCallback : public SFACallback<ReturnT, ParamT> {
private:

    static ReturnT functor(const SFACallback<ReturnT, ParamT>* callback, const ParamT param) {
        Class *object = (Class*) callback->object;
        methodPointer method = *reinterpret_cast<const methodPointer*> (&callback->method);
        return (object->*method)(param);
    };

public:
    typedef void (Class::*methodPointer)(const ParamT);

    SFAMemberCallback(Class& object, const methodPointer method) : SFACallback<ReturnT, ParamT>(functor, &object, &method) {
    };
};

namespace SFACall {

    template <class Class, class ReturnT, class ParamT>
    inline SFAMemberCallback<Class, ReturnT, ParamT> member(Class &object, ReturnT(Class::*method)(const ParamT)) {
        return SFAMemberCallback<Class, ReturnT, ParamT>(object, method);
    };
};

#endif