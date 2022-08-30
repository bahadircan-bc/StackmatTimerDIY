#include <LiquidCrystal.h>



#define LEFTSENSOR 3

#define RIGHTSENSOR 2

#define RESETBUTTON 5



void printlcd(int ,int);

int numdigit(int num);

void printfinaltime(int time, int cursorpos);



LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6);



int readyflag;

int HOLDTIME = 300; //millis



int timeelapsed = 0;

int lastprintedtime = 0;

int start_readytimer = 0;

int end_readytimer = 0;

int start_solvetime = 0;

int end_solvetime = 0;

int resetflag = 1;



void setup() {

Serial.begin(9600);



lcd.begin(16,2);

lcd.clear();

lcd.home();

int written = lcd.print("Ready!");

Serial.print("Serial com open.\n");

pinMode(LEFTSENSOR, INPUT);

pinMode(RIGHTSENSOR, INPUT);



}



void loop() {

if(digitalRead(RESETBUTTON)){

lcd.clear();

lcd.home();

lcd.print("Ready!");

if(lastprintedtime){

lcd.setCursor(0,1);

lcd.setCursor(0,1);

lcd.print("Last solve ");

printfinaltime(lastprintedtime,11);

}

while(digitalRead(RESETBUTTON))

{

if(digitalRead(LEFTSENSOR) && digitalRead(RIGHTSENSOR))

{

Serial.print("exit\n");

while(digitalRead(LEFTSENSOR) || digitalRead(RIGHTSENSOR)||digitalRead(RESETBUTTON))

;

}

}

resetflag=1;

}

if(digitalRead(LEFTSENSOR) && digitalRead(RIGHTSENSOR) && resetflag){

readyflag = 1;

start_readytimer = millis();

while(digitalRead(LEFTSENSOR) && digitalRead(RIGHTSENSOR)){

end_readytimer = millis();

if(end_readytimer-start_readytimer > HOLDTIME){

lcd.clear();

lcd.print("GO!");

readyflag = 1;

lastprintedtime = 0;

break;

}

else{

readyflag = 0;

}

}

while(digitalRead(LEFTSENSOR) && digitalRead(RIGHTSENSOR))

;

}



if(readyflag && resetflag){

start_solvetime = millis();

while(!(digitalRead(LEFTSENSOR) && digitalRead(RIGHTSENSOR))){

timeelapsed = millis()-start_solvetime;

printlcd(timeelapsed,lastprintedtime);

lastprintedtime = timeelapsed;

}

end_solvetime = millis();

timeelapsed = end_solvetime - start_solvetime;

lastprintedtime = timeelapsed;

lcd.clear();

lcd.setCursor(0,0);

lcd.print("Stop!");

printfinaltime(timeelapsed,0);

Serial.println(timeelapsed/10);

resetflag = 0;

readyflag = 0;

}

}





void printlcd(int time, int oldtime){

int sec = time/1000;

int ms = time%1000;

if(oldtime == 0 || oldtime/1000 != sec){

lcd.setCursor(0,1);

lcd.print(sec);

lcd.print(":");

lcd.print(ms);

}

else {

lcd.setCursor(numdigit(oldtime/1000)+1,1);

lcd.print(ms);

}

}



void printfinaltime(int time, int cursorpos){

int sec = time/1000;

int ms = time%1000;

lcd.setCursor(cursorpos,1);

lcd.print(sec);

lcd.print(":");

lcd.setCursor(cursorpos + numdigit(sec)+1,1);

switch(numdigit(ms)){

case 3:

lcd.print(ms); break;

case 2:

lcd.print("0"); lcd.print(ms); break;

case 1:

lcd.print("00"); lcd.print(ms); break;

}

}



int numdigit(int num){

if(num==0)

return 1;

int result = 0;

while(num){

result++;

num/=10;

}

return result;

}
