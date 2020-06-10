#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);  // D9 Left and D8 right
BBCar car(pin8, pin9, servo_ticker);

int main() {
    while(1){
           car.goStraight(-100);
           wait(1);
           car.stop();
           wait(1);
    }
}