#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <string>

// Fingerprint da URL
// const uint8_t fingerprint[20] = {0xB3, 0x3F, 0x76, 0x00, 0x4D, 0x83, 0x11, 0xAE, 0xDA, 0x2D, 0x94, 0x0F, 0xB0, 0x92, 0x53, 0x3F, 0x80, 0x49, 0x3A, 0xC5};
//Fingerprint do Wi-Fi usado

const uint8_t fingerprint[20] = {0x2B, 0xB5, 0xF0, 0x49, 0xBB, 0x7A, 0xDE, 0xCB, 0x2F, 0x32, 0x67, 0x2E, 0x10, 0xD5, 0x45, 0x3E, 0xBE, 0x2C, 0x18, 0x0B};
//Fingerprint do roteador do celular usado

#define RST_PIN  D3     // pino RST do leitor, no pino D3 do microcontrolador
#define SS_PIN   D4     // pino SS do leitor, no pino D4 do microcontrolador

//Chamando as funções das bibliotecas do RFID e do ESP8266
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
ESP8266WiFiMulti WiFiMulti;
MFRC522::StatusCode status;      

int blockNum = 2;  

// Criar outro array pra ler os dados do bloco
// Tamanho do buffer tem que ser 2 Bytes a mais do que o tamanho do bloco (16 Bytes)
byte bufferLen = 18;
byte readBlockData[18];

String data2;
const String data1 = "https://script.google.com/macros/s/AKfycbyhVQRw80ZsAbWkVLXm58_uX0W1rBackqwGgrzV8GzGYMWS9zxjcHL7-VBhOBsxdyBi/exec?name=";
// Essa será a URL usada para fazer a requisição para o Google Sheets
void setup() 
{
  // Inicializa o serial para fazer a comunicação com o PC
  Serial.begin(9600);

  /*STATUS DE INICIALIZAÇÃO:
  Serial.println();
  Serial.println();
  Serial.println();

  Serial.printf("Espere\n");
  for (uint8_t t = 4; t > 0; t--) 
  {
    Serial.printf("%d...\n", t);
    Serial.flush();
    delay(1000);
  }
  */

  WiFi.mode(WIFI_STA);
  
  // Aqui coloca o nome e a senha do Wi-Fi
<<<<<<< HEAD
  WiFiMulti.addAP("iPhone de Wesley", "12345678");
=======
  WiFiMulti.addAP("Nome Wi-fi", "Senha Wi-fi");
>>>>>>> 89475dd20a24fb3ba5ffd1e020647ad101d1b08b

  // Inicializa o SPI (Biblioteca usada para fazer a comunicação entre o leitor RFID com o microcontrolador)
  SPI.begin();

  rfid.PCD_Init();

  //Inicia o Wi-Fi do aparelho
  WiFiMulti.run(WL_CONNECTED);

  // Testando conexão com Wi-Fi
  int w=0;
  while(w<1){
    if ((WiFiMulti.run() == WL_CONNECTED)){
      Serial.println("Wi-Fi conectado.");
      w++;
    }else{
      Serial.println("Wi-Fi não conectado. Confira o Wi-Fi.");
    }
  }

}

void loop()
{

  // Inicializa o módulo MFRC522 (Leitor do cartão)
  mfrc522.PCD_Init();
  //Esperando por algum cartão
  // Reseta o loop se nenhum cartão se aproximar do leitor MFRC522
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  /*STATUS DE LEITURA:
  // Quando algum cartão for aproximado, o leitor registra o ID do cartão no monitor serial
  Serial.println();
  Serial.println(F("Reading last data from RFID..."));
  */

  String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      String currByte = String(mfrc522.uid.uidByte[i]);

      uid = uid + currByte;
  }
  Serial.println(uid);
  
  // Esperando a conexão Wi-Fi
  if ((WiFiMulti.run() == WL_CONNECTED)) 
  {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
  
    //Concatenando o ID do cartão com a URL do Google Sheets
    data2 = data1 + uid;
    data2.trim();

    /* STATUS DE REQUISIÇÃO:
    Serial.println(data2);
    */
    
    HTTPClient https;
    
    /*STATUS DE CONEXÃO:
    Serial.print(F("[HTTPS] begin...\n"));
    */
    if (https.begin(*client, (String)data2))
    {  

      /* STATUS DE CONEXÃO:
      // HTTP
      Serial.print(F("[HTTPS] GET...\n"));
      */

      // Innicia a conexão e manda o leitor HTTP
      int httpCode = https.GET();
    
      // httpCode será negativo se der erro
      if (httpCode > 0) 
      {

        /* STATUS DE CONEXÃO:
        // A requisição HTTP foi enviada e a resposta do servidor foi tratada
        Serial.printf("[HTTPS] GET... resposta: %d\n", httpCode);
        */
        
      }
      else 
      {
        Serial.printf("[HTTPS] GET... FALHOU, ERRO: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
      delay(1000);
    } 
    else 
    {
      Serial.printf("[HTTPS] Não foi possível se conectar\n");
    }
  }else{
    
  }
}
