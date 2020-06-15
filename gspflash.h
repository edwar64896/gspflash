#ifndef GSP_FLASH
#define GSP_FLASH

#include "Arduino.h"
#include <gspgrouped.h>

#define FAST_COUNT 8192
#define SLOW_COUNT 16384

class gspFlash:public gspGrouped {

    public:
        gspFlash(int pin);
        ~gspFlash(){};
    
        static gspFlash * makeOne(uint8_t _pin) {
            gspFlash * instance = new gspFlash(_pin);
            gspGrouped::register_instance(instance);
            return instance;
        }

        void turnOn();
        void turnOff();
        void flashSlow();
        void flashFast();
    
        bool check();

        static void checkAll() {
            gspGrouped::checkAll(gspFlash::firstInstance);
        }        

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
};

#endif