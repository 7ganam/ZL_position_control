////this code sends 1000 tagged messages as follows
//"s\n",i,"\n",t,"\n"
//where s is the "s" char
//i is integer
//t is the time of sending the message in microsecond 
//---------------------------------------------------
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A8, A7, A5, A4, A3, A2); // 

int i = 0;
float start_time_micros;
float read_timer_start;
float read_timer_current;

enum STATE{Start, Sending, Reading ,End}state ;
void setup() 
{
    Serial.begin(115200);
    state = Sending;  
}

void loop() 
{
    if (state == Start)
    {
            start_time_micros = micros();
            read_timer_start = micros();
            state = Sending;
    }
    
    if (state == Sending)
    {
          delay(5);
          if (i==100000)
          {
              Serial.println("e");
              state = End;
          }
          else
          {
              Serial.println("s");
              Serial.println(i);
              Serial.println(micros()-start_time_micros);
              i=i+1;
              read_timer_current = micros()-read_timer_start ;

              if(read_timer_current > 1000)
              {
                state = Reading;
              } 
          }        
    }
  
    if (state == Reading)
    {
           if ( Serial.available() )
           {
              float tag;
              tag =Serial.parseFloat();
              if (tag == 145.0)
              {
//                Serial.println("e");
                state = End;
              }
              else if(tag != 145.0)
              {
                state = Sending;
                read_timer_start = micros();
              }
              
           }
           else 
           {
             state = Sending;  
             read_timer_start = micros();
           }

           
    }
    if (state == End)
    {
      while(1)
      {
                lcd.clear();
                lcd.print(i);
      }
    }
    


}
