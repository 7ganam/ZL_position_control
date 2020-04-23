////this code sends 1000 tagged messages as follows
//"s\n",i,"\n",t,"\n"
//where s is the "s" char
//i is integer
//t is the time of sending the message in microsecond 
//---------------------------------------------------
void setup() 
{
    Serial.begin(115200);
    float st = micros();
    
    for (int i = 0; i<1000 ; i++)
    {
      delay(5);
      Serial.println("s");
      Serial.println(i);
      Serial.println(micros()-st);
    }
    Serial.println("e");
}

void loop() 
{

}
