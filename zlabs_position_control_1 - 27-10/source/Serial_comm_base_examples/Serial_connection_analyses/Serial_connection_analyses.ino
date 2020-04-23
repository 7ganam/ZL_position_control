void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(115200);
    delay(2000);
    float st = micros();
    
    for (int i =0; i<1000 ; i++)
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
