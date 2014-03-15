#include "CDDataUnit.h"

CDDataUnit::CDDataUnit(CDDataUnitHeader &header) : header(header), body((CDTVL*) malloc(0)), bodyLenght(0) {
}

CDDataUnit::~CDDataUnit() {
    free(body);
}

void CDDataUnit::addTVL(CDTVL &element) {
    this->bodyLenght++;
    this->body = (CDTVL*) realloc(this->body, this->bodyLenght * sizeof (CDTVL));
    this->body[this->bodyLenght - 1] = CDTVL(element.getTag(), element.getLenght(), element.getValue());
}

byte *CDDataUnit::getBytes() {
    byte *bytes = this->header.getBytes();
    int totalSize = 3;
    for (int i = 0; i < this->bodyLenght; i++) {
        byte *ptr = this->header.getBytes();
        ptr = this->body[i].getBytes();
        bytes = CDByteUtils::concat(bytes, totalSize, ptr, this->body[i].getLenght() + 2);
        totalSize += body[i].getLenght() + 2;
        free(ptr);
    }
    return bytes;
}

int CDDataUnit::length() {
    int totalSize = 3;
    for (int i = 0; i < this->bodyLenght; i++) {
        totalSize += body[i].getLenght() + 2;
    }
    return totalSize;
}