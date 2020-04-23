
// Define the encoder related pins
#include <stdio.h>
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\encoder.h"
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\control.h"
#include"C:\Users\Ganam\Desktop\zlabs_position_control_1\include\resetting.h"

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A8, A7, A5, A4, A3, A2); // 

#include <PID_v1.h>


double  Kp =10;
double  Ki = 0;
double  Kd = .4;
double set_point;
double kp;
double ki;
double kd;
float start_time;
double  Input, Output; //Define Variables we'll be connecting to





PID myPID(&Input, &Output, &set_point, Kp, Ki, Kd, DIRECT);


enum STATE {Connection_confirmation, Reserting, Waiting_go , Waiting_values, Validation , Running , Halt }state ;
float  angle;
void setup()
{
    state = Connection_confirmation;
    Serial.begin(115200); // start the serial monitor link
    myPID.SetOutputLimits(-255, 255);
    myPID.SetMode(AUTOMATIC);
   
}


void loop() 
{
    
    if (state == Connection_confirmation)
    {

//      1-listen to the serial input till the message "111.1" arrives
//      2-sends the string "Right\n" back to the serial" 
//      3-sets the state to "Reserting"       
      
      lcd.clear();

        lcd.print(state);
       bool right_message_arrived=0;
       while (!right_message_arrived)
       {
           if ( Serial.available() )
           {
              float tag;
              tag =Serial.parseFloat(); 
              lcd.clear();
              lcd.print(tag);
              if (tag == 111.1)
              {
                lcd.clear();
                lcd.print("RighT");
                Serial.println("RighT");
                right_message_arrived=1;
                state = Reserting;

              }
           }
       }
    }
    if (state == Reserting)
    {        lcd.clear();

              lcd.print(state);

            reset();
            Serial.println("ReseteD");
            state = Waiting_values;
    }
    if (state == Waiting_go)
    {
              lcd.print(state);

    }
    if (state == Waiting_values)
    {        lcd.clear();

        lcd.print(state);
         if ( Serial.available() )
         {
            float tag;
            tag =Serial.parseFloat(); 
            if (tag == 222.2)
            {
              kp= Serial.parseFloat();
                          lcd.setCursor(8, 5);
            lcd.print(kp);
            delay(1000);
              ki= Serial.parseFloat();
              kd= Serial.parseFloat();
              set_point= Serial.parseFloat();
              myPID.SetTunings(kp, ki, kd);
              state = Validation;
            }
            
         }
    }
    
    if (state == Validation)
    {
        lcd.clear();
        lcd.print(state);
        Serial.println("GainS");
        Serial.println("kp");
        Serial.println(kp);
        Serial.println("ki");
        Serial.println(ki);
        Serial.println("kd");        
        Serial.println(kd);
        Serial.println("sp");        
        Serial.println(set_point);

        bool right_message_arrived=0;
        while (!right_message_arrived)
        {
           if ( Serial.available() )
           {
              float tag;
              tag =Serial.parseFloat(); 
              if (tag == 444.4)
              {
                right_message_arrived=1;
                start_time = micros();
                state = Running;
              }
           }
        }
//         
    }
    
    if (state == Running)
    {
//        lcd.clear();
//        lcd.print(state);
        delay(10);
        angle = float(encoderPos)/2000*360;
//        lcd.print(angle);
        Input = angle;
        myPID.Compute();
        int t=control_out(Output);
        Serial.println("s");
        Serial.println(angle);
        Serial.println(micros()-start_time);
    }
    
    if (state == Halt)
    {
        lcd.clear();
        lcd.print(state);
    }
    

}
