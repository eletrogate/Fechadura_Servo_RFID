#include <SPI.h>                                   //Inclusão das bibliotecas
#include <MFRC522.h>

#define ss 10                                     //Define os pinos ss e rst
#define rst 9 

MFRC522 rfid(ss, rst);

void setup() {
  Serial.begin(9600);                             //Inicia o Monitor Serial
  SPI.begin();                                    //Inicia o SPI
  rfid.PCD_Init();                                //Inicia o leitor
}

void loop() {
  String id = "";                                  //Cria a variável "id"
  
  //Se não houver nenhum cartão, não faz nada
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
     return;
  } 
  
  id = le_cartao();                               //Chama a função e imprime a uid lida             
  Serial.println(id)
}

String le_cartao() {  
  String _id = "";                                //Cria a variável "_id"
  for (byte i = 0; i < 4; i++) {                  //Loop for para percorrer os caracteres lidos, seguindo o formato proposto
    _id += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
  }
    
  _id.toUpperCase();                              //Transforma as letras em caixa alta
  rfid.PICC_HaltA();                              //Para a criptografia
  rfid.PCD_StopCrypto1(); 

  return _id;                                     //Retorna a uid lida
}