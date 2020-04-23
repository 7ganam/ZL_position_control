
#include <LiquidCrystal.h> 

LiquidCrystal lcd(A8, A7, A5, A4, A3, A2); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
void setup()
{ 
       Serial.begin(115200);
       lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}
void loop() 
{
 if ( Serial.available() )
   {
      float tag;
      tag =Serial.parseFloat(); // the expected input is in the format of four numbers separated by any charachter EX: 145*11*18*19 .. parse float reads one number at a time. the first number is the tag.
      if (tag == 145.0)
      {
        float kp= Serial.parseFloat();
        float ki= Serial.parseFloat();
        float kd= Serial.parseFloat();
        float end_tag= Serial.parseFloat();

        if(end_tag==999)
        {
          lcd.print(kp); //         lcd.setCursor(2,1); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.print(" "); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.print(ki); 
          lcd.print(" "); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.print(kd); 
        }
      }
      
   }
}
