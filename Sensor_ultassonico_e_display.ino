// Bibliotecas necessárias

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

#define trigger 3 //  pino de trigger  na porta 3
#define echo 2  //  pino de echo  na porta 2
float distancia = 0; 
float tempo = 0;  

void setup() {
  
  lcd.begin (16,2); // Dimensão da tela 
  lcd.setBacklight(HIGH); //Liga a luz de fundo
  
  pinMode(trigger, OUTPUT); //trigger como saída
  digitalWrite(trigger, LOW); // trigger em nível baixo inicialmente
  
  pinMode(echo, INPUT); // echo como entrada de sinal digital
                   
}

void loop() {

  // leitura do sensor
  
  distancia = 0;
  digitalWrite(trigger, HIGH);          
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  tempo = pulseIn(echo, HIGH);          
  tempo = tempo/1000000;                
  distancia = (tempo*340)*50;         

// escreve na tela a distância em cm

  lcd.clear();                         
  lcd.setCursor(0,0);                   
  lcd.print("Dist:");        
  lcd.setCursor(6,0);                   
  lcd.print(distancia);                
  lcd.setCursor(12,0);                 
  lcd.print("cm");                     

  delay(500);                         
}
