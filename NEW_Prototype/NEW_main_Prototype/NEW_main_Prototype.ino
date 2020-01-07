#include <FastLED.h>
#include <Chrono.h>
#include "player.h"

#define NUM_LEDS 144 // all leds
#define LED_PIN 14   // place the led

const int ledLength = 8;     // later long of car
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
int MAX_BRIGHTNESS =  60;
const int fps = 100;

#define ctsPin 19  // place the sensor


float speedC = 0;
float gravity = 0.09;


//VARIABLEN ERZEUGEN
int sensorPinA = 15;    //hier ist die nummer des analogen pins gespeichert an dem unser sensor angeschlossen ist, ggf. anpassen! (z.b. 16, 17, 20, oder 21)
int sensorPinB = 16;
int sensorPinC = 17;
int sensorPinD = 18;
int sensorWertA = 0;    //in dieser variable wird unser sensorwert, d.h. der Rückgabewert der Funktion analogRead(); oder touchRead(); gespeichert.
int sensorWertB = 0;
int sensorWertC = 0;
int sensorWertD = 0;
int sensorValueTest = 0;

//create chrono objects for timed actions:
Chrono cNextFrame(Chrono::MICROS);
Chrono cCheckInput;


CRGB led [NUM_LEDS];

int OnePlayerPosition = 6;

float OneFireFirstPosition = 7;
float OneFireSecondPosition = 8;

float OnePlayerFireFirst = 0.0;
float OnePlayerFireSecond = 0.0;

int OneEnergyPlayer = 5;

bool OnefireCase = false;


Player player1(OnePlayerPosition, OneFireFirstPosition, OneFireSecondPosition, OnePlayerFireFirst, OnePlayerFireSecond, OneEnergyPlayer, OnefireCase);




void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(led, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip); //LEDS.setCorrection(Candle); or (Tungsten40W)

  Serial.begin(115200); //serielle datenverbindung zum computer herstellen damit wir mit Serial.print(); oder Serial.println(); daten senden können
  //pinMode(sensorValue, OUTPUT);
  //pinMode(ctsPin, INPUT);

  pinMode(sensorPinA, INPUT_PULLUP);  //declare pin as input AND enable internal 33kohm pullup resistor (that is: a 33k resistor between the analog input pin and 3.3 volts)
  pinMode(sensorPinB, INPUT_PULLUP);
  pinMode(sensorPinC, INPUT_PULLUP);
  pinMode(sensorPinD, INPUT_PULLUP);
}

void loop()
{
  Chrono bright;
  Chrono defence2;
  Chrono defence1;

  sensorWertA = filter(analogRead(sensorPinA), 0.25, sensorWertA);
  sensorWertB = filter(analogRead(sensorPinB), 0.25, sensorWertB);
  sensorWertC = filter(analogRead(sensorPinC), 0.25, sensorWertC);
  sensorWertD = filter(analogRead(sensorPinD), 0.25, sensorWertD);
  sensorWertA = map(sensorWertA, 0, 1023, 0, 100);
  sensorWertB = map(sensorWertB, 0, 1023, 0, 100);
  sensorWertC = map(sensorWertC, 0, 1023, 0, 100);
  sensorWertD = map(sensorWertD, 0, 1023, 0, 100);
  Serial.println(sensorWertA);               //send debug data to the Arduino Serial Monitor


  //INTERACTIVITY: work with sensor data every X ms
  if (cCheckInput.hasPassed(1)) {
    cCheckInput.restart();

    player1.playShow(sensorWertA, sensorWertB);


  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps)  ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();

    int i = (int) player1.fireFirstPositionC;



    led[i].setRGB(player1.playerFireFirstC, 0, 0);
    led[i + 1].setRGB(player1.playerFireSecondC, 0, 0);
    //  led[0].setRGB(102, 0, 0);

    switch (player1.energyPlayerC) {
      case 5:
          led[0].setRGB( 50, 0, 0);
                    led[1].setRGB( 50, 22, 0);
                              led[2].setRGB( 50, 50, 0);
                                        led[3].setRGB( 22 , 50, 0);
                                                  led[4].setRGB( 0, 50, 0);

        break;
      case 4:
                    led[i].setRGB( 220, 0, 0);
                              led[i].setRGB( 220, 0, 0);
                                        led[i].setRGB( 220, 0, 0);
                                                  led[i].setRGB( 220, 0, 0);
        break;
      case 3:
                              led[i].setRGB( 220, 0, 0);
                                        led[i].setRGB( 220, 0, 0);
                                                  led[i].setRGB( 220, 0, 0);
        break;
      case 2:
                              led[i].setRGB( 220, 0, 0);
                                        led[i].setRGB( 220, 0, 0);
        break;
      case 1:
                                        led[i].setRGB( 220, 0, 0);
        break;
    }
    if (player1.effect3 == true) {
      player1.fireFirstPositionC = player1.fireFirstPositionC + speedC;
      speedC = speedC + gravity;
      if ( player1.fireFirstPositionC > 140) {
        for (int i = 0; i < NUM_LEDS; i++) {
          led[i].setRGB( 220, 0, 0);
          FastLED.show();
          delay(10);
        }
        player1.resetPlayer();
      }
    }




    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
