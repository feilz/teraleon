#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#define rintaPIXLS 120
#define rintaPIN 5
#define absPIXLS 60 
#define absPIN 9
#define pottaPIXLS 55
#define pottaPIN 2
#define OAVPIN 4

#define OARPIN 3
#define olkaAseVP 19
#define olkaAseRP 16

#define SLAVE_ADDRESS 0x12

int rintaLeds[] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,
                    47,48,49,50,51,52,53,
                    55,56,57,58,59,60,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,
                    107,108,109,110,111,112,
                    114,115,116,117,118,119};
int vatsaLeds[] = {6,7,8,9,10,11,
                   20,21,22,23,24,
                   42,43,44,45,46,
                   54,55,56,57,58};  
int val, toggled,command=0,helpCommand=0;
Adafruit_NeoPixel rinta = Adafruit_NeoPixel(rintaPIXLS, rintaPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel vatsa = Adafruit_NeoPixel(absPIXLS, absPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel potta = Adafruit_NeoPixel(pottaPIXLS, pottaPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel olkaAseV = Adafruit_NeoPixel(olkaAseVP, OAVPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel olkaAseR = Adafruit_NeoPixel(olkaAseRP, OARPIN, NEO_GRB + NEO_KHZ800);

uint32_t red = vatsa.Color(240,0,0);
uint32_t green = vatsa.Color(0,240,0);
uint32_t blue = vatsa.Color(0,0,240);
uint32_t black = vatsa.Color(0,0,0);
boolean inits=true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(recv);
  rinta.begin();
  vatsa.begin();
  potta.begin();
  vatsa.setBrightness(120);
  rinta.setBrightness(120);
  potta.setBrightness(120);
  initLoop();
}
void loop() {
  switch(command){
    case 1: 
      fire(red);
      break;
    case 2:
      colorToggle();
      break;
    case 3:
      if(toggled){
        strobo(potta.Color(150,0,0));
        delay(200);
        strobo(potta.Color(150,0,0));
        lightUp(potta.Color(150,0,0));
        toggled=false;
      }
      redBreathe();
      break;
    case 4:
      if(toggled){
        strobo(potta.Color(0,0,150));
        delay(200);
        strobo(potta.Color(0,0,150));
        lightUp(potta.Color(0,0,150));
        toggled=false;
      }
      blueBreathe();
      break;
    case 5:
      if(toggled){
        strobo(potta.Color(0,150,0));
        delay(200);
        strobo(potta.Color(0,150,0));
        lightUp(potta.Color(0,150,0));
        toggled=false;
      }
      greenBreathe();
      break;
    case 6:
      allBlack();
      break;
    case 7:
      fire(red);
      break;
    default:
      break;
  }
}
void colorToggle(){
  helpCommand+=1;
  switch (helpCommand){
    case 1:
      command=4;
      break;
    case 2:
      command=5;
    case 3:
      command=3;
      helpCommand=0;
    default:
      break;
  }
}
void initLoop(){
  while (inits){
    blueBreathe();
  }
}

void redBreathe(){
  int intensity;
  for (int i=0;i<800;i++){
    intensity = (250.0/2.0)*(1.0+sin(0.02*i));
    for (int i=0;i<sizeof(rintaLeds)/2;i++){
      rinta.setPixelColor(rintaLeds[i],intensity,0,0);
      if (i<sizeof(vatsaLeds)/2) vatsa.setPixelColor(vatsaLeds[i],intensity,0,0);
    }
    for(int i=0;i<8;i++){
        potta.setPixelColor(i, intensity,0,0);
      }
      for(int i=13;i<21;i++){
        potta.setPixelColor(i, intensity,0,0);
      }
      for(int i=26;i<35;i++){
        potta.setPixelColor(i, intensity,0,0);
      }
      for(int i=40;i<49;i++){
        potta.setPixelColor(i, intensity,0,0);
      }
    rinta.show();
    vatsa.show();
    potta.show();
    if (toggled) return;
    delay(1);
  }
}

void greenBreathe(){
  int intensity;
  for (int i=0;i<800;i++){
    intensity = (250.0/2.0)*(1.0+sin(0.02*i));
    for (int i=0;i<sizeof(rintaLeds)/2;i++){
      rinta.setPixelColor(rintaLeds[i],0,intensity,0);
      if (i<sizeof(vatsaLeds)/2) vatsa.setPixelColor(vatsaLeds[i],0,intensity,0);
    }
    for(int i=0;i<8;i++){
        potta.setPixelColor(i, 0,intensity,0);
      }
      for(int i=13;i<21;i++){
        potta.setPixelColor(i, 0,intensity,0);
      }
      for(int i=26;i<35;i++){
        potta.setPixelColor(i, 0,intensity,0);
      }
      for(int i=40;i<49;i++){
        potta.setPixelColor(i, 0,intensity,0);
      }
    rinta.show();
    vatsa.show();
    potta.show();
    if (toggled) return;
    delay(1);
  }  
}
void blueBreathe(){
  int intensity;
  for (int i=0;i<800;i++){
    intensity = (250.0/2.0)*(1.0+sin(0.02*i));
    for (int i=0;i<sizeof(rintaLeds)/2;i++){
      rinta.setPixelColor(rintaLeds[i],0,0,intensity);
      if (i<sizeof(vatsaLeds)/2) vatsa.setPixelColor(vatsaLeds[i],0,0,intensity);
    }
    for(int i=0;i<8;i++){
        potta.setPixelColor(i, 0,0,intensity);
      }
      for(int i=13;i<21;i++){
        potta.setPixelColor(i, 0,0,intensity);
      }
      for(int i=26;i<35;i++){
        potta.setPixelColor(i, 0,0,intensity);
      }
      for(int i=40;i<49;i++){
        potta.setPixelColor(i, 0,0,intensity);
      }
    rinta.show();
    vatsa.show();
    potta.show();
    if (toggled) return;
    delay(1);
  }
}

void test(){
  int intensity;
  for (int i=0;i<800;i++){
    intensity = (250.0/2.0)*(1.0+sin(0.02*i));
    for (int i=0;i<sizeof(rintaLeds)/2;i++){
      rinta.setPixelColor(rintaLeds[i],intensity,0,0);
      if (i<sizeof(vatsaLeds)/2) vatsa.setPixelColor(vatsaLeds[i],intensity,0,0);
    }
    rinta.show();
    vatsa.show();
    delay(1);
  }
 }

void allBlack(){
  for (int i=0;i<sizeof(rintaLeds)/2;i++){
    rinta.setPixelColor(rintaLeds[i],black);
    if (i<sizeof(vatsaLeds)/2) vatsa.setPixelColor(vatsaLeds[i],black);
  }
  rinta.show();
  vatsa.show();
}
void recv(int howMany){
  toggled=true;
  val=Wire.read();
  if (inits) inits=false;
  else {
    command=val;
    /*switch(val){
      case 1:
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
      case 5:
        command=5;
        break;
      case 6:
        command=6;
        break;
      case 7:
        command=7;
        break;
    }*/
  }
}

void lightOn(Adafruit_NeoPixel &strip,int led,uint32_t color){
  strip.setPixelColor(led,color);
  strip.show();
}

void strobo(uint32_t c) {
  for(int k=0;k<3;k++){
  for(int i=0;i<8;i++){
    potta.setPixelColor(i, c);
  }
  for(int i=13;i<21;i++){
    potta.setPixelColor(i, c);
  }
  for(int i=26;i<35;i++){
    potta.setPixelColor(i, c);
  }
  for(int i=40;i<49;i++){
    potta.setPixelColor(i, c);
  }
    potta.show();
  
  delay(50);
  
  for(int i=0;i<50;i++){
    potta.setPixelColor(i, 0,0,0);
  }
    potta.show();
    delay(50);
  }
}

int aseO[] = {0,1,2,3,4,5,10,11,12,13,14,15};
int aseV[] = {0,1,2,3,4,5,13,14,15,16,17,18};

void fire(uint32_t color){
  for (int i=0;i<19;i++){
    olkaAseV.setPixelColor(i,black);
    olkaAseR.setPixelColor(i,black);
  }
  olkaAseV.show();
  olkaAseR.show();
  for (int i=0;i<6;i++){
    lightOn(olkaAseV,aseV[i],color);
    lightOn(olkaAseR,aseO[i],color);
    lightOn(olkaAseV,aseV[i-1],black);
    lightOn(olkaAseR,aseO[i-1],black);
    delay(150);
  }
  for (int i=-1;i>-7;i--){
    lightOn(olkaAseV,aseV[i],color);
    lightOn(olkaAseR,aseO[i],color);
    lightOn(olkaAseV,aseV[i+1],black);
    lightOn(olkaAseR,aseO[i+1],black);
    delay(150);
  }
}



void lightUp(uint32_t c) {
  for(int i=0;i<130;i++){
    potta.setBrightness(i);
    for(int i=0;i<8;i++){
        potta.setPixelColor(i, c);
      }
        potta.show();
      for(int i=13;i<21;i++){
        potta.setPixelColor(i, c);
      }
        potta.show();
      for(int i=26;i<35;i++){
        potta.setPixelColor(i, c);
      }
        potta.show();
      for(int i=40;i<49;i++){
        potta.setPixelColor(i, c);
      }
    potta.show();
    delay(30);
  }
}
