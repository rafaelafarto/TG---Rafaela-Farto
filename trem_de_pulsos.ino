#define TEMPO 33

const int pin1 = 9;  // First output pin
const int pin2 = 10; // Second output pin
const int pin3 = 11; // Third output pin
const int pin4 = 12; // Fourth output pin

void aciona(bool p1, bool p2, bool p3, bool p4){
    digitalWrite(pin1, p1);
    digitalWrite(pin2, p2);
    digitalWrite(pin3, p3);
    digitalWrite(pin4, p4);
    delayMicroseconds(TEMPO); // Wait 50us

    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    delayMicroseconds(TEMPO); // Wait 50us
}

void setup() {
  // Set output pins for pulse generation
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  
  // Initialize serial communication for current monitoring
  Serial.begin(9600);
}

void loop() {
  // Repeat indefinitely
  aciona(LOW,LOW,LOW,LOW); // Não aciona nenhum pino
  aciona(HIGH,LOW,LOW,LOW); // Aciona apenas 1 pino
  aciona(HIGH,HIGH,LOW,LOW); //Aciona apenas 2 pinos
  aciona(HIGH,HIGH,HIGH,LOW); //Aciona apenas 3 pinos
  aciona(HIGH,HIGH,HIGH,HIGH); // Acionando os quatro pinos
  aciona(HIGH,HIGH,HIGH,LOW); //Aciona apenas 3 pinos
  aciona(HIGH,HIGH,LOW,LOW); //Aciona apenas 2 pinos
  aciona(HIGH,LOW,LOW,LOW); // Aciona apenas 1 pino
  aciona(LOW,LOW,LOW,LOW); // Não aciona nenhum pino

  delay(10);
}
