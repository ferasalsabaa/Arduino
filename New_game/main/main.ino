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

int carOnePosition = 0;  // where is the car
int carTwoPosition = 0;  // where is the car

int carOneCount = 0;  // bouns
int carTwoCount = 0;  // bouns

#define ctsPin 19  // place the sensor

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

int change = 0;


//create chrono objects for timed actions:
Chrono cNextFrame(Chrono::MICROS);
Chrono cCheckInput;


CRGB led [NUM_LEDS];

Player car1; // first car
Player car2; // first car

unsigned long previousTimeFire;
unsigned long previousTimeBright;
unsigned long previousTimeDark;

int x_counter_Fire = 130;
int x_counter_bright = 100;
int x_counter_dark = 130;

int fire_count;

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
  previousTimeFire = 0;
  previousTimeBright = 0;
  previousTimeDark = 0;
}

void loop()
{
  unsigned long currentTime = millis();
  unsigned long currentTime_bright = millis();
  unsigned long currentTime_dark = millis();

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
    if (carOnePosition < carTwoPosition) {
      car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 2, change);
      car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1, change);
    } else if (carOnePosition > carTwoPosition) {
      car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 2, change);
      car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1, change);
    } else {
      if (carTwoPosition == 0 && carOnePosition == 0) {
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1, change);
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1, change);
      }
      else if (sensorWertA < sensorWertC) {
        carTwoPosition --;
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 2, change);
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1, change);
      } else {
        carOnePosition --;
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 2, change);
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1, change);
      }
    }
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...

    cNextFrame.restart();
    FastLED.clear();
    //first one:
    led[20].setRGB(220, 0, 0);
    led[21].setRGB(220, 0, 0);
    led[22].setRGB(220, 0, 0);
    led[23].setRGB(220, 0, 0);
    led[24].setRGB(220, 0, 0);
    led[25].setRGB(220, 0, 0);
    //second one:
    led[90].setRGB(0, 0, 220);
    led[91].setRGB(0, 0, 220);
    led[92].setRGB(0, 0, 220);
    led[93].setRGB(0, 0, 220);
    led[94].setRGB(0, 0, 220);
    led[95].setRGB(0, 0, 220);
    led[96].setRGB(0, 0, 220);
    led[97].setRGB(0, 0, 220);
    led[98].setRGB(0, 0, 220);
    led[99].setRGB(0, 0, 220);
    led[100].setRGB(0, 0, 220);
    led[101].setRGB(0, 0, 220);

    //third blocks
    led[110].setRGB(248, 255, 10);
    led[111].setRGB(248, 255, 10);
    led[138].setRGB(0, 255, 10);
    //new blocks

    if (carOnePosition == carTwoPosition) {
      led[carOnePosition].setRGB(255, 51, 51);
      led[carTwoPosition].setRGB(255, 51, 51);

    } else if (carOnePosition == 144) {
      carOnePosition = 0;
    } else if (carTwoPosition == 144) {
      carTwoPosition = 0;
    }
    else {
      led[carOnePosition].setRGB(102, 0, 102);
      led[carTwoPosition].setRGB(255, 255, 102);
    }
    if (currentTime - previousTimeFire >= 70) {
      if (change <= 3) {
        previousTimeFire = currentTime;
        //leds[x].setRGB(255,69,0);
        led[x_counter_Fire].setRGB(220, 0, 0);
        FastLED.show();
        if (++x_counter_Fire >= 136) x_counter_Fire = 130;
        led[130].setRGB(248, 255, 10);
        led[131].setRGB(248, 255, 10);

        if (carOnePosition == 130 || carOnePosition == 131 || carOnePosition == 132 || carOnePosition == 133 || carOnePosition == 134 || carOnePosition == 135 || carOnePosition == 136 ) {
          brighten(carOnePosition);
          carOnePosition = 0;
        }
        if (carTwoPosition == 130 || carTwoPosition == 131 || carTwoPosition == 132 || carTwoPosition == 133 || carTwoPosition == 134 || carTwoPosition == 135 || carTwoPosition == 136) {
          brighten(carTwoPosition);
          carTwoPosition = 0;
        }

      } else {
         led[130].setRGB(10, 0, 0);
        led[131].setRGB(10, 0, 0);
        if (carTwoPosition == 138 || carOnePosition == 138) {
          brighten(carTwoPosition);
          brighten(carOnePosition);
          for (int i = 0; i < NUM_LEDS; i++) {
            fill_rainbow(led, i, 0, 5);
            FastLED.show();
            delay(10);
          }
          carOnePosition = carTwoPosition = 0;
          carTwoCount =   carOneCount = 0;  // bouns
          change = 0;
        }

      }
    }
    if (currentTime_bright - previousTimeBright >= 500) {
      previousTimeBright = currentTime_bright;
      led[70].setRGB( 0, 0, x_counter_bright);
      led[40].setRGB( 0, 0, x_counter_bright);
      led[42].setRGB( 0, 0, x_counter_bright);
      FastLED.show();
      if (x_counter_bright ++ >= 200) x_counter_bright = 0;
    }

  }

} // end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
void brighten(int now) {
  uint16_t j;
  for (j = 50; j < 200; j++) {
    led[now].setRGB( j, 0, 0);
    FastLED.show();
    delay(5);
  }


  for (j = 200; j > 0; j--) {
    led[now].setRGB( j, 0, 0);

    FastLED.show();
    delay(5);
    Serial.println(j);
  }
}
