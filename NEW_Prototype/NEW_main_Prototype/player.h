
class Player {

  public:
    int playerPositionC;

    float fireFirstPositionC;
    float fireSecondPositionC;

    float playerFireFirstC;
    float playerFireSecondC;

    int energyPlayerC;

    bool FirstfireCaseC;


    float speedC = 0;
    float gravity = 0.009;

    boolean effect1 = false;
    int countEffect1 = 0;


    boolean effect2 = false;

    boolean effect3 = false;


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
      if (effect1 == true) {
        if (countEffect1 > 250) {
          resetPlayer();
        }
        // fireFirstPositionC = fireFirstPositionC + 0.4;
        fireFirstPositionC = fireFirstPositionC + speedC;
        speedC = speedC + gravity;
        playerFireFirstC = playerFireFirstC - 0.7;
        playerFireSecondC = playerFireSecondC -0.7 ; 
        if (fireFirstPositionC > 100) {
          speedC = speedC * -1;
          countEffect1 ++;
        }
        if (fireFirstPositionC < 1) {
          fireFirstPositionC = 1;
        }
        countEffect1 ++;
      } else if (effect2 == true) {
        fireFirstPositionC = fireFirstPositionC + speedC;
        speedC = speedC + gravity;
        if (fireFirstPositionC > 140) {
          resetPlayer();
        }
      } else if (effect3 == true) {

      } else {
        if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC <= 200) {
          playerFireFirstC = playerFireFirstC + 0.2;
        } else if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC >= 200 && playerFireSecondC < 200) {
          playerFireSecondC = playerFireSecondC + 0.2;
        }
        if (sensorValue < 7 && sensorValueB < 7 && playerFireSecondC > 10) {
          if (sensorValue > 3 && sensorValueB > 3) {
            effect1 = true;
          } else if (sensorValueB < 4 && sensorValue < 4) {
            effect2 = true;
          } else if (sensorValue > 4 && sensorValueB < 4) {
            effect3 = true;
          }
        }

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
    void resetPlayer() {
      effect1 = false;
      effect2 = false;
      effect3 = false;
      countEffect1 = 0;
      fireFirstPositionC = 7;
      fireSecondPositionC = 8;

      playerFireFirstC = 0;
      playerFireSecondC = 0;

      energyPlayerC = 5;

      FirstfireCaseC = false;
      speedC = 0;
    }
};
