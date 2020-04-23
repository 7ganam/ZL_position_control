
// Define the encoder related pins
#include <stdio.h>
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\encoder.h"
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\control.h"
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\resetting.h"

#include <PID_v1.h>


double  Kp =10;
double  Ki = 0;
double  Kd = .4;
double  Setpoint =90;
double  Input, Output; //Define Variables we'll be connecting to
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


enum STATE {Reserting, Waiting_go , Waiting_values, Validation , Running  } ;
STATE = Running;
float  angle;
void setup()
{
    Serial.begin(115200); // start the serial monitor link
    reset();

    
    myPID.SetOutputLimits(-255, 255);
    myPID.SetMode(AUTOMATIC);
   
}


void loop() 
{
    if (STATE == Reserting)
      {
            
      }
      else if (STATE == Waiting_go)
      {

      }
      else if (STATE == Waiting_values)
      {
        
      }
      else if (STATE == Validation)
      {

      }
      else if (STATE == Running)
      {
        angle = float(encoderPos)/2000*360;
        Input = angle;
        myPID.Compute();
        int t=control_out(Output);
        Serial.println(angle);
      }
    

}
