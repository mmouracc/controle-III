// Proyecto Bola y Barra

//Librerías servo y sensor láser
#include <Servo.h>
#include <Ultrasonic.h>

// Ganancias PID;
double Kp = 0, Ki = 0, Kd = 0;

// Variable posición y posición deseada
int pos = 0;
int setPoint = 12;

// Variables PID
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError, cumError, rateError;
double outPut;

// Distacias medidas
int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING


// Se define el servo y el sensor
Servo myservo;
const int echoPin = 2; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 4; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO

void setup() {
Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
// Pin donde está conectado el servo
  myservo.attach(6);

}

void loop() {
// Se obtiene la distancia del sensor
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  Serial.print("Distancia "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(result); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.println("cm"); //IMPRIME O TEXTO NO MONITOR SERIAL

// Se asigna la posición del servomotor en grados 
  pos = PID(distancia) + 95;
// Se limita el valor de la posición del servo para
// que no exceda los límites
  limite();
//Se manda la posición al servomotor
  myservo.write(pos);

// Se imprimen los valores para graficar en el serial plotter
  Serial.print(setPoint);
  Serial.print(" ");
  delay(10);
}

//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
 }
void limite(void)
{ 
  // Si la posición se pasa de 130 que se mantenga en 130
  if (pos > 130)
  {
    pos = 130;
  }
  // Si la posición es menos de 60 que se mandenga en 60
  if (pos < 60)
  {
    pos = 60;
  }
}
double PID(float input)
{ 
  // Se guarda el tempo actual 
  currentTime = millis();
  // Se calcula el tiempo transcurrido
  elapsedTime = currentTime - previousTime;

  // Se obtiene el error de posición
  error = setPoint - input;
  // Se calcula la integral del error
  cumError += error * elapsedTime;
  // Se calcula la derivada del error
  rateError = (error - lastError) / elapsedTime;
  // Se calcula la salida del controlador
  outPut = Kp * error + Ki * cumError + Kd * rateError;

  // El error actual se convierte en el error pasado
  lastError = error;
  // El tiempo actual se convierte en el tiempo pasado
  previousTime = currentTime;

  // Se regresa la salida del controlador
  return outPut;
}
