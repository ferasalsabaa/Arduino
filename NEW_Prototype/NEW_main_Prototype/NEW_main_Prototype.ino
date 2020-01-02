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

float playerOneFireFirst = 0;  // how strong the first fire for 1st player
float playerTwoFireFirst = 0;  // how strong the first fire for 2nd player

float playerOneFireSecond = 0;  // how strong the second fire for 1st player
float playerTwoFireSecond = 0;  // how strong the second fire for 2nd player

int playerOneFirePosition = 1;  // where is the player1
int playerTwoFirePosition = 142;  // where is the player2

int fireCase1 = 0;
int fireCase2 = 0;

int defenceCountOne = 0;
int defenceCountTwo = 0;

boolean defenceOne = false;
boolean defenceTwo = false;

boolean defenceOneShow = false;
boolean defenceTwoShow = false;




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

// float i = 1;
// float k = 142;

int i = 1;
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

    player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireFirst, fireCase2);
    player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireFirst, fireCase1);
    if (playerOneFireFirst > 199 && fireCase1 == 0) {
      player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireSecond, fireCase1);
    }
    if (playerTwoFireFirst > 199 && fireCase2 == 0) {
      player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireSecond, fireCase2);
    }
 //   player1.playShowFireFirst((sensorWertC, sensorWertD, i);

    if (i > 130) {
      defenceTwo = player2.defenceTest(sensorWertC, sensorWertD);
    }
    if (k < 9) {
      defenceOne = player1.defenceTest(sensorWertA, sensorWertB);
    }
    if (sensorWertA > 7 && sensorWertB < 7) {
      defenceOneShow = true;
    }
    if (sensorWertB > 7 && sensorWertD < 7) {
      defenceTwoShow = true;
    }
  }
  //DRAW FRAME
  //if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...
  if (cNextFrame.hasPassed((1000 * 1000) / fps)  ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();


//int ii = (int) i;

    led[playerOneFirePosition].setRGB( playerOneFireFirst, 0, 0);
    led[playerTwoFirePosition].setRGB( 0 , 0, playerTwoFireFirst);
    led[playerTwoFirePosition - 1].setRGB( 0, 0, playerTwoFireSecond);
    led[playerOneFirePosition + 1].setRGB( playerOneFireSecond, 0, 0);

    led[i].setRGB( playerOneFireFirst, 0, 0);
    led[i + 1].setRGB( playerOneFireSecond, 0, 0);
    led[k].setRGB( 0, 0, playerTwoFireFirst);
    led[k - 1].setRGB( 0, 0, playerTwoFireSecond);
    
    led[143].setRGB(0, 0, 102);
    led[0].setRGB(102, 0, 0);


    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}