
#ifndef REST
#define REST

#include"encoder.h"
#include"control.h"

void reset()
{
    
    Initialize_encoder_pins();
    initialize_motor_pins();
    z_test=0;
    discover_zero()   ;
    moveto(1, encoderPos);
    encoderPos=0;
}
#endif