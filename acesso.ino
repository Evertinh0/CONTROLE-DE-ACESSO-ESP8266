//AUTOR: EVERTON YAN DE JESUS SOUZA
//DATA CRIAÇÃO: 03 DE SETEMBRO DE 2022

//====SERÁ INCLUIDA AS BIBLIOTECAS QUE SERÃO USADAS====//

#include <rdm6300.h>
#include <SoftwareSerial.h>
SoftwareSerial RFID (12); // RX-D6 E TX-D7

//====SERÁ DEFINIDO AS VARIAVEIS E PINOS CORRESPONDENTE====//

#define RDM6300_RX_PIN 12 //D6
#define LED_VERDE 4 //D2
#define LED_VERMELHO 5 //D1
#define ACESSO_RELE 1000
#define SEM_ACESSO_RELE 1000

Rdm6300 rdm6300; 

int RELE = 16; //D0
String text;
String NumeroCartao; 

//==== SERÁ INICIADO TODOS OS COMPONENTES====//

void setup()
{
  Serial.begin(9600);
  pinMode(LED_VERDE,OUTPUT); //DEFINDO COMO PINO DE SAIDA
  pinMode(LED_VERMELHO, OUTPUT); //DEFINDO COMO PINO DE SAIDA
  pinMode(RELE, OUTPUT); //DEFINDO COMO PINO DE SAIDA

  digitalWrite(LED_VERDE, LOW); //DEFINDO COMO LOW = 0(DESLIGADO)
  digitalWrite(LED_VERMELHO, LOW); //DEFINDO COMO LOW = 0(DESLIGADO)
  digitalWrite(RELE, LOW); //DEFINDO COMO LOW = 0(DESLIGADO)
  
  rdm6300.begin(9600);
  RFID.begin(9600);
  Serial.println("APROXIME O CARTAO...");

  setup_cartao();

}
char c;

//===SERÁ FEITO A CHECAGEM DOS CARTÕES===//

void loop()
{
  while (RFID.available() > 0) {
    delay(5);
    c = RFID.read();
    text += c;
  }
  if (text.length() > 20)
  check();
  text = "";
}

void check()
{
  text = text.substring(1, 11);
  Serial.println("Card ID : " + text);
  Serial.println("Access ID : " + NumeroCartao);

//===SERÁ USADO A LOGICA: SE O CARTÃO ESTIVER CADASTRADO, EXECUTE A INSTRUÇÃO 01, SE NÃO, EXECUTE A INSTRUÇÃO 02==//
  

//===INSTRUÇÃO 01===//

  if (NumeroCartao.indexOf(text) >= 0) { 
    Serial.println("ACESSSO PERMITIDO");
    Serial.println();
    delay(100);
    digitalWrite(RELE, LOW);
    digitalWrite(LED_VERDE, HIGH);
    delay(ACESSO_RELE);
    
    digitalWrite(RELE, HIGH);
    digitalWrite(LED_VERDE, LOW);
    delay(1500);
    digitalWrite(RELE, LOW);
  }

//===INSTRUÇÃO 02===//

  else {
    Serial.println("ACESSO NEGADO");
    digitalWrite(LED_VERMELHO, HIGH);
    delay(SEM_ACESSO_RELE);
    digitalWrite(RELE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
  }
  Serial.println(" ");
  Serial.println("APROXIME O CARTÃO …");
}
