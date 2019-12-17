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

int playerOneFireFirst = 0;  // how strong the first fire for 1st player
int playerTwoFireFirst = 0;  // how strong the first fire for 2nd player

int playerOneFireSecond = 0;  // how strong the second fire for 1st player
int playerTwoFireSecond = 0;  // how strong the second fire for 2nd player

int playerOneFirePosition = 1;  // where is the player1
int playerTwoFirePosition = 142;  // where is the player2

int fireCase1 = 0;
int fireCase2 = 0;

boolean defenceOne = false;
boolean defenceTwo = false;


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

int j = 60;

int i = 0;
int k = 142;

Player player1(0, 0, 0); // first car
Player player2(140, 0, 0); // first car

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

    player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireFirst, fireCase2);
    player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireFirst, fireCase1);
    if (playerOneFireFirst > 199 ) {
      player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireSecond, fireCase1);
    }
    if (playerTwoFireFirst > 199 ) {
      player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireSecond, fireCase2);
    }
    /*
      int i = 0;
      int k = 142;

    */
    if (i > 130) {
      defenceTwo = player2.defenceTest(sensorWertC, sensorWertD);
    }
    if (k < 9) {
      defenceOne = player1.defenceTest(sensorWertA, sensorWertB);
    }

  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();



    led[143].setRGB(102, 0, 102);
    led[0].setRGB(102, 0, 102);
    // start
    if (fireCase1 == 0 && fireCase2 == 0) {
      led[playerOneFirePosition].setRGB( playerOneFireFirst, 0, 0);
      led[playerTwoFirePosition].setRGB( playerTwoFireFirst, 0, 0);
      led[playerTwoFirePosition - 1].setRGB( playerTwoFireSecond, 0, 0);
      led[playerOneFirePosition + 1].setRGB( playerOneFireSecond, 0, 0);
      // 1 start   ___ 2 not yet
    } else if (fireCase1 != 0 && fireCase2 == 0) {
      led[playerTwoFirePosition].setRGB( playerTwoFireFirst, 0, 0);
      led[playerTwoFirePosition - 1].setRGB( playerTwoFireSecond, 0, 0);
      if (bright.hasPassed(1)) {
        bright.restart();
        led[i].setRGB( playerOneFireSecond, 0, 0);
        led[i + 1].setRGB( playerOneFireSecond, 0, 0);
        FastLED.show();
        if (i <= 140) {
          i++;
        }
      }
      if (i == 141 && defenceTwo == false) {
        led[i].setRGB( playerOneFireSecond, 0, 0);
        led[i + 1].setRGB( playerOneFireSecond, 0, 0);
      } else if (defenceTwo == true) {
        playerOneFireSecond = 0;
        playerOneFireFirst = 0;
        fireCase1 = 0;
        i = 0;
        defenceTwo = false;
      }
      if (k == i) {
        led[k].setRGB( 0, 0, 220);
        FastLED.show();
        delay(100);
        playerTwoFireSecond = 0;
        playerOneFireSecond = 0;
        playerOneFireFirst = 0;
        playerTwoFireFirst = 0;
        fireCase2 = 0;
        fireCase1 = 0;
        k = 142;
        i = 0;

      }
      // 2 start   ___ 1 not yet
    }  else if (fireCase2 != 0 && fireCase1 == 0) {
      led[playerOneFirePosition].setRGB( playerOneFireFirst, 0, 0);
      led[playerOneFirePosition + 1].setRGB( playerOneFireSecond, 0, 0);
      if (bright.hasPassed(1)) {
        bright.restart();
        led[k].setRGB( playerTwoFireSecond, 0, 0);
        led[k - 1].setRGB( playerTwoFireSecond, 0, 0);
        FastLED.show();
        if (k > 2) {
          k--;
        }
      }
      if (k == 2 && defenceOne == false) {
        led[k].setRGB( playerTwoFireSecond, 0, 0);
        led[k - 1].setRGB( playerTwoFireSecond, 0, 0);
      }else if (defenceOne == true) {
        playerTwoFireSecond = 0;
        playerTwoFireFirst = 0;
        fireCase2 = 0;
        k = 142;
        defenceOne = false;
      }
      if (k == i) {
        led[k].setRGB( 0, 0, 220);
        FastLED.show();
        delay(100);
        playerTwoFireSecond = 0;
        playerOneFireSecond = 0;
        playerOneFireFirst = 0;
        playerTwoFireFirst = 0;
        fireCase2 = 0;
        fireCase1 = 0;
        k = 142;
        i = 0;

      }

    }
    // both start already
    else if (fireCase2 != 0 && fireCase1 != 0) {
      if (bright.hasPassed(1)) {
        bright.restart();
        led[k].setRGB( playerTwoFireSecond, 0, 0);
        led[k - 1].setRGB( playerTwoFireSecond, 0, 0);
        led[i].setRGB( playerOneFireSecond, 0, 0);
        led[i + 1].setRGB( playerOneFireSecond, 0, 0);
        FastLED.show();
        if (k >= 3) {
          k--;
        }
        if (i <= 140) {
          i++;
        }
      }
      if (k == i) {
        led[k].setRGB( 0, 0, 220);
        FastLED.show();
        delay(100);
        playerTwoFireSecond = 0;
        playerOneFireSecond = 0;
        playerOneFireFirst = 0;
        playerTwoFireFirst = 0;
        fireCase2 = 0;
        fireCase1 = 0;
        k = 142;
        i = 0;

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
