/* 
 * File:   CDByteUtils.cpp
 * Author: Welsiton
 * 
 * Created on 27 de Fevereiro de 2014, 15:58
 */

#include "CDByteUtils.h"

byte *CDByteUtils::addElement(byte *arr, int len, byte element) {
    byte *result = (byte *)realloc(arr, (len + 1) * sizeof (byte));
    result[len] = element;
    return result;
}

byte *CDByteUtils::concat(byte *A, int lenA, byte *B, int lenB) {
    byte *C = (byte *)malloc((lenA + lenB) * sizeof(byte));
    memcpy(C, A, lenA * sizeof(byte));
    memcpy(C + lenA, B, lenB * sizeof(byte));
    return C;
}
