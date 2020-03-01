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
float gravity = 0.003;

float color50 = 90;
float color20 = 60;

float colorDefence1 = 90;
float colorDefence2 = 90;

float fade = 0.0;


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

float OneFireFirstPosition = 5;

float OnePlayerFireFirst = 0.0;
float OnePlayerFireSecond = 0.0;

int OneEnergyPlayer = 5;

bool OnefireCase = false;


Player player1(OnePlayerPosition, OneFireFirstPosition, OnePlayerFireFirst, OnePlayerFireSecond, OneEnergyPlayer);

// ---------------------------------player 2------------------------------------------
int TwoPlayerPosition = 137;

float TwoFireFirstPosition = 137;

float TwoPlayerFireFirst = 0.0;
float TwoPlayerFireSecond = 0.0;

int TwoEnergyPlayer = 5;


Player player2(TwoPlayerPosition, TwoFireFirstPosition, TwoPlayerFireFirst, TwoPlayerFireSecond, TwoEnergyPlayer);




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

    if (color50 < 90 && color20 < 60) {
      color50 += 0.4;
      color20 += 0.2;
    } else {
      color50 = 0;
      color20 = 0;
    }

    if (colorDefence1 < 90) {
      colorDefence1 += 0.8;
    } else {
      colorDefence1 = 0;
    }
    if (player2.effect3 == false && player1.effect3) {
      if (colorDefence1 > 5) {
        player1.defenceStrong = true;
      } else {
        player1.defenceStrong = false;
      }
    }

    if (colorDefence2 < 90) {
      colorDefence2 += 0.8;
    } else {
      colorDefence2 = 0;
    }

    if (player1.effect3 == false && player2.effect3 == false) {
      if (colorDefence2 > 10) {
        player2.defenceStrong = true;
      } else {
        player2.defenceStrong = false;
      }
    }

    if (player1.effect3 == true) {
      player1.fireFlame -= 0.06;
      player1.fireFlameWave2 -= 0.2;
      player1.fireFlameWave3 -= 0.15;
      player1.fireFlameWave4 -= 0.32;
      player1.fireFlameWave5 -= 0.32;
      player1.fireFirstPositionC = player1.fireFirstPositionC + player1.speedC;
      player1.speedC = player1.speedC + gravity;



      if (player1.fireFirstPositionC > 135 && player1.fireFirstPositionC < 136 && colorDefence2 > 35 && player2.defence == true) {
        player2.resetPlayerAttack();
        player1.resetPlayer();
      }
      if ( player1.fireFirstPositionC > 140) {
        player2.energyPlayerC = player2.energyPlayerC - 1;
        player2.resetPlayerAttack();
        player1.resetPlayer();
      }
    }
    if (player2.effect3 == true) {
      player2.fireFlame -= 0.06;
      player2.fireFlameWave2 -= 0.2;
      player2.fireFlameWave3 -= 0.15;
      player2.fireFlameWave4 -= 0.32;
      player2.fireFlameWave5 -= 0.32;
      player2.fireFirstPositionC = player2.fireFirstPositionC - player2.speedC;
      player2.speedC = player2.speedC + gravity;
      if (player2.fireFirstPositionC < 9 && player2.fireFirstPositionC > 7 && colorDefence1 > 35 && player1.defence == true) {
        player2.resetPlayer();
        player1.resetPlayerAttack();
      }
      if ( player2.fireFirstPositionC < 4) {
        player1.energyPlayerC = player1.energyPlayerC - 1;
        player2.resetPlayer();
        player1.resetPlayerAttack();
      }
    } //else {
    player1.playShow(sensorWertA, sensorWertB);
    player2.playShow(sensorWertC, sensorWertD);
    //}
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
    led[twoPos +  1].setRGB(0, 0, player2.playerFireSecondC);

    switch (player1.energyPlayerC) {
      case 5:
        led[player1.playerPositionC - 6].setRGB( 0, color50, 0);
        led[player1.playerPositionC - 5].setRGB( 0, color50, 0);
        led[player1.playerPositionC - 4].setRGB( 0, color50, 0);
        led[player1.playerPositionC - 3].setRGB( 0, color50, 0);
        led[player1.playerPositionC - 2].setRGB( 0, color50, 0);

        break;
      case 4:
        led[player1.playerPositionC - 6].setRGB( color20 , color50, 0);
        led[player1.playerPositionC - 5].setRGB( color20 , color50, 0);
        led[player1.playerPositionC - 4].setRGB( color20 , color50, 0);
        led[player1.playerPositionC - 3].setRGB( color20 , color50, 0);
        break;
      case 3:
        led[player1.playerPositionC - 6].setRGB( color50, color50, 0);
        led[player1.playerPositionC - 5].setRGB( color50, color50, 0);
        led[player1.playerPositionC - 4].setRGB( color50, color50, 0);
        break;
      case 2:
        led[player1.playerPositionC - 6].setRGB( color50, color20, 0);
        led[player1.playerPositionC - 5].setRGB( color50, color20, 0);
        break;
      case 1:
        led[player1.playerPositionC - 6].setRGB( color20, 0, 0);
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
        player2.resetPlayerNewGame();
        player1.resetPlayerNewGame();
        break;
    }
    switch (player2.energyPlayerC) {
      case 5:
        led[player2.playerPositionC + 6].setRGB( 0, color50, 0);
        led[player2.playerPositionC + 5].setRGB( 0, color50, 0);
        led[player2.playerPositionC + 4].setRGB( 0, color50, 0);
        led[player2.playerPositionC + 3].setRGB( 0, color50, 0);
        led[player2.playerPositionC + 2].setRGB( 0, color50, 0);

        break;
      case 4:
        led[player2.playerPositionC + 6].setRGB(  color20 , color50, 0);
        led[player2.playerPositionC + 5].setRGB(  color20 , color50, 0);
        led[player2.playerPositionC + 4].setRGB( color20 , color50, 0);
        led[player2.playerPositionC + 3].setRGB( color20 , color50, 0);
        break;
      case 3:
        led[player2.playerPositionC + 6].setRGB( color50, color50, 0);
        led[player2.playerPositionC + 5].setRGB(color50, color50, 0);
        led[player2.playerPositionC + 4].setRGB( color50, color50, 0);
        break;
      case 2:
        led[player2.playerPositionC + 6].setRGB( color50, color20, 0);
        led[player2.playerPositionC + 5].setRGB( color50, color20, 0);
        break;
      case 1:
        led[player2.playerPositionC + 6].setRGB( color50, 0, 0);
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
        player2.resetPlayerNewGame();
        player1.resetPlayerNewGame();
        break;
    }
    if (player1.effect3 == true && player2.effect3 == true && (onePos == twoPos || onePos == twoPos - 1 || onePos == twoPos + 1)) {
      if (onePos < 48) {
        fill_solid( led, NUM_LEDS, CRGB(200, 0, 200));
        player2.resetPlayer();
      } else if (onePos > 96) {
        fill_solid( led, NUM_LEDS, CRGB(200, 0, 200));
        player1.resetPlayer();
      } else {
        fill_solid( led, NUM_LEDS, CRGB(200, 0, 200));
        player2.energyPlayerC = player2.energyPlayerC - 1;
        player1.energyPlayerC = player1.energyPlayerC - 1;
        player1.resetPlayer();
        player2.resetPlayer();
      }


    }
    if (player1.effect1 == true && onePos > 90) {
      led[100].setRGB(200, 0, 0);
      led[99].setRGB(200, 0, 0);
      led[98].setRGB(200, 0, 0);
      led[97].setRGB(200, 0, 0);
      led[96].setRGB(200, 0, 0);
    }

    if (player2.effect1 == true && twoPos < 50) {
      led[40].setRGB(0, 0, 200);
      led[41].setRGB(0, 0, 200);
      led[42].setRGB(0, 0, 200);
      led[43].setRGB(0, 0, 200);
      led[44].setRGB(0, 0, 200);
    }


    if (player2.effect3 == true) {
      led[twoPos + 1].setRGB(0, 0, 170);
      led[twoPos + 2].setRGB(0, 0, player2.playerFireSecondC);
      led[twoPos + 3].setRGB(0, 0, player2.playerFireSecondC);
      led[twoPos + 4].setRGB(0, 0, 140);
      led[twoPos + 5].setRGB(0, 0, 130);
      if (twoPos < 132) {
        led[twoPos + 6].setRGB(0, 0, 120);
        led[twoPos + 7].setRGB(0, 0, 110);
        led[twoPos + 8].setRGB(0, 0, 100);
        led[twoPos + 9].setRGB(0, 0, 90);
        led[twoPos + 10].setRGB(0, 0, 80);
      }
      if (twoPos < 127) {
        led[twoPos + 10].setRGB(0, 0, 80);
        led[twoPos + 11].setRGB(0, 0, 70);
        led[twoPos + 12].setRGB(0, 0, 60);
        led[twoPos + 13].setRGB(0, 0, 50 );
        led[twoPos + 14].setRGB(0, 0, 40);
      }
      if (twoPos < 122) {
        led[twoPos + 15].setRGB(0, 0, 30);
        led[twoPos + 16].setRGB(0, 0, 20);
        led[twoPos + 17].setRGB(0, 0, 10);
        led[128].setRGB(0, 0, player2.fireFlame - 0.1);
        led[126].setRGB(0, 0, player2.fireFlame);
        led[124].setRGB(0, 0, player2.fireFlame + 0.6);
        float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
        float result = player2.fireFlame / r2;
        led[134].setRGB(0, 0, result + 0.6);
        led[136].setRGB(0, 0, player2.fireFlame + 0.6);
      }
      if (twoPos < 106) {
        for (int i = 125; i > 105; i--) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player2.fireFlame / r2;
            led[i].setRGB(0, 0, player2.fireFlame + result);
          }
        }
      }
      if (twoPos < 89) {
        for (int k = 108; k > 88; k--) {
          if (k % 2 == 0) {
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player2.fireFlameWave2 / r2;
            led[k].setRGB(0, 0, player2.fireFlameWave2 + result);
          }
        }
      }
      if (twoPos < 72) {
        for (int i = 91; i > 71; i--) {
          if (i % 2 != 0 || i % 3 == 0) {
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player2.fireFlameWave3 / r2;
            led[i].setRGB(0, 0, result);
          }
        }
      }
      if (twoPos < 55) { // - 17
        for (int k = 74; k > 54; k--) { // 55 + 19; -20
          if (k % 2 == 0) {
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player2.fireFlameWave4 / r2;
            led[k].setRGB(0, 0, player2.fireFlameWave4 + result);
          }
        }
      }
      if (twoPos < 38) {
        for (int k = 57; k > 37; k--) {
          if (k % 2 == 0 || k % 3 == 0) {
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player2.fireFlameWave5 / r2;
            led[k].setRGB(0, 0, player2.fireFlameWave5 + result);
          }
        }
      }
      if (twoPos < 18) {
        led[player1.playerPositionC - 6].setRGB( 0, 0, 200);
        led[player1.playerPositionC - 5].setRGB( 0, 0, 200);
        led[player1.playerPositionC - 4].setRGB( 0, 0, 200);
        led[player1.playerPositionC - 3].setRGB( 0 , 0, 200);
        led[player1.playerPositionC - 2].setRGB( 0, 0, 200);
      }
    }

    if (player1.effect3 == true) {
      led[onePos - 1].setRGB(170, 0, 0);
      led[onePos - 2].setRGB(player1.playerFireSecondC, 0, 0);
      led[onePos - 3].setRGB(player1.playerFireSecondC, 0, 0);
      led[onePos - 4].setRGB(140, 0, 0);
      led[onePos - 5].setRGB(130, 0, 0);
      if (onePos > 10) {
        led[onePos - 6].setRGB(120, 0, 0);
        led[onePos - 7].setRGB(110, 0, 0);
        led[onePos - 8].setRGB(100, 0, 0);
        led[onePos - 9].setRGB(90, 0, 0);
        led[onePos - 10].setRGB(80, 0, 0);
      }
      if (onePos > 15) {
        led[onePos - 10].setRGB(80, 0, 0);
        led[onePos - 11].setRGB(70, 0, 0);
        led[onePos - 12].setRGB(60, 0, 0);
        led[onePos - 13].setRGB(50, 0, 0 );
        led[onePos - 14].setRGB(40, 0, 0);
      }
      if (onePos > 20) {
        led[onePos - 15].setRGB(30, 0, 0);
        led[onePos - 16].setRGB(20, 0, 0);
        led[onePos - 17].setRGB(10, 0, 0);
      }
      if (onePos > 25) {
        for (int i = 6; i < 26; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlame / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 42) {
        for (int i = 15; i < 35; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlame / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 59) {
        for (int i = 40; i < 60; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlameWave2 / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 76) {
        for (int i = 57; i < 77; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlameWave3 / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 93) {
        for (int i = 76; i < 96; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlameWave4 / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 110) {
        for (int i = 91; i < 111; i++) {
          if (i % 2 != 0 || i % 3 == 0) {

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
            float result = player1.fireFlameWave5 / r2;
            led[i].setRGB(player1.fireFlame + result, 0, 0);
          }
        }
      }
      if (onePos > 127) {
        led[player2.playerPositionC + 6].setRGB( 200, 0, 0);
        led[player2.playerPositionC + 5].setRGB( 200, 0, 0);
        led[player2.playerPositionC + 4].setRGB( 200, 0, 0);
        led[player2.playerPositionC + 3].setRGB( 200 , 0, 0);
        led[player2.playerPositionC + 2].setRGB( 200, 0, 0);

      }
    }

    if (player1.defence == true) {
      led[player1.playerPositionC + 1].setRGB( colorDefence1 - 50, 0, 0);
      led[player1.playerPositionC + 2].setRGB( colorDefence1 - 20 , 0, 0);
      led[player1.playerPositionC + 3].setRGB( colorDefence1, 0, 0);
      led[player1.playerPositionC + 4].setRGB( colorDefence1 - 20 , 0, 0);
      led[player1.playerPositionC + 5].setRGB(colorDefence1 - 50, 0, 0);
    }

    if (player2.defence == true) {
      led[player2.playerPositionC - 1].setRGB( 0, 0, colorDefence2 - 50);
      led[player2.playerPositionC - 2].setRGB( 0, 0, colorDefence2 - 20);
      led[player2.playerPositionC - 3].setRGB( 0, 0, colorDefence2);
      led[player2.playerPositionC - 4].setRGB( 0, 0, colorDefence2 - 20);
      led[player2.playerPositionC - 5].setRGB( 0 , 0, colorDefence2 - 50);
    }
    /*
        if (player1.defence == true) {
      led[player1.playerPositionC + 1].setRGB( colorDefence1 - 50, 0, 0);
      led[player1.playerPositionC + 2].setRGB( colorDefence1 - 50, 0, 0);
      led[player1.playerPositionC + 3].setRGB( colorDefence1 - 20 , 0, 0);
      led[player1.playerPositionC + 4].setRGB( colorDefence1 - 20 , 0, 0);
      led[player1.playerPositionC + 5].setRGB(colorDefence1, 0, 0);
      }

      if (player2.defence == true) {
      led[player2.playerPositionC - 1].setRGB( 0, 0, colorDefence2 - 50);
      led[player2.playerPositionC - 2].setRGB( 0, 0, colorDefence2 - 50);
      led[player2.playerPositionC - 3].setRGB(0, 0, colorDefence2 - 20);
      led[player2.playerPositionC - 4].setRGB( 0, 0, colorDefence2 - 20);
      led[player2.playerPositionC - 5].setRGB( 0, 0, colorDefence2);
      }
    */


    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
