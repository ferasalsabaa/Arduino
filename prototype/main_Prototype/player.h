class Player {

  public:
    int playerPositionC;
    int powerPlayer;
    int farPlayer;
    int j = 0;
    Player(int playerPosition, int power, int far) {
      playerPositionC = playerPosition;
      powerPlayer = power;
      farPlayer = far;
    }
    void playShow(int& sensorValue, CRGB led[], int NUM_LEDS, int& sensorValueB, int& playerFire) {
     Chrono brightTime;
      if (sensorValue < 7 && playerFire <= 200) {
    //    if (brightTime.hasPassed(8) == 1) {
          brightTime.restart();
          playerFire++;
        //  FastLED.show();
      //  }
      }
    }

    void brighten(int now, CRGB led[], int& sensorValueB, int& sensorValue) {
      Chrono darkTime;
      Chrono brightTime;

      while (j < 200 && sensorValue < 7) {
        if (brightTime.hasPassed(800) == 1) {
          brightTime.restart();
          led[50].setRGB( j, 0, 0);
          FastLED.show();
          j++;
        }
      }



    }
};
