// Projeto RX_02 28/07/2020
// Sensor Ulta-sonico ativado

#include <Servo.h> //Biblioteca utilizada
Servo servoMotor;  // Cria um Objeto servo chamado Servo

int posServo = 10; //Definimos a variável que indica a posição do servo inicial
int flagServo = 0;
boolean setServoMotor = false;

//Motor Esquerdo Dianteiro
int motEDF = 4;
int motEDT = 5;

//Motor Esquerdo Trazeiro
int motETF = 6;
int motETT = 7;

//Motor Direito Dianteiro
int motDDF = 8;
int motDDT = 9;

//Motor Direito Trazeiro
int motDTF = 10;
int motDTT = 11;

//Iluminacao
int led_1 = 22;
int led_2 = 23;
int led_3 = 24;
int led_4 = 25;

//Sesor Fotoeletrico
int IRDireito = 52; // Escolhe pino de entrada para Sensor Infravermelho Direito
int IREsquerdo = 53; // Escolhe pino de entrada para Sensor Infravermelho Esquerdo

//Declaracao de velocidades
int duration, distance, velocidade, velocidadeRot;
int flag_motor_active = 0;

//Sensor ultrasonicos
const int echoPin = 2;
const int trigPin = 3;

//Define valor de curva
int curva = 50;
char letra = '*';
const int buzzer = 12;

int distanciaUltra;
long duracao;

void setup() {
  velocidade = 0; //Define a velocidade dos motores frente
  velocidadeRot = 0; //Define a velocidade da Rotacao

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  
  digitalWrite(led_1, HIGH); //Inicia com os Leds apagados
  digitalWrite(led_2, HIGH); //Inicia com os Leds apagados
  digitalWrite(led_3, HIGH); //Inicia com os Leds apagados
  digitalWrite(led_4, HIGH); //Inicia com os Leds apagados
  
  Serial.begin(9600);
  servoMotor.attach(13); //porta do Servo
  servoMotor.write(posServo); //Comeca o motor na posicao Meio
}

//int ultrassonicDist(int trigPin, int echoPin){
//  //seta o pino com um pulso baixo "LOW" ou desligado
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  
//  //seta o pino com pulso alto "HIGH" ou ligado
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  //pulseIn lê o tempo entre a chamada e o pino entrar em high
//  duracao = pulseIn(echoPin, HIGH);
//  
//  //esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado, tempo de ida e volta do ultrassom
//  //distancia = (duracao/2) / 29.1; 
//
//  return ((duracao/2) / 29.1);
//}

void rotacaoServoMotor(boolean active) {
  //flagServo 1 Esquerda
  //flagServo 0 Meio
  //flagServo 2 Direita

  if (active == true) {
    //Define a flag de apoio
    if (posServo == 20) flagServo = 1;
    else if (posServo == 190) flagServo = 2;

    //Configura o incremento ou decremento do valor do Servo-Motor
    if (flagServo == 1) posServo++;
    else if (flagServo == 2) posServo--;
  } else {
    posServo = 100;
  }
  servoMotor.write(posServo);
}

void motorPare() {
  digitalWrite(motDTF, LOW);
  digitalWrite(motDDF, LOW);
  digitalWrite(motETF, LOW);
  digitalWrite(motEDF, LOW);

  digitalWrite(motDTT, LOW);
  digitalWrite(motDDT, LOW);
  digitalWrite(motETT, LOW);
  digitalWrite(motEDT, LOW);
}

void motorFrente() {
  motorPare();
  analogWrite(motDTF, velocidade);
  analogWrite(motDDF, velocidade);
  analogWrite(motETF, velocidade);
  analogWrite(motEDF, velocidade);
}

void motorRe() {
  motorPare();
  analogWrite(motDTT, velocidade);
  analogWrite(motDDT, velocidade);
  analogWrite(motETT, velocidade);
  analogWrite(motEDT, velocidade);
}

void motorEsquerda() {
  motorPare();
  analogWrite(motDTF, velocidadeRot);
  analogWrite(motDDF, velocidadeRot);
  analogWrite(motETT, velocidadeRot);
  analogWrite(motEDT, velocidadeRot);
}

void motorDireita() {
  motorPare();
  analogWrite(motETF, velocidadeRot);
  analogWrite(motEDF, velocidadeRot);
  analogWrite(motDTT, velocidadeRot);
  analogWrite(motDDT, velocidadeRot);
}

void motorFrente_CurvaEsquerda() {
  motorPare();
  curva = ((velocidade / 100) * 65);

  analogWrite(motDTF, velocidade);
  analogWrite(motDDF, velocidade);
  analogWrite(motETF, velocidade - curva);
  analogWrite(motEDF, velocidade - curva);
}

void motorFrente_CurvaDireita() {
  motorPare();
  curva = ((velocidade / 100) * 65);

  analogWrite(motDTF, velocidade - curva);
  analogWrite(motDDF, velocidade - curva);
  analogWrite(motETF, velocidade);
  analogWrite(motEDF, velocidade);
}

void gerenciaVelocidade() {
  if (flag_motor_active == 0) {
    motorPare();
  } else if (flag_motor_active == 1) {
    motorFrente();
  } else if (flag_motor_active == 2) {
    motorRe();
  } else if (flag_motor_active == 3) {
    motorEsquerda();
  } else if (flag_motor_active == 4) {
    motorDireita();
  } else if (flag_motor_active == 5) {
    motorFrente_CurvaEsquerda();
  } else if (flag_motor_active == 6) {
    motorFrente_CurvaDireita();
  }
}

void sensorIRDireito() {
  if ((digitalRead(IRDireito) == LOW) || ((posServo > 150)  && (distanciaUltra <= 20) && setServoMotor == true)) {
    velocidadeRot = 220; //Define a velocidade da Rotacao
    motorEsquerda();
    delay (210);
    motorPare();
  }
}

void sensorIREsquerdo() {
  if ((digitalRead(IREsquerdo) == LOW) || ((posServo < 150)  && (distanciaUltra <= 20) && setServoMotor == true)) {
    velocidadeRot = 220; //Define a velocidade da Rotacao
    motorDireita();
    delay (210);
    motorPare();
  }
}

void loop() {
  //Serial.print("Distancia da Esquerda: ");
  //distanciaUltra = (ultrassonicDist(trigPin, echoPin)); 
  //Serial.println(distanciaUltra);
  //Serial.println("------------------------------------");

  //Leitura de Sensores Infra-Vermelho
  //sensorIRDireito();
  //sensorIREsquerdo();

  //Verifica a posicao do Servo-Motor
  rotacaoServoMotor(setServoMotor);

  //Verifica as flags de velocidade
  gerenciaVelocidade();

  if (Serial.available() > 0) {
    letra = Serial.read();
    Serial.println(letra);

    //Parametros de velocidade
    switch (letra) {
      case '0':
        velocidade = 1; //Define a velocidade dos motores
        velocidadeRot = 1; //Define a velocidade da Rotacao
        break;
      case '1':
        velocidade = 70;
        velocidadeRot = 90;
        break;
      case '2':
        velocidade = 140;
        velocidadeRot = 140;
        break;
      case '3':
        velocidade = 170;
        velocidadeRot = 170;
        break;
      case '4':
        velocidade = 190;
        velocidadeRot = 190;
        break;
      case '5':
        velocidade = 200;
        velocidadeRot = 200;
        break;
      case '6':
        velocidade = 220;
        velocidadeRot = 220;
        break;
      case '7':
        velocidade = 230;
        velocidadeRot = 230;
        break;
      case '8':
        velocidade = 240;
        velocidadeRot = 240;
        break;
      case '9':
        velocidade = 245;
        velocidadeRot = 245;
        break;
      case 'q':
        velocidade = 255;
        velocidadeRot = 255;
        break;
      case 'F':
        flag_motor_active = 1;
        break;
      case 'B':
        flag_motor_active = 2;
        break;
      case 'L':
        flag_motor_active = 3;
        break;
      case 'R':
        flag_motor_active = 4;
        break;
      case 'G':
        flag_motor_active = 5;
        break;
      case 'I':
        flag_motor_active = 6;
        break;
      case 'H':
        //--------------Nao Habilitado-------------//
        break;
      case 'J':
        //--------------Nao Habilitado-------------//
        break;
      case 'S':
        //Parada automatica
        flag_motor_active = 0;
        break;
      case 'W':
        digitalWrite(led_1, LOW);
        break;
      case 'w':
        digitalWrite(led_1, HIGH);
        break;
      case 'U':
        digitalWrite(led_3, LOW);
        break;
      case 'u':
        digitalWrite(led_3, HIGH);
        break;
      case 'V':
        tone(buzzer, 1700);
        break;
      case 'v':
        noTone(buzzer);
        break;
      case 'X':
        posServo = 20; //Inicia o ciclo
        setServoMotor = true;
        break;
      case 'x':
        setServoMotor = false;
        break;
      case 'D':
        //---------------------------//
        break;
      default:
        // Serial.println("Opcao Invalida");
        break;
    } // end: switch
  }
  delay(10);
}
