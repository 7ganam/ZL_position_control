
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A8, A7, A5, A4, A3, A2); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}
void loop() { 
// lcd.print("Arduino"); // Prints "Arduino" on the LCD 
// delay(3000); // 3 seconds delay 
// lcd.setCursor(2,1); // Sets the location at which subsequent text written to the LCD will be displayed 
// lcd.print("LCD Tutorial"); 
// delay(3000); 
// lcd.clear(); // Clears the display 
// lcd.blink(); //Displays the blinking LCD cursor 
// delay(4000); 
// lcd.setCursor(7,1); 
// delay(3000); 
// lcd.noBlink(); // Turns off the blinking LCD cursor 
// lcd.cursor(); // Displays an underscore (line) at the position to which the next character will be written 
// delay(4000); 
// lcd.noCursor(); // Hides the LCD cursor 
// lcd.clear(); // Clears the LCD screen 

lcd.setCursor(1,1); // Sets the location at which subsequent text written to the LCD will be displayed 
lcd.print("11"); 

lcd.setCursor(5,1); // Sets the location at which subsequent text written to the LCD will be displayed 
lcd.print("51"); 

lcd.setCursor(2,0); // Sets the location at which subsequent text written to the LCD will be displayed 
lcd.print("20");
}
