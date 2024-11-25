const int analogInPin = A0;  // Analog input pin that the sensor is attached to
float sensorValue = 0;        // value read from the sensor
float media=0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin)*5.0/1024.0;
  media=0.97*media+0.03*sensorValue;
  //media=0;
  Serial.print(1000.0*sensorValue);
  Serial.print("\t");
  Serial.println(1000.0*media);
    

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10);
}
