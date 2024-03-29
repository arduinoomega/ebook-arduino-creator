// Incluindo Bibliotecas Necessárias

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

#include <SPI.h> 
#include <MFRC522.h> 


#define SS_PIN 10 //Pino SDA no Pino Digital D4
#define RST_PIN 9 //Pino RST Pino Digital D4

MFRC522 rfid(SS_PIN, RST_PIN); 


int Buzzer = 8;

int ledverde = 6;

int ledverm = 7;


void setup(){

   lcd.begin (16,2); // Dimensão da tela 
  lcd.setBacklight(HIGH); //Liga a luz de fundo
 
  
  

  // Iniciando as bibliotecas
  
  Wire.begin(); 
  SPI.begin(); 
  rfid.PCD_Init(); 


// Definindo o Buzzer como Saída Digital

 pinMode(Buzzer, OUTPUT);
 pinMode(ledverde, OUTPUT);
 pinMode(ledverm, OUTPUT);
 digitalWrite(Buzzer, LOW);


// Inicia o lcd 

 lcd.setCursor(0,0); // coluna 0, linha 0
 lcd.print("  INSIRA A TAG");  // Escreve no Display 
  

   
}

void loop() {
  leituraRfid(); 
}

//Função de validação da TAG
void leituraRfid(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) 
    return;


  String strID = ""; 
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();


  //Insira a UID da tag capturada anteriormente
  
  if (strID.indexOf("B3:80:F7:0A") >= 0) { // Se a TAG for correta 

 
  int qtd_bips = 2; //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){
    
    // Ligando o Buzzer com uma frequência de 1500 hz

 lcd.clear();
 lcd.setCursor(0,0); // coluna 0, linha 0
 lcd.print("ACESSO  LIBERADO"); // Escreve no Display  
    
    tone(Buzzer,1500);
    digitalWrite(ledverde, HIGH);
    delay(100);  
    noTone(Buzzer);
    digitalWrite(ledverde, LOW);
    delay(100);
  }

  delay(2000);

  lcd.clear(); // Limpa lcd
  lcd.setCursor(0,0); // coluna 0, linha 0
  
  lcd.print("  INSIRA A TAG");  // Escreve no Display 
    
  }else{ //SENÃO, FAZ (CASO A TAG LIDA NÃO SEJÁ VÁLIDA)
    int qtd_bips = 1;  //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){   
    //Ligando o Buzzer com uma frequência de 500 hz
   

 lcd.clear(); // Limpa lcd
 lcd.setCursor(0,0); // coluna 0, linha 0
 lcd.print(" ACESSO  NEGADO ");  // Escreve no Display 
 
    tone(Buzzer,500);
    digitalWrite(ledverm,HIGH);
   
   
    delay(500); 
      
    // Desligando o Buzzer 

   digitalWrite(ledverm,LOW);
   noTone(Buzzer);
   delay(1000);

    lcd.clear(); // Limpa lcd 
    
    lcd.setCursor(0,0); // coluna 0, linha 0
    lcd.print("  INSIRA A TAG"); 

  }  
  
  }

  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1();
  }
