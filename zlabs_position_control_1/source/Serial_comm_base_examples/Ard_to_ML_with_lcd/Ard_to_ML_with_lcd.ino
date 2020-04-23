void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(115200);
    float st = micros();
    for (int i =0; i<1000 ; i++)
    {
      delay(5);
      Serial.println(micros()-st);
    }
    Serial.println(-2);
}

void loop() 
{

}
