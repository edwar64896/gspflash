#include "gspflash.h"

uint16_t gspFlash::_flashCnt=0;

gspGrouped * gspFlash::firstInstance=nullptr;


// mode=0 (Off=0,On=1)
// mode=1 (Off=1,On=0)
void gspFlash::parseOnOff(char * szInput, int mode) {

    int iInput=atoi(szInput);
    if (mode)
        iInput=1-iInput;
    switch(iInput) {
        case 0:
            turnOff();
        break;
        case 1:
            turnOn();
        break;
    }
}

void gspFlash::parseOffOn(char * szInput) {
    parseOnOff(szInput,1);
}


gspFlash::gspFlash(int pin):gspGrouped() {
    _pin=pin;
}

void gspFlash::turnOff(){
    digitalWrite(_pin,LOW);
    bFlashing=false;
}

void gspFlash::turnOn() {
    digitalWrite(_pin,HIGH);
    bFlashing=false;
}

void gspFlash::flashFast() {
    bFlashing=true;
    _flashSpd=FAST_COUNT;

}

void gspFlash::flashSlow() {
    bFlashing=true;
    _flashSpd=SLOW_COUNT;

}

bool gspFlash::check() {
    if (_flashCnt++>_flashSpd) {
        _flashCnt=0;
        _flashToggle=!_flashToggle;
    }

    if (bFlashing) {
        if (_flashToggle) {
            digitalWrite(_pin,HIGH);   
        } else {
            digitalWrite(_pin,LOW);
        }
    }

    return true;

}