#ifndef CDBYTEUTILS_H
#define	CDBYTEUTILS_H

#include <arduino.h>

class CDByteUtils {
public:
    static byte *addElement(byte *arr, int len, byte element);
    static byte *concat(byte *A, int lenA, byte *B, int lenB); 
private:

};

#endif
