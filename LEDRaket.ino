
// LEDRaketen, Av Anton Dalsmo och Henrik Horlin

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      9



// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int raket_possiotion;


int delayval = 500; // delay for half a second


int myColors[][3] = {{100,50,50}, 
                      {50,25,25}, 
                      {30,15,25}, 
                      {10,10,10},
                      {0,5,5}};

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  raket_possiotion = 0;
}

void loop() {
  int temp;
  for(int i=0; i<5;i++){ // lys upp raketen
    temp = raket_possiotion-i;
    if(temp>=0 && temp<NUMPIXELS){ // kollar att temp ar en lysdiod
      pixels.setPixelColor(temp, pixels.Color(myColors[i][0],myColors[i][1],myColors[i][2]));
    } 
  }
  temp--;
  if(temp>=0 && temp<NUMPIXELS){ // kollar att temp ar en lysdiod, en lysdiod efter raketen
      pixels.setPixelColor(temp,pixels.Color(0,0,0)); // slck sista lysdioden
  } 
  pixels.show();
  delay(delayval);
  if (raket_possiotion<20){
    raket_possiotion++;
  }
}
