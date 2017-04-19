#include <Wire.h>
#include <Servo.h>
#define SLAVE_ADDRESS 0x05
#define klPIN 7
#define epPIN 8
#define isopPIN 5
#define l1PIN 3
#define l2PIN 4
#define l3PIN 9
#define l1top 112
#define l1bot 155
#define l2top 107
#define l2bot 157
#define l3top 80
#define l3bot 125
#define isoptop 40
#define isopbot 140
#define kltop 135
#define klbot 70
#define eptop 65
#define epbot 175
#define dur 5000

Servo kl,ep, l1,l2,l3,isop;
boolean pyssytAlhaal=false, inits=true;
int val,command;
uint32_t timer;


void init10(){
  kl.attach(klPIN);
  kl.write(klbot);
  kl.detach();
  ep.attach(epPIN);
  ep.write(epbot);
  ep.detach();
  l1.attach(l1PIN);
  l1.write(l1bot);
  l1.detach();
  l2.attach(l2PIN);
  l2.write(l2bot);
  l2.detach();
  l3.attach(l3PIN);
  l3.write(l3bot);
  l3.detach();
  isop.attach(isopPIN);
  isop.write(isopbot);
  isop.detach();
  pyssytAlhaal=true;
}
void detachAll(){
  kl.detach();
  ep.detach();
  l1.detach();
  l2.detach();
  l3.detach();
  isop.detach();
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDRESS);
  TWBR = 152;
  Wire.onReceive(recv);
  initloop();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(command){
    case 1:
      pyssyt();
      break;
    case 2:
      if (pyssytAlhaal) pyssyt();
      break;
    case 6:
      if (!pyssytAlhaal) pyssyt();
    case 7:
      epicLoop();
      break;
    default: 
      break;
  }
}
void epicLoop(){
  inits=true;
  timer=0;
  if (!pyssytAlhaal) pyssyt();
  while(inits){
    if (timer==dur){
      pyssyt();
      timer=0;  
    }
    timer+=1;
    delay(1);
  }
}

void initloop(){
  while (inits){
    pyssyt1();
  }
}


void pyssyt(){
  if (pyssytAlhaal){
    moveServo(kl,klbot,kltop,40,klPIN);
    moveServo(ep,epbot,eptop,20,epPIN);
    moveServo(isop,isopbot,isoptop,25,isopPIN);
    moveServo(l1,l1bot,l1top,2,l1PIN);
    moveServo(l2,l2bot,l2top,2,l2PIN);
    moveServo(l3,l3bot,l3top,2,l3PIN);
    pyssytAlhaal=false;
  }else{
    moveServo(l1,l1top,l1bot,2,l1PIN);
    moveServo(l2,l2top,l2bot,2,l2PIN);
    moveServo(l3,l3top,l3bot,2,l3PIN);
    moveServo(kl,kltop,klbot,40,klPIN);
    moveServo(ep,eptop,epbot,20,epPIN);
    moveServo(isop,isoptop,isopbot,25,isopPIN);
    pyssytAlhaal=true;   
  }
  command=0;
}
void pyssyt1(){
  if (pyssytAlhaal){
    moveServo(kl,klbot,kltop,40,klPIN);
    if (!inits) return;
    moveServo(ep,epbot,eptop,20,epPIN);
    if (!inits) return;
    moveServo(isop,isopbot,isoptop,25,isopPIN);
    if (!inits) return;
    moveServo(l1,l1bot,l1top,2,l1PIN);
    moveServo(l2,l2bot,l2top,2,l2PIN);
    moveServo(l3,l3bot,l3top,2,l3PIN);
    pyssytAlhaal=false;
  }else{
    moveServo(l1,l1top,l1bot,2,l1PIN);
    moveServo(l2,l2top,l2bot,2,l2PIN);
    moveServo(l3,l3top,l3bot,2,l3PIN);
    if (!inits) return;
    moveServo(isop,isoptop,isopbot,25,isopPIN);
    if (!inits) return;
    moveServo(kl,kltop,klbot,40,klPIN);
    if (!inits) return;
    moveServo(ep,eptop,epbot,20,epPIN);
    pyssytAlhaal=true;   
  }
}

void moveServo(Servo &a, int alku, int loppu, int nopeus, uint8_t pin){
  a.attach(pin);
  if (alku<loppu){
    for (int i=alku;i<loppu;i+=2){
      a.write(i);
      delay(nopeus);
    }
  }else {
    for (int i=alku;i>loppu;i-=2){
      a.write(i);
      delay(nopeus);
    }
  }
  a.detach(); 
}
/*
void moveServo(sInfo &a){
  a.servo.attach(a.pin);
  if (pyssytAlhaal){
    if (a.bot<a.top){
      for (int i=a.bot;i<a.top;i+=2){
        a.servo.write(i);
        delay(a.spd);
      }
    }else{
      for (int i=a.bot;i>a.top;i-=2){
        a.servo.write(i);
        delay(a.spd);
      }
    }
  }else {
    if (a.top<a.bot){
      for (int i=a.top;i<a.bot;i+=2){
        a.servo.write(i);
        delay(a.spd);
      }
    }else{
      for (int i=a.top;i>a.bot;i-=2){
        a.servo.write(i);
        delay(a.spd);
      }
    }
  }
  a.servo.detach(); 
}
*/
void recv(uint8_t howmany){
  val=Wire.read();
  if (inits){
    init10();
    inits=false;
  }else{
    switch(val){
      case 1:
        command=1;
        break;
      case 2:   
        command=2;
        break;
      case 6:
        command=6;
        break;
      case 7:
        command=7;
        break;
      default:
        break;  
    }
  }
}

