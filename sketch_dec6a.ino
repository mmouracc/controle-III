//Leitura de distância com o sensor HC-SR04
#include <Ultrasonic.h>
 Ultrasonic ultrassom(4,2); // define o nome do sensor(ultrassom)
//e onde esta ligado o trig(4) e o echo(2) respectivamente
long distancia;
// Esta função "setup" roda uma vez quando a placa e ligada ou resetada
 void setup() {
 Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
 
 }
// Função que se repete infinitamente quando a placa é ligada
 void loop()
 {
   distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
                                     // centímetros(CM) ou polegadas(INC)
   Serial.print(distancia); //imprime o valor da variável distancia
   Serial.println("cm");
   delay(100);
 }