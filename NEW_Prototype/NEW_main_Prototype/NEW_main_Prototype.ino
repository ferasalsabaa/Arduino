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


float speedPlayer1 = 0;
float speedPlayer2 = 0;
float gravity = 0.009;


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
// ---------------------------------player 1------------------------------------------
int OnePlayerPosition = 6;

float OneFireFirstPosition = 7;
float OneFireSecondPosition = 8;

float OnePlayerFireFirst = 0.0;
float OnePlayerFireSecond = 0.0;

int OneEnergyPlayer = 5;

bool OnefireCase = false;


Player player1(OnePlayerPosition, OneFireFirstPosition, OneFireSecondPosition, OnePlayerFireFirst, OnePlayerFireSecond, OneEnergyPlayer);

// ---------------------------------player 2------------------------------------------
int TwoPlayerPosition = 137;

float TwoFireFirstPosition = 136;
float TwoFireSecondPosition = 135;

float TwoPlayerFireFirst = 0.0;
float TwoPlayerFireSecond = 0.0;

int TwoEnergyPlayer = 5;


Player player2(TwoPlayerPosition, TwoFireFirstPosition, TwoFireSecondPosition, TwoPlayerFireFirst, TwoPlayerFireSecond, TwoEnergyPlayer);




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

    if (player1.effect3 == true) {
      player1.fireFirstPositionC = player1.fireFirstPositionC + player1.speedC;
      player1.speedC = player1.speedC + gravity;
      if ( player1.fireFirstPositionC > 140 && player2.playerFireSecondC<190) {
        player2.energyPlayerC = player2.energyPlayerC - 1;
        player1.resetPlayer();
      } else if(player1.fireFirstPositionC > 140 && player2.playerFireSecondC>190){
               
        player1.resetPlayer();
        player2.effect3 = true;
        }
    } else if (player2.effect3 == true) {
      player2.fireFirstPositionC = player2.fireFirstPositionC - player2.speedC;
      player2.speedC = player2.speedC + gravity;
      if ( player2.fireFirstPositionC < 4 && player1.playerFireSecondC<190) {
        player1.energyPlayerC = player1.energyPlayerC - 1;
        player2.resetPlayer();
      } else if( player2.fireFirstPositionC < 4 && player1.playerFireSecondC>190){
        player2.resetPlayer();
        player1.effect3 = true;
        }
    } else {
      player1.playShow(sensorWertA, sensorWertB);
      player2.playShow(sensorWertC, sensorWertD);
    }
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps)  ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();

    int onePos = (int) player1.fireFirstPositionC;
    int twoPos = (int) player2.fireFirstPositionC;


    led[onePos].setRGB(player1.playerFireFirstC, 0, 0);
    led[onePos + 1].setRGB(player1.playerFireSecondC, 0, 0);
    led[twoPos].setRGB(0, 0, player2.playerFireFirstC);
    led[twoPos - 1].setRGB(0, 0, player2.playerFireSecondC);

    switch (player1.energyPlayerC) {
      case 5:
        led[0].setRGB( 50, 0, 0);
        led[1].setRGB( 50, 22, 0);
        led[2].setRGB( 50, 50, 0);
        led[3].setRGB( 22 , 50, 0);
        led[4].setRGB( 0, 50, 0);

        break;
      case 4:
        led[0].setRGB( 50, 0, 0);
        led[1].setRGB( 50, 22, 0);
        led[2].setRGB( 50, 50, 0);
        led[3].setRGB( 22 , 50, 0);
        break;
      case 3:
        led[0].setRGB( 50, 0, 0);
        led[1].setRGB( 50, 22, 0);
        led[2].setRGB( 50, 50, 0);
        break;
      case 2:
        led[0].setRGB( 50, 0, 0);
        led[1].setRGB( 50, 22, 0);
        break;
      case 1:
        led[0].setRGB( 50, 0, 0);
        break;
      case 0:
        for (int i = 0; i < 200; i++) {
          fill_solid( led, NUM_LEDS, CRGB(0, 0, i));
          FastLED.show();
          delay(10);
        }
        for (int i = 0; i < NUM_LEDS; i++) {
          fill_rainbow(led, i, 0, 5);
          FastLED.show();
          delay(10);
        }
        player2.resetPlayer();
        player2.energyPlayerC = 5;
        player1.resetPlayer();
        player1.energyPlayerC = 5;
        break;
    }
    switch (player2.energyPlayerC) {
      case 5:
        led[143].setRGB( 50, 0, 0);
        led[142].setRGB( 50, 22, 0);
        led[141].setRGB( 50, 50, 0);
        led[140].setRGB( 22 , 50, 0);
        led[139].setRGB( 0, 50, 0);

        break;
      case 4:
        led[143].setRGB( 50, 0, 0);
        led[142].setRGB( 50, 22, 0);
        led[141].setRGB( 50, 50, 0);
        led[140].setRGB( 22 , 50, 0);
        break;
      case 3:
        led[143].setRGB( 50, 0, 0);
        led[142].setRGB( 50, 22, 0);
        led[141].setRGB( 50, 50, 0);
        break;
      case 2:
        led[143].setRGB( 50, 0, 0);
        led[142].setRGB( 50, 22, 0);
        break;
      case 1:
        led[143].setRGB( 50, 0, 0);
        break;
      case 0:
        for (int i = 0; i < 200; i++) {
          fill_solid( led, NUM_LEDS, CRGB(i, 0, 0));
          FastLED.show();
          delay(10);
        }
        for (int i = 0; i < NUM_LEDS; i++) {
          fill_rainbow(led, i, 0, 5);
          FastLED.show();
          delay(10);
        }
        player2.resetPlayer();
        player2.energyPlayerC = 5;
        player1.resetPlayer();
        player1.energyPlayerC = 5;
        break;
    }

    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
