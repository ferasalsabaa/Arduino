#include <FastLED.h>
#include <Chrono.h>
#include "Car_class.h"

#define NUM_LEDS 144 // all leds
#define LED_PIN 14   // place the led

const int ledLength = 8;     // later long of car
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS  120
const int fps = 100;

int now=0;    // where is the car

#define ctsPin 19  // place the sensor
int sensorValue  = 0;  // touch value

//create chrono objects for timed actions:
Chrono cNextFrame(Chrono::MICROS);
Chrono cCheckInput;


CRGB led [NUM_LEDS];

Car_class car1; // first car

void setup() {

  FastLED.addLeds<NEOPIXEL,LED_PIN>(led, NUM_LEDS);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(led, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip); //LEDS.setCorrection(Candle); or (Tungsten40W)
  FastLED.setBrightness(MAX_BRIGHTNESS);

      Serial.begin(9600);
       pinMode(sensorValue, OUTPUT);
       pinMode(ctsPin, INPUT);
} 

void loop()
    {
   sensorValue = touchRead(ctsPin);
  Serial.println(sensorValue);               //send debug data to the Arduino Serial Monitor

  
  //INTERACTIVITY: work with sensor data every X ms
  if (cCheckInput.hasPassed(1)){
    cCheckInput.restart();
    car1.testMethod(sensorValue, now, led, NUM_LEDS);
 /*   if (sensorValue > 900)   //modify this threshold and relaunchVel to adjust sensitivity
    {
      led[now].setRGB(220,62,220);
      FastLED.show();
      now = now + 1 ;
      if(now == 144){
        now = 0;
     for(int i=0;i<NUM_LEDS;i++){
        fill_rainbow(led, i, 0, 5);
        FastLED.show();
        delay(10);
  }
FastLED.clear();
        }
    }*/ 
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...
  
    cNextFrame.restart();
    FastLED.clear();

led[now].setRGB(220,62,220);

    FastLED.show();
  }
  
      } // end loop
