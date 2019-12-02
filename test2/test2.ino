#include <FastLED.h>
#include <Chrono.h>
#include "Car_class.h"

#define NUM_LEDS 144 // all leds
#define LED_PIN 14   // place the led

const int ledLength = 8;     // later long of car
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS  60
const int fps = 100;

int carOnePosition = 0;  // where is the car
int carTwoPosition = 0;  // where is the car

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


//create chrono objects for timed actions:
Chrono cNextFrame(Chrono::MICROS);
Chrono cCheckInput;


CRGB led [NUM_LEDS];

Car_class car1; // first car
Car_class car2; // first car

void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(led, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip); //LEDS.setCorrection(Candle); or (Tungsten40W)
  FastLED.setBrightness(MAX_BRIGHTNESS);

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
  // sensorValue = filter(analogRead(sensorPinA), 0.5, sensorWertA);
  //  sensorWertA = filter(analogRead(sensorPinA), 0.25, sensorWertA);
  //  sensorValueTest = map(sensorValue, 0, 1023, 0, 100);
  // sensorValue = sensorWertA
 // sensorWertA = analogRead(sensorPinA);
    sensorWertA = filter(analogRead(sensorPinA), 0.25, sensorWertA);
    sensorWertB = filter(analogRead(sensorPinB), 0.25, sensorWertB);
    sensorWertC = filter(analogRead(sensorPinC), 0.25, sensorWertC);
    sensorWertD = filter(analogRead(sensorPinD), 0.25, sensorWertD);
      sensorWertA = map(sensorWertA, 0, 1023, 0, 100);
      sensorWertB = map(sensorWertB, 0, 1023, 0, 100);
      sensorWertC = map(sensorWertC, 0, 1023, 0, 100);
      sensorWertD = map(sensorWertD, 0, 1023, 0, 100);
 // sensorWertB = analogRead(sensorPinB);
 // sensorWertC = analogRead(sensorPinC);
 // sensorWertD = analogRead(sensorPinD);
  Serial.println(sensorWertA);               //send debug data to the Arduino Serial Monitor


  //INTERACTIVITY: work with sensor data every X ms
  if (cCheckInput.hasPassed(1)) {
    cCheckInput.restart();
    car1.moveAlong(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB);
    car2.moveAlong(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD);
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...

    cNextFrame.restart();
    FastLED.clear();
    led[20].setRGB(220, 0, 0);
    led[21].setRGB(220, 0, 0);
    led[22].setRGB(220, 0, 0);
    led[23].setRGB(220, 0, 0);
    led[24].setRGB(220, 0, 0);
    led[25].setRGB(220, 0, 0);
    if (carOnePosition == carTwoPosition) {
      led[carOnePosition].setRGB(255, 51, 51);
      led[carTwoPosition].setRGB(255, 51, 51);

    } else {
      led[carOnePosition].setRGB(102, 0, 102);
      led[carTwoPosition].setRGB(255, 255, 102);
    }
    FastLED.show();
  }

} // end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
