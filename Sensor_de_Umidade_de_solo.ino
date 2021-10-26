// Incluindo bibliotecas

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 


int umidade;
int led = 2; 
 
void setup()
{

 lcd.begin (16,2); // Dimensão da tela 
 lcd.setBacklight(HIGH); //Liga a luz de fundo
 
 pinMode(led, OUTPUT); // definindo led com saída
}
void loop()
{

 umidade = analogRead(A0);
 int Porcento = map(umidade, 1023, 0, 0, 100);

// mostra a porcentagem de umidade na tela  

 lcd.setCursor(0,0);
 lcd.print("Umidade:");
 lcd.setCursor(9,0);
 lcd.print(Porcento);
 lcd.setCursor(11,0);
 lcd.print("%");

 // se a porcentagem for menor ou igual a 20
 
 if(Porcento <=20){  // você pode alterar esse valor se achar necessário

 // uma mensagem de aviso surge na tela e o LED é ligado 
 
 lcd.setCursor(0,1);
 lcd.print("Umidade Baixa !");
 lcd.setCursor(0,0);
 lcd.print("Umidade:");
 
 lcd.setCursor(9,0);
 lcd.print(Porcento);

 lcd.setCursor(11,0);
 lcd.print("%");
 digitalWrite(led, HIGH);
 delay(1000);
 lcd.clear();
 
 }else{
 
 digitalWrite(led, LOW);
 
 delay(1000);
 }}
