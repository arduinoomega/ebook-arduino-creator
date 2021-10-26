#include <IRremote.h>

int pinoRecepitorIR = 2;
int valorRecebido;
int IN1= 3;
int IN2 = 4; 

// Definindo as teclas

int ligaIN1 =  0000000000; // insira os valores capturados
int ligaIN2 =  0000000000; // insira os valores capturados
int desliga =  0000000000; // insira os valores capturados

IRrecv irrecv(pinoRecepitorIR);
decode_results results;

void setup()
{

pinMode(IN1, OUTPUT); // Definindo relé com saída
pinMode(IN2, OUTPUT); // Definindo relé com saída

irrecv.enableIRIn(); // Inicializa o receptor IR do controle remoto

digitalWrite(IN1, HIGH); // Relé inicia desligado
digitalWrite(IN2, HIGH); // Relé inicia desligado
}

void loop()
{
if (irrecv.decode(&results)) // Executa caso receba algum códico
{
valorRecebido = (results.value);

if (valorRecebido == ligaIN1 ) // Se a tecla 1 for acionada 

digitalWrite(IN1, LOW); //Liga o relé IN1

}

if (valorRecebido == ligaIN2 ) // Se a tecla 2 for acionada
{
digitalWrite(IN2, LOW); //Liga o relé IN2

}

if (valorRecebido == desliga ) // Se a tecla 3 for acionada
{
digitalWrite(IN1, HIGH); //desliga o relé
digitalWrite(IN2, HIGH); //desliga o relé

}
irrecv.resume(); 

}
