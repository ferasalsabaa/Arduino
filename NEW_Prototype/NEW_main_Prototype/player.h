class Player {

  public:
    int playerPositionC;

    float fireFirstPositionC;
    float fireSecondPositionC;

    float playerFireFirstC;
    float playerFireSecondC;

    int energyPlayerC;

    bool FirstfireCaseC;

    Player(int playerPosition, float fireFirstPosition, float fireSecondPosition, float playerFireFirst, float playerFireSecond, int energyPlayer, bool FirstfireCase) {
      playerPositionC = playerPosition;

      fireFirstPositionC = fireFirstPosition;
      fireSecondPositionC = fireSecondPosition;

      playerFireFirstC = playerFireFirst;
      playerFireSecondC = playerFireSecond;

      energyPlayerC = energyPlayer;

      FirstfireCaseC = FirstfireCase;

    }
    void playShow(int& sensorValue, int& sensorValueB) {
      if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC <= 200) {
        playerFireFirstC = playerFireFirstC + 0.2;
      } else if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC >= 200) {
        playerFireSecondC = playerFireSecondC + 0.2;
      }
      if (sensorValue < 7 && sensorValueB < 7 && playerFireSecondC > 10) {
        fireFirstPositionC = fireFirstPositionC + 0.4;
      }
      if (fireFirstPositionC > 140) {

         fireFirstPositionC = 1;
         fireSecondPositionC = 2;

         playerFireFirstC = 0;
         playerFireSecondC = 0;

        int energyPlayerC = 0;

        bool FirstfireCaseC = false;
      }
    }

    void playShowFireFirst(int& sensorValue, int& sensorValueB, float& i) {
      if (sensorValueB > 7 && sensorValue < 7  && i <= 142) {
        i = i + 1;
      }
    }

    boolean defenceTest(int& sensorWertC, int& sensorWertD) {
      if (sensorWertD < 7 && sensorWertC > 7) {
        return true;
      } else {
        return false;
      }
    }
    void resetPlayer(int& playerFireSecond, int& playerFireFirst, int& fireCase, boolean& defence, boolean& defenceShow) {
      playerFireSecond = 0;
      playerFireFirst = 0;
      fireCase = 0;
      defence = false;
      defenceShow = false;
    }
};
