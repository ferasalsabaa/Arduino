class Car_class {

  public:


    void moveAlong(int& sensorValue, int& now, CRGB led[], int NUM_LEDS, int& sensorValueB) {
      if (sensorValueB < 8)   //modify this threshold and relaunchVel to adjust sensitivity
      {
        if (now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25) {
          led[now].setRGB(0, 0, 220);
          FastLED.show();
          delay(100);
          now = now + 1 ;
        } else {
          if (now == 0) {
            led[now].setRGB(220, 62, 220);
            FastLED.show();
            delay(100);
          } else {
            FastLED.show();
            delay(100);
            now = now - 1 ;
          }
        }

      } else if (sensorValue < 8) {
        if (now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25) {
          led[now].setRGB(0, 0, 220);
          FastLED.show();
          delay(1000);
          now = now + 1 ;
        } else {
          FastLED.show();
          delay(100);
          now = now + 1 ;
        }
        if (now == NUM_LEDS) {
          now = 0;
          for (int i = 0; i < NUM_LEDS; i++) {
            fill_rainbow(led, i, 0, 5);
            FastLED.show();
            delay(10);
          }
        }

      }

    }


};
