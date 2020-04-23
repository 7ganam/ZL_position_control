
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


float start_time_micros; // this timer starts onece only when the encoder readings start flowing out, it's used to send the time of each reading to ML

float switch_to_reading_state_timer_start;  
float switch_to_reading_state_timer_current;
float switch_to_reading_state_period=1000;

PID myPID(&Input, &Output, &set_point, Kp, Ki, Kd, DIRECT);


enum STATE {Connection_confirmation, Reserting, Waiting_go , Waiting_values, Validation , Running , Reading_serial_input, Halt }state ;
float  angle;
void setup()
{
   lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
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
      
       lcd.setCursor(0,0);
       lcd.print(state);
       bool right_message_arrived=0;
       while (!right_message_arrived)
       {
           if ( Serial.available() )
           {
              float tag;
              tag =Serial.parseFloat(); 
              if (tag == 111.1)
              {

                Serial.println("RighT");
                right_message_arrived=1;
                state = Reserting;

              }
           }
       }
    }
    if (state == Reserting)
    {        
              lcd.setCursor(0,0);
              lcd.print("RT");

            reset();
            delay(1000);
            Serial.println("ReseteD");
            state = Waiting_values;
    }
    if (state == Waiting_go)
    {
              lcd.print(state);
              
    }
    if (state == Waiting_values)
    {   
        stop_motor();
        lcd.setCursor(0,0);
        lcd.print("WV");
        lcd.setCursor(0,1);
        lcd.print(micros());
         if ( Serial.available() )
         {
                  lcd.setCursor(0,0);
        lcd.print("WV2");
            float tag;
            tag =Serial.parseFloat(); 
            lcd.setCursor(5,1);
            lcd.print(tag);
            if (tag == 222.2)
            {
              kp= Serial.parseFloat();

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

        lcd.setCursor(0,0);
        lcd.print("VA");
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
//              lcd.setCursor(10,1);
//              lcd.print(1);
           if ( Serial.available() )
           {
              float tag;
              tag =Serial.parseFloat();
              lcd.setCursor(5,1);
              lcd.print(tag);
              if (tag == 444.4)
              {
                right_message_arrived=1;
                start_time = micros();
                switch_to_reading_state_timer_start = micros();
                state = Running;
              }
           }
        }
//         
    }
    
    if (state == Running)
    {
        lcd.setCursor(0,0);
        lcd.print("RU");
        delay(10);
        angle = float(encoderPos)/2000*360;
        Input = angle;
        myPID.Compute();
        int t=control_out(Output);
        Serial.println("s");
        Serial.println(angle);
        Serial.println(micros()-start_time);


        
        switch_to_reading_state_timer_current = micros()-switch_to_reading_state_timer_start ;
        if(switch_to_reading_state_timer_current > switch_to_reading_state_period)
        {
          state = Reading_serial_input;
        } 
    }
    if (state ==Reading_serial_input)
    {
              lcd.setCursor(0,0);
        lcd.print("RS");
        if ( Serial.available() )
       {
          float tag;
          tag =Serial.parseFloat();
          if (tag == 145.0)
          {
            lcd.clear();
            state = Reserting;
          }
          else if(tag != 145.0)
          {
            state = Running;
            switch_to_reading_state_timer_start = micros();
          }
          
       }
       else 
       {
         state = Running;  
         switch_to_reading_state_timer_start = micros();
       }
    }
    if (state == Halt)
    {
//        lcd.setCursor(0,0);
//        lcd.print(state);
    }
    

}
