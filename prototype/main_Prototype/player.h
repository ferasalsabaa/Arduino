class Player {

  public:
    int playerPositionC;
    int powerPlayer;
    int farPlayer;
    int j = 10;
    Player(int playerPosition, int power, int far) {
      playerPositionC = playerPosition;
      powerPlayer = power;
      farPlayer = far;
    }
    void playShow(int& sensorValue, CRGB led[], int NUM_LEDS, int& sensorValueB, int playerPosition) {
      brighten(1, led);
      if (playerPosition == 0) {
        if (sensorValueB < 7 && sensorValue < 7) {
          brighten(1, led);
        }
      }

    }

    void brighten(int now, CRGB led[]) {
      Chrono darkTime;
      Chrono brightTime;

      while (j < 200) {
        if (brightTime.hasPassed(800) == 1) {
          brightTime.restart();
          led[50].setRGB( j, 0, 0);
          FastLED.show();
          j++;
        }
      }


    }
};
