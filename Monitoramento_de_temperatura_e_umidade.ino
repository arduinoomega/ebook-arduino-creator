// Incluindo bibliotecas necessárias 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>
int DHTPIN = A0; // Sensor está no porta analógica A0

#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);



LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 


// Simbolo de grau

byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};
 
void setup(){ // inicia o void setup
  
 lcd.begin (16,2); // Dimensão da tela 
 lcd.setBacklight(HIGH); //Liga a luz de fundo
 lcd.createChar(0, grau);
 dht.begin(); 
}
 
void loop(){ // inicia o void loop
  
float h = dht.readHumidity(); // Faz a leitura da Umidade 
float t = dht.readTemperature(); // Faz a leitura da Temperatura

// Imprime o valor da Temperatura na tela 

lcd.setCursor(0,0);
lcd.print("TEMP: ");
lcd.print(" ");
lcd.setCursor(7,0);
lcd.print(t,1);
lcd.setCursor(12,0);
lcd.write((byte)0);
 
// Imprime o valor da Umidade na tela 

lcd.setCursor(0,1);
lcd.print("UMID: ");
lcd.print(" ");
lcd.setCursor(7,1);
lcd.print(h,1);
lcd.setCursor(12,1);
lcd.print("%");
 
delay(2000);
}
