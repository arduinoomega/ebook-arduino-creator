// bibliotecas necessárias

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

// definindo portas 

int Led = 3; 
int buzzer = 2; 
int sensorD = 4; 
int sensorA = A0;

void setup(){
  
 lcd.begin (16,2); // Dimensão da tela 
 lcd.setBacklight(HIGH); //Liga a luz de fundo

 // definindo portas como entrada ou saída
 
  pinMode(sensorD, INPUT); 
  pinMode(sensorA, INPUT); 
  pinMode(Led, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
  
}
void loop(){

  
    lcd.setCursor(3,0);
    lcd.print("Sem Chuva");

  if(digitalRead(sensorD) == LOW){ // se o sensor estiver molhado
    
      digitalWrite(Led, HIGH); // liga LED
      lcd.setCursor(0,0);
      lcd.print("Comecou a Chover"); // escreve na tela
      tone(buzzer, 1500,1000); // aciona o buzzer
      delay(1000);
      lcd.clear();
      
  }else{ // se não nada acontece
    
    digitalWrite(Led, LOW); 
    noTone(buzzer);
  
  }
}
