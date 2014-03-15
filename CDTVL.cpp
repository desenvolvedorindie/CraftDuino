#include "CDTVL.h"

CDTVL::CDTVL(byte tag, byte lenght, byte value[]) : tag(tag), lenght(lenght), value(value) {
}

CDTVL::CDTVL(const CDTVL& orig) {
    this->tag = orig.tag;
    this->lenght = orig.lenght;
    this->value = orig.value;
}

byte *CDTVL::getBytes() const {
    byte *bytes_ptr = (byte *) malloc((this->getLenght() + 2) * sizeof (byte));
    bytes_ptr[0] = this->getTag();
    bytes_ptr[1] = this->getLenght();
    for (int i = 2; i < this->getLenght() + 2; i++) {
        bytes_ptr[i] = value[i - 2];
    }
    return bytes_ptr;
}

byte CDTVL::getTag() const {
    return this->tag;
}

void CDTVL::setTag(byte value) {
    this->tag = value;
}

byte CDTVL::getLenght() const {
    return this->lenght;
}

byte *CDTVL::getValue() const {
    return this->value;
}

void CDTVL::setValue(byte lenght, byte *value) {
    this->value = value;
    this->lenght = lenght;
}