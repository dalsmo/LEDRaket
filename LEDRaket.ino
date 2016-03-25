// LEDRaketen, Av Anton Dalsmo och Henrik Horlin

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8



// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int raket_possiotion;
bool raket_laddad = true;

int delayval = 200; // delay for half a second


//int myColors[][3] = {{100,50,50}, 
//                      {50,25,25}, 
//                      {30,15,25}, 
//                      {10,10,10},
//                      {0,5,5}};

//int myColors[][3] = {{0,200,50}, 
//                      {10,100,50}, 
//                      {25,50,10}, 
//                      {25,10,0},
//                      {25,5,0}};

int myColors[][3] = {{0,0,250}, 
                      {100,10,150}, 
                      {250,10,50}, 
                      {75,10,0},

                      {25,5,0}};
                      

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  
  Serial.begin(400000); 
  Serial.setTimeout(10);
}

void loop() {
  if(raket_laddad){
    for(int j=0;j<(8+5);j++){
      for(int i=0; i<8;i++){ // nollstall raketen
        pixels.setPixelColor(i, pixels.Color(0,0,0)); // (0,0,0) ingen farg
      }
      for(int i=0; i<5;i++){ // sett raketen
        //int temp = raket_possiotion-i;
        int temp = j-i;
        if(temp>=0 && temp<NUMPIXELS){ // kollar att temp ar en lysdiod
          pixels.setPixelColor(temp, pixels.Color(myColors[i][0],myColors[i][1],myColors[i][2]));
        }  
      }

      // lys lysdioder
      if(j==9){
        pixels.show();
        delay(delayval);
        pixels.updateLength(NUMPIXELS+1);
        pixels.setPixelColor(9, pixels.Color(0,0,0));
        pixels.show();
        pixels.updateLength(NUMPIXELS);
      }else{
        pixels.show(); // lys lysdioder
        delay(delayval);
      }
    }   
    raket_laddad = false;
  }

  // kolla om vi skall bli triggade
  if (Serial.available() >0){
    byte inData[12];
    Serial.readBytes(inData,12);
    Serial.flush();
    raket_laddad = true;
  }
}


