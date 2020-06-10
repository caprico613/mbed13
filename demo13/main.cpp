#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

void carGo(Arguments *in, Reply *out);
RPCFunction rpcCar(&carGo, "carGo");

int main() {
    // please contruct you own calibration table with each servo    
    // left
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-13.02, -12.76, -12.159, -11.806, -6.600, 0.000, 7.018, 11.843, 12.680, 12.891, 13.099};
    // right
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-13.318, -13.318, -13.159, -12.512, -5.180, 0.000, 5.900, 11.484, 13.180, 13.181, 13.199};

     car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    char buf[256], outbuf[256];
    while (1) {
        for( int i=0; ;i++ ) {
            buf[i] = xbee.getc();
            if(buf[i] == '\n') break;
        }

        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);
    }
}

void carGo (Arguments *in, Reply *out)   {

    double x = in->getArg<double>();


    car.goStraightCalib(x);

}