#include <Vnh2sp30.h>
#include <Wire.h>
//VARMISTA ETTEI KETJUT OLE PAIKOILLAAN KUN LAITAT PÄÄLLE!!!!
#define SLAVE_ADDRESS 0x14
#define POT_LEFT 195
#define POT_RIGHT 155

#define POT_PORT A3
#define basic_speed 500

//              ENA A   B   PWM   CS    inv
Vnh2sp30  oik( A0, 7,  8,  5,    A2,   0);             // Left side straight
Vnh2sp30  vas( A1, 4,  9,  6,    A3,   1);             // Right side reversed

int pot,val, command;
boolean inits=true,lrun=false, rrun=false;

void setup() { 
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(recv);
  //initloop();
  walk();
  }

void loop() { 
  checkPot();
  switch(command){
    case 1:
      walk();
      break;
    case 2:
      left(basic_speed);
      break;
    case 3:
      right(basic_speed);
      break;
    case 4:
      stopMov();
      break;
    default:
      break;
  }
}

//VARMISTA ETTEI KETJUT OLE PAIKOILLAAN KUN LAITAT PÄÄLLE!!!!
void initloop(){
  while (inits){
    val=analogRead(POT_PORT);
    Serial.println(val);
    delay(10);
    /*oik.run(1023);
    delay(2000);
    oik.stop();
    vas.run(-1023);
    delay(2000);
    vas.stop();*/
  }
}

void recv(int howMany){
  val = Wire.read();
  if (inits){
    inits=false;
  }
  else {
  switch (val){
    case 1:
      command=1;
        break;
    case 2:
      command=2;
      break;
    case 3:
      command=3;
      break;
    case 4:
      command=4;
      break;
    default:
      break;
    }
  }
}
void walk(){
  inits=true;
  while (inits){
    checkPot();
    left(-1023);
    right(1023);
  }
}

void left(int spd){
  if (lrun && !oik.state()) vas.run(spd);
}

void right(int spd){
  if (rrun && !vas.state()) oik.run(spd);
}

void stopMov(){
 vas.stop();                        // Stop both motors
 oik.stop();
}

void checkPot(){
  pot = analogRead(POT_PORT);
  Serial.println(pot);
  lrun=(pot>POT_RIGHT);
  rrun=(pot<POT_LEFT);
  if (!lrun||oik.state()) vas.stop();
  if (!rrun||vas.state()) oik.stop();
}
