int teclado(){
  
   int n =0;
  
for(int x=0; x < 5; x++)
{
  digitalWrite(tecladoColunas[x],LOW);
  
for(int y=0; y<4; y++)
{

  if(digitalRead(tecladoLinhas[y])==LOW)
  {
while(digitalRead(tecladoLinhas[y])==LOW){ // evita acionamentos multiplos caso o botão seja mantido pressionado.
  delay(50);
  }
    
 //   Serial.print("Coluna = ");
 //   Serial.print(x);
  //  Serial.print(" Linha = ");
  //  Serial.print(y);

  //  Serial.print(" Numero = ");
  //  Serial.println(n);
return n;
//break;
      
  //  delay(300);
    }
     n++;
  }
  
  digitalWrite(tecladoColunas[x],HIGH);
  }

  return 20;
  
  
  
  }
