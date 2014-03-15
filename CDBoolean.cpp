#include "CDBoolean.h"

const CDBoolean CDBoolean::BOOLEAN_TRUE(true);
const CDBoolean CDBoolean::BOOLEAN_FALSE(false);
const CDBoolean CDBoolean::BOOLEAN_FALSE(false);

CDBoolean CDBoolean::createFromTVL(const CDTVL &tvl) {
    if (tvl.getTag() == CDIType::BOOLEAN_TYPE) {
        if (tvl.getLenght() == 1) {
            if (tvl.getValue()[0] == 0) {
                return BOOLEAN_FALSE;
            } else if (tvl.getValue()[0] == 1) {
                return BOOLEAN_TRUE;
            }
        }
    }
    return BOOLEAN_NULL;
}

CDBoolean::CDBoolean(boolean value) : value(value) {
    this->value = value;
}

boolean CDBoolean::getValue() const {
    return this->value;
}

CDTVL CDBoolean::getTVL() const {
    byte bytes[1];
    if (this->value) {
        bytes[0] = 1;
    } else {
        bytes[0] = 0;
    }
    return CDTVL(CDIType::BOOLEAN_TYPE, 1, bytes);
}

bool CDBoolean::operator==(const CDBoolean &other) const {
    return this->value == other.value;
}

bool CDBoolean::operator!=(const CDBoolean &other) const {
    return this->value != other.value;
}