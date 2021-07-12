/* Código Fonte */ 
/* Projeto Samsung */
/* Programa: Alarme com Sensor de gás/fumaça MQ-2*/
/* Obs: É preciso que o arquivo esteja em uma pasta com 
        mesmo nome do arquivo (Alarme_SensorMQ-2)
*/

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2); 

//Definções dos pinos
const int pin_Sensor = A0; //Pino Sensor
const int pin_Buzzer = 3; //Pino Buzzer 

//LED RGB - Portas Digitais
const int pin_LedRed = 13;
const int pin_LedBlue = 12;
const int pin_LedGreen = 11;

int nivelGas = 40; //Variável para selecionar a quantidade de Gás/Fumaça detectada
int valor_analogico = 0; //Variável le o sensor e armazena a quantidade de Gás/Fumaça

void setup() {
  Serial.begin(9600); //Inicia porta Serial
  pinMode(pin_Sensor,INPUT); //Define o pino de leitura do Sensor como ENTRADA
  
  // Define pinos Leds e Buzzer como SAíDA
  pinMode(pin_Buzzer, OUTPUT);
  pinMode(pin_LedRed, OUTPUT);
  pinMode(pin_LedBlue, OUTPUT);
  pinMode(pin_LedGreen, OUTPUT);
  
  lcd.init(); //Inicializa o LCD
  lcd.backlight(); //Ativa led de backlight (Luz de Fundo) 
  lcd.clear(); //Limpa a tela
}

void loop() {
  //Le os dados do pino analogico A0 do sensor
  int valor_analogico = analogRead(pin_Sensor);
  valor_analogico = map(valor_analogico, 0, 1023, 0, 100); //Faz a conversão da variável para porcentagem

  //Mostra os dados no serial monitor
  Serial.print("Nivel Gas: ");
  Serial.println(valor_analogico);
  
  //Verifica o nivel de gas/fumaca detectado
  if(valor_analogico > nivelGas){
    //Acendendo LED RGB - Vermelho
    digitalWrite(pin_LedRed, LOW);
    digitalWrite(pin_LedGreen, HIGH);
    digitalWrite(pin_LedBlue, HIGH);
  
    lcd.clear();
    lcd.setCursor(1,0);          
    lcd.print("Gas Detectado!");
    tone(pin_Buzzer, 500, 500); //Dispara alarme de vazamento ou possível incêndio
  }else{
    //Acendendo LED RGB - Verde
    digitalWrite(pin_LedRed, HIGH);
    digitalWrite(pin_LedGreen, LOW);
    digitalWrite(pin_LedBlue, HIGH);
    
    lcd.clear();
    lcd.setCursor(3,0); //Selecionando Coluna 4 e Linha 1          
    lcd.print("Nenhum Gas"); 
    lcd.setCursor(3,1); //Selecionando Coluna 4 e Linha 2          
    lcd.print("Detectado!");
  }
  digitalWrite(pin_Buzzer, LOW); //Desliga o alarme
  delay(1000);
}
