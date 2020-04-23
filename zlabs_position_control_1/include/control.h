
#ifndef CONT
#define CONT




//define motor  related pins
#define ENA 45
#define IN2 49
#define IN1 53

void initialize_motor_pins()
{
  //set output for motor  related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  //initialize motor 1 run in clockwise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

}

int stop_motor()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA ,0);
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





#endif