#ifndef GSP_FLASH
#define GSP_FLASH

#include "Arduino.h"
#include <gspgrouped.h>

#define FAST_COUNT 8192
#define SLOW_COUNT 16384

#define GSPFLASH_ONOFF_PARSER(a) [&a](char* szInput) {a.parseOnOff(szInput);}
#define GSPFLASH_OFFON_PARSER(a) [&a](char* szInput) {a.parseOffOn(szInput);}
#define GSPFLASH_TURNON(a)       [&a]() {a.turnOn();}
#define GSPFLASH_TURNOFF(a)      [&a]() {a.turnOff();}
#define GSPFLASH_FLASHSLOW(a)    [&a]() {a.flashSlow();}
#define GSPFLASH_FLASHFAST(a)    [&a]() {a.flashFast();}

class gspFlash:public gspGrouped {

    public:
    
        gspFlash(int pin);
        ~gspFlash(){};

        void parseOnOff(char * ,int =0);
        void parseOffOn(char * );

        void flashNot()     { bFlashing = false; };
        void turnOff()      { _OnState  = false; }
        void turnOn()       { _OnState  = true;  }
        void flashFast()    { bFlashing = true; _OnState=true; _flashSpd=FAST_COUNT; }
        void flashSlow()    { bFlashing = true; _OnState=true; _flashSpd=SLOW_COUNT; }
        void toggleState()  { _OnState  = !_OnState;}
        int getState();

        //bool check();
        bool _isr();

        static void startCheckAll() {
            gspGrouped::_isr_checking = true;
            gspGrouped::_isr_setInitialInstance_fast(gspFlash::firstInstance);
            gspGrouped::_isr_startTimer();
        }    

        //static void checkAll() {
           // gspGrouped::checkAll(gspFlash::firstInstance);
        //}        

    protected:

        void setFirstInstance(gspGrouped * fi) {gspFlash::firstInstance = fi;}
        gspGrouped * getFirstInstance() {return gspFlash::firstInstance;}
        static gspGrouped * firstInstance;   

    private:

        int _pin=0;
        bool bFlashing=false;
        static uint16_t _flashCnt;
        uint16_t _flashSpd=0;
        bool _flashToggle=false;
        bool _flashToggleSlow=false;
        bool _OnState=false;
};

#endif
