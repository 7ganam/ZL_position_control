
#ifndef ENC
#define ENC
#include"control.h"

inline  void Initialize_encoder_pins();
#define pinA 19
#define pinB 18
#define pinZ 2


volatile int   aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile int   bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile int   encoderPos = 0;//this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255


volatile int   oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile int   reading   = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

volatile float z_poin;
volatile bool z_test=0;




inline  void PinA()
{  
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  int a= digitalRead(pinA);
  int b= digitalRead(pinB);
  if (a==1 && b==1 && aFlag)
  { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //decrement the encoder's position count
    analogWrite(5 , encoderPos*2/360*255);
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (b==1 && a==0) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

inline void PinB()
{
  
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
    int a= digitalRead(pinA);
  int b= digitalRead(pinB);
  if (a && b && bFlag)
  { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //increment the encoder's position count
    analogWrite(5 , encoderPos*2/360*255);
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (a==1 && b==0) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}


inline void PinZ()
{
    z_test=1;
}
inline  void Initialize_encoder_pins()
{

  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)
  pinMode(pinZ, INPUT_PULLUP); // set pinB as an input, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)

  attachInterrupt(digitalPinToInterrupt(pinB), PinA,  RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinA), PinB,  RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below).
  attachInterrupt(digitalPinToInterrupt(pinZ), PinZ,  CHANGE); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

}


int discover_zero()   
{
   digitalWrite(IN2, LOW);
   digitalWrite(IN1, HIGH);
   analogWrite(ENA ,80);

   while(z_test==0){};//wait till the zchannel interrupt changes z_test to 1;
   
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, LOW);
   analogWrite(ENA , abs(0));
  //  encoderPos=0;
   z_test=0;
   return (1);

}
int moveto(int goal_position , int start_position)
{
  while (1)
  {
    control_out(80);
    if (encoderPos - start_position   >= goal_position )
    {

      control_out(0);
      return (0);

    }
  }

}
int moveto_negative(int goal_position , int start_position)
{
  while (1)
  {
    control_out(-100);
    if ( start_position-encoderPos    >= goal_position )
    {

      control_out(0);
      return (0);

    }
  }

}

#endif