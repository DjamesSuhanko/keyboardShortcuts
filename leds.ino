void leds(){

  byte index=0;
  
  for(int x=0; x<3; x++){
    
 digitalWrite(ledsColunas[x],LOW);

  for(int y=0; y<4; y++){   
  
 boolean aux = ledsStatus[index];
 
digitalWrite(ledsLinhas[y], aux);


index ++;
 
  } 
 delay(8); // diminui o efeito das piscadas dos leds resultante da multiplexação 
 digitalWrite(ledsColunas[x],HIGH);
 
  }
  

  
}// fim do loop
