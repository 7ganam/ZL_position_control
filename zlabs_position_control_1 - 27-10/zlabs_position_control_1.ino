// PID control of DC motor experiment.
#include <PID_v1.h>
#include <stdio.h>
//Define PID controller variables
//--------------------------------------------------------------------------------------------------------------------------------------------
double  Kp =10;
double  Ki = 0;
double  Kd = .4;
double  Setpoint =90;
volatile float z_poin;
volatile bool z_test=0;
//--------------------------------------------------------------------------------------------------------------------------------------------
int moveto(int goal_position , int start_position);

//Specify the links and initial tuning parameters
double  Input, Output; //Define Variables we'll be connecting to
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
 int discover_zero() ; 


boolean set_pid = false;

//define motor  related pins
#define ENA 45
#define IN2 49
#define IN1 53


// Define the encoder related pins
static int     pinA = 19; // Our first hardware interrupt pin is digital pin 2
static int     pinB = 18; // Our second hardware interrupt pin is digital pin 3
static int     pinZ = 2; // Our first hardware interrupt pin is digital pin 2

volatile int   aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile int   bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile int   encoderPos = 0;//this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
float angle;
volatile int   oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile int   reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent




//#######################################################################################//

void setup()
{
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)
  pinMode(pinZ, INPUT_PULLUP); // set pinB as an input, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)

  attachInterrupt(digitalPinToInterrupt(pinB), PinA, RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinA), PinB, RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below).
  attachInterrupt(digitalPinToInterrupt(pinZ), PinZ,  CHANGE); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  Serial.begin(115200); // start the serial monitor link

  //set output for motor  related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  //initialize motor 1 run in clockwise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //initialize the variables we're linked to

  //turn the PID on
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
  
     discover_zero()   ;
     delay(200);
     Serial.println("moveto");

    moveto(290 , encoderPos);
    Serial.println("moveto");
    delay(2000);

     encoderPos=0;


}

//#######################################################################################//
void loop()
{

    angle = float(encoderPos)/2000*360;
    Serial.println(angle);
    Input = angle;
    myPID.Compute();
    int t=control_out(Output);
    

    Serial.println(angle);


}

//#######################################################################################//
int moveto(int goal_position , int start_position)
{
  while (1)
  {
    control_out(80);
    Serial.println(start_position - encoderPos );
    if (encoderPos - start_position   >= goal_position )
    {

      control_out(0);
      return (0);

    }



  }

}



int discover_zero()   
{
   digitalWrite(IN2, LOW);
   digitalWrite(IN1, HIGH);
   analogWrite(ENA ,100);
   delay(100);
  analogWrite(ENA ,100);

   while(z_test==0){};
   
        Serial.print("in Z_test");

    digitalWrite(IN1, LOW);
   digitalWrite(IN2, LOW);
    analogWrite(ENA , abs(0));
    encoderPos=0;
    z_test=0;
     delay(1000);

    return (1);
    
  
}



int control_out(int signed_pwm)   // this function reads input(signed_pwm) ranged from (-255 to 255)
//                                   if the input is
//                                          - out of range : clip it back to range
//                                          - negative : set the output to the motor to run clockwise with the same abspolute value
//                                          - positive : set the output to the motor to run counter-clockwise with the same abspolute value
{
  if (signed_pwm > 255)
  {
    signed_pwm = 255;
  }
  if (signed_pwm < -255)
  {
    signed_pwm = -255;
  }

  if (signed_pwm > 0 )
  {
    //set motor 1 run in clockwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  if (signed_pwm < 0 )
  {
    //set motor 1 run in clockwise
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

  }

  analogWrite(ENA , abs(signed_pwm));
  return (abs(signed_pwm));
}



void PinA()
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

void PinB()
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

void PinZ()
{
//  z_poin=encoderPos;
//    Serial.println(z_poin);
    z_test=1;
    Serial.print("***************>");
//    Serial.println(encoderPos);
}
