#include "CDDataUnitHeader.h"

CDDataUnitHeader::CDDataUnitHeader(byte commandLenght, byte commandID, byte commandStatus) : commandLenght(commandLenght), commandID(commandID), commandStatus(commandStatus) {
}

CDDataUnitHeader::CDDataUnitHeader(const CDDataUnitHeader& orig) {
    this->commandLenght = orig.commandLenght;
    this->commandID = orig.commandID;
    this->commandStatus = orig.commandStatus;
}

CDDataUnitHeader::~CDDataUnitHeader() {
}

byte *CDDataUnitHeader::getBytes() {
    byte *bytes_ptr = (byte *) malloc(3 * sizeof (byte));
    bytes_ptr[0] = this->commandLenght;
    bytes_ptr[1] = this->commandID;
    bytes_ptr[2] = this->commandStatus;
    return bytes_ptr;
}

byte CDDataUnitHeader::getCommandLenght() {
    return this->commandLenght;
}

void CDDataUnitHeader::setCommandLenght(byte commandLenght) {
    this->commandLenght = commandLenght;
}

byte CDDataUnitHeader::getCommandID() {
    return this->commandID;
}

void CDDataUnitHeader::setCommandID(byte commandID) {
    this->commandID = commandID;
}

byte CDDataUnitHeader::getCommandStatus() {
    return this->commandStatus;
}

void CDDataUnitHeader::setCommandStatus(byte commandStatus) {
    this->commandStatus = commandStatus;
}