#include <Servo.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x13
#define palkPIN1 5 
#define palkPIN2 9
#define salPIN1 3
#define salPIN2 7
#define sydPIN1 2
#define sydPIN2 6
#define paaPIN1 4
#define paaPIN2 10
#define suuPIN1 11
#define suuPIN2 12

#define syd1top 175 
#define syd1bot 5
#define syd2top 5
#define syd2bot 175
#define sydnop 5

#define sal1top 115
#define sal1bot 35
#define sal2top 70
#define sal2bot 152
#define salnop 20

#define palk1top 180
#define palk1bot 40
#define palk2top 180
#define palk2bot 40
#define palknop 20

#define paa1top 60
#define paa1bot 90
#define paa2top 45
#define paa2bot 140
#define paanop 30
 
#define suu1top 72
#define suu1bot 125 
#define suu2top 77 
#define suu2bot 130
#define suunop 20

#define dur 5000

Servo s1, s2;
int val, command=0;
boolean allBot=false,inits=true;
uint32_t timer=0;
void init10(){
  move2servo(s1,paaPIN1,s2,paaPIN2,200,paa1bot,200,paa2bot,paanop);
  move2servo(s1,suuPIN1,s2,suuPIN2,200,suu1bot,200,suu2bot,suunop);
  move2servo(s1,sydPIN1,s2,sydPIN2,200,syd1bot,200,syd2bot,sydnop);
  move2servo(s1,salPIN1,s2,salPIN2,200,sal1bot,200,sal2bot,salnop);
  move2servo(s1,palkPIN1,s2,palkPIN2,200,palk1bot,200,palk2bot,palknop);
  allBot=true;
}
//move2servo &a, pin1, &b, pin2, alku1, loppu1, alku2, loppu2, nop)

//hartia -> sydan -> salama -> palkit 
void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDRESS);
  TWBR=152;
  Wire.onReceive(recv);
  initloop();
}

void loop() {
  switch (command){
    case 1:
      getAngry();
      break;
    case 2:
      if (allBot) getAngry();
      break;
    case 6:
      if (!allBot) getAngry();
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
  if (!allBot) getAngry();
  while(inits){
    if (timer==dur){
      getAngry();
      timer=0;  
    }
    timer+=1;
    delay(1);
  }
}

void initloop(){
  while(inits){
    getAngry1();
    delay(200);
  }
}
void getAngry(){
  if (allBot){
    move2servo(s1,paaPIN1,s2,paaPIN2,paa1bot,paa1top,paa2bot,paa2top,paanop);
    move2servo(s1,suuPIN1,s2,suuPIN2,suu1bot,suu1top,suu2bot,suu2top,suunop);
    move2servo(s1,sydPIN1,s2,sydPIN2,syd1bot,syd1top,syd2bot,syd2top,sydnop);
    move2servo(s1,salPIN1,s2,salPIN2,sal1bot,sal1top,sal2bot,sal2top,salnop);
    move2servo(s1,palkPIN1,s2,palkPIN2,palk1bot,palk1top,palk2bot,palk2top,palknop);
    allBot=false;
  }else{
    move2servo(s1,paaPIN1,s2,paaPIN2,paa1top,paa1bot,paa2top,paa2bot,paanop);
    move2servo(s1,suuPIN1,s2,suuPIN2,suu1top,suu1bot,suu2top,suu2bot,suunop);
    move2servo(s1,sydPIN1,s2,sydPIN2,syd1top,syd1bot,syd2top,syd2bot,sydnop);
    move2servo(s1,salPIN1,s2,salPIN2,sal1top,sal1bot,sal2top,sal2bot,salnop);
    move2servo(s1,palkPIN1,s2,palkPIN2,palk1top,palk1bot,palk2top,palk2bot,palknop);
    allBot=true;
  }
  command=0;
}
void getAngry1(){
  if (allBot){
    move2servo(s1,paaPIN1,s2,paaPIN2,paa1bot,paa1top,paa1bot,paa2top,paanop);
    if (!inits) return;
    move2servo(s1,suuPIN1,s2,suuPIN2,suu1bot,suu1top,suu1bot,suu2top,suunop);
    if (!inits) return;
    move2servo(s1,sydPIN1,s2,sydPIN2,syd1bot,syd1top,syd2bot,syd2top,sydnop);
    if (!inits) return;
    move2servo(s1,salPIN1,s2,salPIN2,sal1bot,sal1top,sal2bot,sal2top,salnop);
    if (!inits) return;
    move2servo(s1,palkPIN1,s2,palkPIN2,palk1bot,palk1top,palk2bot,palk2top,palknop);
    allBot=false;
  }else{
    move2servo(s1,paaPIN1,s2,paaPIN2,paa1top,paa1bot,paa2top,paa2bot,paanop);
    if (!inits) return;
    move2servo(s1,suuPIN1,s2,suuPIN2,suu2top,suu1bot,suu2top,suu2bot,suunop);
    if (!inits) return;
    move2servo(s1,sydPIN1,s2,sydPIN2,syd1top,syd1bot,syd2top,syd2bot,sydnop);
    if (!inits) return;
    move2servo(s1,salPIN1,s2,salPIN2,sal1top,sal1bot,sal2top,sal2bot,salnop);
    if (!inits) return;
    move2servo(s1,palkPIN1,s2,palkPIN2,palk1top,palk1bot,palk2top,palk2bot,palknop);
    allBot=true;
  }
}
void moveServo(Servo &a, uint8_t pin, int alku, int loppu, int nopeus){
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
void move2servo(Servo &a,uint8_t pin1,Servo &b,uint8_t pin2,int alku1,int loppu1,int alku2,int loppu2, int nop){
  a.attach(pin1);
  b.attach(pin2);
  if (alku1==200) alku1=a.read();
  if (alku2==200) alku2=b.read();
  if (alku1<loppu1){
    if (alku2<loppu2){
      for (int i=alku1,j=alku2;i<loppu1,j<loppu2;i+=2,j+=2){
        a.write(i);
        b.write(j);
        delay(nop);
    }
    }else {
      for (int i=alku1,j=alku2;i<loppu1,j>loppu2;i+=2,j-=2){
        a.write(i);
        b.write(j);
        delay(nop);
      }
    }
  }else {
    if (alku2<loppu2){
     for (int i=alku1,j=alku2;i>loppu1,j<loppu2;i-=2,j+=2){
        a.write(i);
        b.write(j);
        delay(nop);
      } 
    }else {
     for (int i=alku1,j=alku2;i>loppu1,j>loppu2;i-=2,j-=2){
        a.write(i);
        b.write(j);
        delay(nop);
      } 
    }
  }
}
void recv(){
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
    case 3:
      break;
    case 4:
      break;
    case 5:  
      break;
    case 6:
      command=6;
      break;
    case 7:
      command=7;
      break;
    case 8:
      break;
    case 9:
      break; 
  }
}
