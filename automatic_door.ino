#include<LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte ctrl_key = 3;
const byte m_pins[2] ={12,13};
void setup() {
  lcd.begin(16,2);
  pinMode(ctrl_key ,INPUT_PULLUP);
  for (int i=0 ; i<2 ;i++)
    pinMode(m_pins[i],OUTPUT);
    
}
bool gate_state = false;
int counter =0; //0 -close , 1-open
long start_time =0;
long timestep =500;
void loop() {
 if(!digitalRead(ctrl_key)){
  while(!digitalRead(ctrl_key));
  gate_state ^=1;
  start_time = millis();
 }
 lcd.setCursor(1,0);
 lcd.print(counter);
 lcd.print(" ");
if(gate_state ==0){ //to colse or closed
  if(counter ==0){ //closed
    lcd.setCursor(0,1);
    lcd.print("Gate closed");
    gate_none();
    }else { //closing 
       gate_off();
     lcd.setCursor(0,1);
     lcd.print("Gate closing");
     if(millis() - start_time >= timestep){
      start_time = millis();
      if (counter >0){
        counter --;   
      }
     
     }
  }
} else{ //to open or opened
  if(counter ==10){ //opened
    lcd.setCursor(0,1);
    lcd.print("Gate opened");
    gate_none();
  }else{//opening
     gate_on();
    lcd.setCursor(0,1);
    lcd.print("Gate opening");
    if(millis() - start_time >= timestep){
      start_time = millis();
      if(counter <10){
        counter++;
      }
     
    }
  }
}
}
void gate_on(){
  digitalWrite(m_pins[0],1);
  digitalWrite(m_pins[1],0);
  }

 void gate_off(){
  digitalWrite(m_pins[0],0);
  digitalWrite(m_pins[1],1);
  }
void gate_none(){
  digitalWrite(m_pins[0],0);
  digitalWrite(m_pins[1],0);
}
