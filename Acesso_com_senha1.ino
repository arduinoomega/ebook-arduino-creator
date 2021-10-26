
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

#include <Password.h>   // Inclui biblioteca Password.h
#include <Keypad.h>       // Inclui biblioteca Keypa.h
                                       
#define buzzer 2           // Define a porta 2 como buzzer 
 
Password senha = Password("1234");      // Senha para liberação de acesso
 
const byte linha = 4;     // Define número de linhas
const byte coluna = 4;    // Define número de colunas
 
// Relaciona linha e colunas para determinação dos caracteres
char keys[linha][coluna] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 
byte pinolinha[linha] = {10, 9, 8, 7};       // Declara os pinos de interpretação das linha
byte pinocoluna[coluna] = {6, 5, 4, 3};      // Declara os pinos de interpretação das coluna
 
Keypad keypad = Keypad(makeKeymap(keys), pinolinha, pinocoluna, linha, coluna);
 
void setup() {

  
  lcd.begin (16,2); // Dimensão da tela 
  lcd.setBacklight(HIGH); //Liga a luz de fundo
  pinMode(buzzer, OUTPUT);           // Declara o pino como um pino de Saída de sinal
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  keypad.setDebounceTime(5);         // Tempo de atraso para leitura das teclas.
  
}
 
void loop() {
  lcd.setCursor(0,0); // coluna 0, linha 0
  lcd.print(" INSIRA A SENHA");  // Escreve no Display
  keypad.getKey();
}
 

void keypadEvent(KeypadEvent eKey) {
    switch (keypad.getState()) {
      case PRESSED:
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        switch (eKey) {
          case 'C': verificasenha();
            break;
          default:
            senha.append(eKey);
        }
    }
  }
 
// Verifica o senha digitada após pressionar C
void verificasenha() {
  
  if (senha.evaluate()) {

 int qtd_bips = 2; //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){

    lcd.setCursor(0,0);
    lcd.print(" ACESSO LIBERADO");
    tone(buzzer,1500);
 
    delay(100);  
    
    noTone(buzzer);
    delay(100);
  }
 
    delay(2000);
   
    senha.reset();
    lcd.clear();
    
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(" SENHA INVALIDA!");
    int qtd_bips = 1;  //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){   

 //Ligando o Buzzer com uma frequência de 500 hz

    tone(buzzer,500);
    delay(500); 
      
// Desligando o Buzzer 

noTone(buzzer);
delay(1000);

  }
 
    lcd.clear();
    senha.reset();
  }  }
