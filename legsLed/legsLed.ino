// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      120

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  pixels.begin();
  for(int i=0;i<120;i++){
    pixels.setPixelColor(i, 0,0,0);
  }
  pixels.show();
  
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
  strip.setBrightness(255);
  pixels.setBrightness(255);
}

void loop() {
  for(int i=0;i<150;i++){
    pixels.setBrightness(i);
    for(int k=99;k<120;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }

  for(int i=150;i>0;i--){
    pixels.setBrightness(i);
    for(int k=99;k<120;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }
  
  for(int i=0;i<150;i++){
    pixels.setBrightness(i);
    for(int k=67;k<82;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }
  
  for(int i=150;i>0;i--){
    pixels.setBrightness(i);
    for(int k=67;k<82;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }
  
  
  for(int i=0;i<150;i++){
    pixels.setBrightness(i);
    for(int k=23;k<60;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }

  for(int i=150;i>0;i--){
    pixels.setBrightness(i);
    for(int k=23;k<60;k++){
      pixels.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      pixels.show();
  }
  
  
  for(int i=0;i<150;i++){
    strip.setBrightness(i);
    for(int k=27;k<60;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }

  for(int i=150;i>0;i--){
    strip.setBrightness(i);
    for(int k=27;k<60;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }
  
  
  for(int i=0;i<150;i++){
    strip.setBrightness(i);
    for(int k=69;k<74;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }

  for(int i=150;i>0;i--){
    strip.setBrightness(i);
    for(int k=69;k<74;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }
  
  
  for(int i=0;i<150;i++){
    strip.setBrightness(i);
    for(int k=92;k<97;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }

  for(int i=150;i>0;i--){
    strip.setBrightness(i);
    for(int k=92;k<97;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }
  
  
  for(int i=0;i<150;i++){
    strip.setBrightness(i);
    for(int k=113;k<120;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }

  for(int i=150;i>0;i--){
    strip.setBrightness(i);
    for(int k=113;k<120;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }
  
  
  for(int i=0;i<150;i++){
    strip.setBrightness(i);
    for(int k=126;k<138;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }

  for(int i=150;i>0;i--){
    strip.setBrightness(i);
    for(int k=126;k<138;k++){
      strip.setPixelColor(k, 150,0,0);
    }
    //delay(5);
      strip.show();
  }
  
  
  delay(200);
  for(int i=0;i<120;i++){
    pixels.setPixelColor(i, 0,0,0);
  }
  pixels.show();
  
  for(int i=0;i<144;i++){
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
}
