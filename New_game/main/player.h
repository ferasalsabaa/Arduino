class Player {

  public:
    void blocks(int& sensorValue, int& now, CRGB led[], int NUM_LEDS, int& sensorValueB, int& count, int speedBounos, int& change) {
      if (sensorValueB < 7 && sensorValue < 7) {
        if (now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25) {
          //led[now].setRGB(0, 0, 220);
          FastLED.show();
          delay(70 / speedBounos);
          now = now + 1 ;
        } else if (now == 90 || now == 91 || now == 92 || now == 93 || now == 94 || now == 95 || now == 96 || now == 97 || now == 98 || now == 99 || now == 100 || now == 101) {

          FastLED.show();

        } else if (now == 70 || now == 42 || now == 40) {
          count ++;
          delay(100 / speedBounos);
          now = now + 1 ;
          for(int i=now; i<133; i++){
            led[i].setRGB(0,220,0);
            delay(10);
            FastLED.show();
            led[i] = CRGB::Black;
            }
        } else if (now == 110 || now == 111) {
          FastLED.show();
          delay(1000 / speedBounos);
          now = now + 1 ;
        }  else if ((now == 130 || now == 131) && count >=3) {
          now = now + 1 ;
          FastLED.show();
          change --;
        } else {
          if (now == 0) {
            // led[now].setRGB(220, 62, 220);
            now = now + 1 ;
            FastLED.show();
            delay(100 / speedBounos);
          } else {
            FastLED.show();
            delay(150 / speedBounos);
            now = now + 1 ;
          }
        }
      }
      if (sensorValue < 7 && sensorValueB > 7) {
        if (now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25) {
          //led[now].setRGB(0, 0, 220);
          FastLED.show();
          delay(1000 / speedBounos);
          now = now + 1 ;
        } else if (now == 90 || now == 91 || now == 92 || now == 93 || now == 94 || now == 95 || now == 96 || now == 97 || now == 98 || now == 99 || now == 100 || now == 101) {
          if (sensorValue < 4 ) {
            FastLED.show();
            delay(1000 / speedBounos);
            now = now + 1 ;
          } else {
            FastLED.show();
            delay(60 / speedBounos);
            now = now + 1 ;
          }
        } else if (now == 110 || now == 111) {
          if (count >= 3) {
            FastLED.show();
            delay(60 / speedBounos);
            now = now + 1 ;
          } else {
            FastLED.show();
            delay(10000 / speedBounos);
            now = now + 1 ;
          }
        }  else {
          if (now == 0) {
            // led[now].setRGB(220, 62, 220);
            now = now + 1 ;
            FastLED.show();
            delay(120 / speedBounos);
          } else {
          led[now].fadeLightBy(70);
          delay(1000);
            FastLED.show();
            delay(100 / speedBounos);
            now = now + 1 ;
          }
        }
      }
      if (sensorValue > 7 && sensorValueB < 7) {
        if (now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25) {
          //led[now].setRGB(0, 0, 220);
          FastLED.show();
          delay(70 / speedBounos);
          now = now - 1 ;
        } else if (now == 90 || now == 91 || now == 92 || now == 93 || now == 94 || now == 95 || now == 96 || now == 97 || now == 98 || now == 99 || now == 100 || now == 101) {
          if (sensorValueB > 4 ) {
            FastLED.show();
            delay(60 / speedBounos);
            now = now - 1 ;
          } else {
            FastLED.show();
            delay(1000 / speedBounos);
            now = now - 1 ;
          }
        } else {
          if (now == 0) {
            // led[now].setRGB(220, 62, 220);
            FastLED.show();
            delay(100 / speedBounos);
          } else {
            FastLED.show();
            delay(60 / speedBounos);
            now = now - 1 ;
          }
        }
      }
    }

    void fad (int now, CRGB led[]){
      int count = 80;
      for(int i = count; i!=0 ; i--)
     led[i].maximizeBrightness(i);
     FastLED.show();
     delay(5);
      
      }


};