//Projeto RX_02 10/07/2018
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

//Sesor Fotoeletrico
int IRDireito = 52; // Escolhe pino de entrada para Sensor Infravermelho Direito
int IREsquerdo = 53; // Escolhe pino de entrada para Sensor Infravermelho Esquerdo

// variavel para leitura de status
int valorStatus = 0;

//Declaracao de velocidades
int duration, distance, velocidade, velocidadeRe, velocidadeRot;
int flag_motor_active = 0;

//Define valor de curva
int curva = 50;

char letra = '*';
const int buzzer = 24;

void setup() {
  velocidade = 0; //Define a velocidade dos motores frente
  velocidadeRot = 0; //Define a velocidade da Rotacao
  velocidadeRe = 0; //Define a velocidade dos motores Re
  Serial.begin(9600);
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

  //Parar tracao trazeira
  digitalWrite(motDTT, LOW);
  digitalWrite(motDDT, LOW);
  digitalWrite(motETT, LOW);
  digitalWrite(motEDT, LOW);
}

void motorRe() {
  motorPare();
  analogWrite(motDTT, velocidadeRe);
  analogWrite(motDDT, velocidadeRe);
  analogWrite(motETT, velocidadeRe);
  analogWrite(motEDT, velocidadeRe);

  //Parar tracao Dianteira
  digitalWrite(motDTF, LOW);
  digitalWrite(motDDF, LOW);
  digitalWrite(motETF, LOW);
  digitalWrite(motEDF, LOW);
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
  curva = ((velocidade/100) * 65);
  
  analogWrite(motDTF, velocidade);
  analogWrite(motDDF, velocidade);
  analogWrite(motETF, velocidade - curva);
  analogWrite(motEDF, velocidade - curva);
}

void motorFrente_CurvaDireita() {
  motorPare();
  curva = ((velocidade/100) * 65);
  
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
  valorStatus = digitalRead(IRDireito);
  if (valorStatus == LOW) {
    //Serial.println("Sensor IRDireito Ativado");
    tone(buzzer,1730,100);
    velocidadeRot = 220; //Define a velocidade da Rotacao
    motorEsquerda();
    delay (210);
    motorPare();
    delay(100);
  }
}

void sensorIREsquerdo() {
  valorStatus = digitalRead(IREsquerdo);
  if (valorStatus == LOW) {
    //Serial.println("Sensor IREsquerdo Ativado");
    tone(buzzer,1730,100);
    velocidadeRot = 220; //Define a velocidade da Rotacao
    motorDireita();
    delay (210);
    motorPare();
    delay(100);
  }
}

void loop() {
  //Leitura de Sensores Infra-Vermelho
  sensorIRDireito();
  sensorIREsquerdo();

  //Verifica as flags de velocidade
  gerenciaVelocidade();

  if (Serial.available() > 0) {
    letra = Serial.read();
    Serial.println(letra);

    //Parametros de velocidade
    switch (letra) {
      case '0':
        velocidade = 1; //Define a velocidade dos motores frente
        velocidadeRot = 1; //Define a velocidade da Rotacao
        velocidadeRe = 1; //Define a velocidade dos motores Re
        break;
      case '1':
        velocidade = 70;
        velocidadeRot = 90;
        velocidadeRe = 70;
        break;
      case '2':
        velocidade = 140;
        velocidadeRot = 140;
        velocidadeRe = 140;
        break;
      case '3':
        velocidade = 170;
        velocidadeRot = 170;
        velocidadeRe = 170;
        break;
      case '4':
        velocidade = 190;
        velocidadeRot = 190;
        velocidadeRe = 190;
        break;
      case '5':
        velocidade = 200;
        velocidadeRot = 200;
        velocidadeRe = 200;
        break;
      case '6':
        velocidade = 220;
        velocidadeRot = 220;
        velocidadeRe = 220;
        break;
      case '7':
        velocidade = 230;
        velocidadeRot = 230;
        velocidadeRe = 230;
        break;
      case '8':
        velocidade = 240;
        velocidadeRot = 240;
        velocidadeRe = 240;
        break;
      case '9':
        velocidade = 245;
        velocidadeRot = 245;
        velocidadeRe = 245;
        break;
      case 'q':
        velocidade = 255;
        velocidadeRot = 255;
        velocidadeRe = 255;
        break;
      case 'F':
        flag_motor_active = 1;
        motorFrente();
        break;
      case 'B':
        flag_motor_active = 2;
        motorRe();
        break;
      case 'L':
        flag_motor_active = 3;
        motorEsquerda();
        break;
      case 'R':
        flag_motor_active = 4;
        motorDireita();
        break;
      case 'G':
        flag_motor_active = 5;
        motorFrente_CurvaEsquerda();
        break;
      case 'I':
        flag_motor_active = 6;
        motorFrente_CurvaDireita();
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
        motorPare();
        break;
      case 'W':
        //---------------------------//
        break;
      case 'w':
        //---------------------------//
        break;
      case 'U':
        //---------------------------//
        break;
      case 'u':
        //---------------------------//
        break;
      case 'V':
        tone(buzzer,1730);
        break;
      case 'v':        
        noTone(buzzer);
        break;
      case 'X':
        //---------------------------//
        break;
      case 'x':
        //---------------------------//
        break;
      case 'D':
        //---------------------------//
        break;
      default:
        //Serial.println("Opcao Invalida");
        //motorPare();
        break;
    } // end: switch
  }
  delay(10);
}
