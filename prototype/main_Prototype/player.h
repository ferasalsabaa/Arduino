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
      if (sensorValue < 7 && playerFire <= 200) {
        playerFire++;
        if (playerFire >= 199) {
        }
      }
    }
};
