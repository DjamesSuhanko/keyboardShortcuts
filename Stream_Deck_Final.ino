#include "Keyboard.h"

// declara os pinos das linhas do teclado                   
int tecladoLinhas[4]{15, 14, 16, 10};  // L0, L1, L2, L3

// declara os pinos das colunas do teclado
int tecladoColunas[5]{2, 3, 4, A1, A0}; // C0, C1, C2, C3, C4   

// declara os pinos das linha dos leds
int ledsLinhas [4]{5,6,A2,A3};

// de clara os pinos das colunas dos leds
int ledsColunas[3]{7,8,9};

bool ledsStatus[12]{
1,0,0,0,
0,0,0,0,
0,0,0,0
};


bool cenasSts[4]{1,0,0,0};
int cenasKeys[4]{KEY_F13,KEY_F14,KEY_F15,KEY_F16};

int  gravacaoKeys[2]{KEY_F21,KEY_F22};
bool muteSts    = false;
int  contMute   = 0;
int  muteKey    = KEY_F23;

bool pauseSts   = false;
int  contPause  = 0;
int  pauseKey    = KEY_F24;

bool iniciarSts = false;


bool redesSts[4]{0,0,0,0};

#define timeRedes1  10  // tempo de exibição em segundos
#define timeRedes2  10
#define timeRedes3  10
#define timeRedes4  10

int timerRedes[4]{timeRedes1,timeRedes2,timeRedes3,timeRedes4};
int redesKeys[4]{KEY_F17,KEY_F18,KEY_F19,KEY_F20};
long time[4]{};

int extrasKeys[8]{KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20};



void setup(){

for(int x=0; x < 5 ; x++){
  pinMode(tecladoColunas[x],OUTPUT);
  digitalWrite(tecladoColunas[x],HIGH);
}

for(int x=0; x < 4; x++){
  pinMode(tecladoLinhas[x],INPUT_PULLUP);
  pinMode(ledsLinhas[x],OUTPUT);  
  digitalWrite(ledsLinhas[x],LOW);
} 

for(int x=0; x < 3; x++){
 pinMode(ledsColunas[x],OUTPUT);  
 digitalWrite(ledsColunas[x],HIGH);
} 

Keyboard.begin();

}// fim do setup



void loop(){


leds();                // atualiza a matriz de leds
int dados = teclado(); // "Lê" a matriz do teclado e retorna um valor entre 0 e 19


// **** SELEÇÃO DE CENAS ****
if(dados >=0 && dados <= 3){
for(byte x=0; x<=4; x++){
if(dados == x){
  ledsStatus[x]=HIGH;

 Keyboard.press(cenasKeys[x]);
  delay(5);
  }
  else
  {
    ledsStatus[x]=LOW;
    }
    }
}
// **************************


// **** REDES SOCIAIS *************************
if(dados >= 8 && dados < 12){ 
  for(byte x=8; x<12; x++)
  {
   if(dados == x){
    redesSts[x-8] = true;
    ledsStatus[x] = HIGH;
    time[x-8]=millis();
     Keyboard.press(redesKeys[x-8]);
     delay(5);
    }}}

// *** TIMER DAS REDES ***
for(byte x=0; x<4; x++){
if(millis() - time[x] >  timerRedes[x] * 1000){
if(redesSts[x]==true){
Keyboard.press(redesKeys[x]);
  ledsStatus[8+x]=LOW;
  redesSts[x]=false;
  delay(5);
}}}

// *******************************************




// *** GRAVAÇÃO *****************

if(dados == 4 || dados == 5){  // Botão "INICIAR" e "PARAR" 
for(byte x = 4; x < 6; x++){
if(dados == x){
ledsStatus[x] = HIGH;
Keyboard.press(gravacaoKeys[x-4]);
if(dados == 4){
  iniciarSts=true;
  } else 
  {
    iniciarSts=false;
    }
pauseSts = false;
}
else
{
  ledsStatus[x]=LOW;
}}}

// *****************************




// **** BOTÃO PAUSE  *****

if(dados == 6){
pauseSts =! pauseSts;
ledsStatus[4]=LOW; // apaga o led do botão iniciar
Keyboard.press(pauseKey);
}


if(pauseSts == true){
 contPause ++;
 if(contPause >= 20){
   ledsStatus[6] =! ledsStatus[6];
    contPause = 0;
  }
}
  else
  {
    ledsStatus[6]=LOW;
    if(iniciarSts == true)// se a gravação estava rodando...
    {
      ledsStatus[4]=HIGH; // reativa o led de gravação
      }
    }
  

// *****************



// **** BOTÃO MUTE  *****

if(dados == 7){
muteSts =! muteSts;
Keyboard.press(muteKey);
}


if(muteSts == true){
 contMute ++;
 if(contMute >= 20){
   ledsStatus[7] =! ledsStatus[7];
    contMute = 0;
  }
}
  else
  {
    ledsStatus[7]=LOW;
    }
  

// *****************





// **** EXTRAS *******************

if (dados >= 12 && dados <= 19){
for(byte x = 12; x < 20; x++)
{
  if(dados==x){
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press(extrasKeys[x-12]);
  delay(5);
}}}

// ******************



 // "SOLTA" QUALQUER TECLA QUE TENHA SIDO PRESSIONADA
  Keyboard.releaseAll();

}// fim do loop
