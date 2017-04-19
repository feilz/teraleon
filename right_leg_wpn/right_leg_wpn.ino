#include <Servo.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x11
#define yaPIN 4
#define yatop 0
#define yabot 90
#define yaspd 10

#define aaPIN 5
#define aatop 0 
#define aabot 90
#define aaspd 10

#define dur 5000

Servo ase;

int command=0, val=0;
boolean inits=true,aseetAlhaal=false;
uint32_t timer=0;

void init10(){
  moveServo(ase,yaPIN,yatop,yabot,yaspd);
  moveServo(ase,aaPIN,aatop,aabot,aaspd);
  aseetAlhaal=true;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDRESS);
  TWBR=152;
  Wire.onReceive(recv);
  initloop();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(command){
    case 1:
      aseet();
      break;
    case 2:
      if (aseetAlhaal) aseet();
      break;
    case 6:
      if (!aseetAlhaal) aseet();
      break;
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
  if (!aseetAlhaal) aseet();
  while(inits){
    if (timer==dur){
      aseet();
      timer=0;  
    }
    timer+=1;
    delay(1);
  }
}

void initloop(){
  while (inits){
    aseet1();
  }
}

void aseet(){
  if (aseetAlhaal){
    moveServo(ase,yaPIN,yabot,yatop,yaspd);
    moveServo(ase,aaPIN,aabot,aatop,aaspd);
    aseetAlhaal=false;
  } else {
    moveServo(ase,yaPIN,yatop,yabot,yaspd);
    moveServo(ase,aaPIN,aatop,aabot,aaspd);
    aseetAlhaal=true;
  }
  command=0;
}


void aseet1(){
  if (aseetAlhaal){
    moveServo(ase,yaPIN,yabot,yatop,yaspd);
    if (!inits) return;
    moveServo(ase,aaPIN,aabot,aatop,aaspd);
    aseetAlhaal=false;
  } else {
    moveServo(ase,yaPIN,yatop,yabot,yaspd);
    if (!inits) return;
    moveServo(ase,aaPIN,aatop,aabot,aaspd);
    aseetAlhaal=true;
  }
}

void moveServo(Servo &a, uint8_t pin, int alku, int loppu, int nopeus){
  a.attach(pin);
  if (alku==200) alku=a.read();
  if (alku<loppu){
    for (int i=alku;i<loppu;i+=1){
      a.write(i);
      delay(nopeus);
    }
  }else {
    for (int i=alku;i>loppu;i-=1){
      a.write(i);
      delay(nopeus);
    }
  }
  a.detach(); 
}
void recv(uint8_t howmany){
  val=Wire.read();
  if (inits){
    init10();
    inits=false;
  }
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
