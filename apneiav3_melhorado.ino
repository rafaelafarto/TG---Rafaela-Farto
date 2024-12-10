

#define NPONTOS 1000
#define AMPLMIN 30
#define TEMPO 33

const int pin1 = 9;  // First output pin
const int pin2 = 10; // Second output pin
const int pin3 = 11; // Third output pin
const int pin4 = 12; // Fourth output pin

const int analogInPin = A0;        // Analog input pin that the sensor is attached to

// taxa de amostragem: 100 pontos/s -> período de 10ms
// vetor para guardar 10s de dados = 1000 pontos
byte dados[NPONTOS];
int contador = 0;
bool carregar_dados = false;
long t_ultimo_disparo = millis();
float media=0;
float media_base=0;


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

void dispara(){
  aciona(LOW,LOW,LOW,LOW); // Não aciona nenhum pino
  aciona(HIGH,LOW,LOW,LOW); // Aciona apenas 1 pino
  aciona(HIGH,HIGH,LOW,LOW); //Aciona apenas 2 pinos
  aciona(HIGH,HIGH,HIGH,LOW); //Aciona apenas 3 pinos
  aciona(HIGH,HIGH,HIGH,HIGH); // Acionando os quatro pinos
  aciona(HIGH,HIGH,HIGH,LOW); //Aciona apenas 3 pinos
  aciona(HIGH,HIGH,LOW,LOW); //Aciona apenas 2 pinos
  aciona(HIGH,LOW,LOW,LOW); // Aciona apenas 1 pino
  aciona(LOW,LOW,LOW,LOW); // Não aciona nenhum pino
}

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dado = analogRead(analogInPin)/4.0;
  media=0.98*media+0.02*dado;
  media_base=0.995*media_base+0.005*dado;
  float media_final = media-media_base;
  Serial.print(dado);
  Serial.print("\t");
  Serial.print(media);
  Serial.print("\t");
  Serial.print(media_base);
  Serial.print("\t");
  Serial.print(media_final);
  dados[contador] = int(media_final+127);
  contador = contador+1;
  if (contador == NPONTOS){ // verifica se chegou no final do vetor
    carregar_dados = true;
    contador = 0;
  }

  if (carregar_dados){ // se janela cheia...
    int  meumin = 2000;
    int  meumax = -1;
    for (int idx = 0; idx < NPONTOS; idx++){
      if (dados[idx] > meumax) meumax = dados[idx];
      if (dados[idx] < meumin) meumin = dados[idx];
    }
    int amplitude = meumax - meumin;
    Serial.print("\t");
    Serial.print(amplitude);
    if ((amplitude < AMPLMIN) && (millis() - t_ultimo_disparo > 5000)){ // teve apneia
      digitalWrite(LED_BUILTIN, HIGH);
      dispara();
      t_ultimo_disparo = millis();
    }
    else digitalWrite(LED_BUILTIN, LOW);
  }

  Serial.print("\n");
  delay(10);
}
