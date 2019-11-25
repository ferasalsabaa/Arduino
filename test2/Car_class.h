class Car_class{

public:

int now=0;    // where is the car



#define ctsPin 19
int sensorValue  = 0;

void testMethod(int& sensorValue, int& now, CRGB led[], int NUM_LEDS){
      if (sensorValue > 900)   //modify this threshold and relaunchVel to adjust sensitivity
    {
      led[now].setRGB(220,62,220);
      FastLED.show();
      now = now + 1 ;
      if(now == NUM_LEDS){
        now = 0;
      for(int i=0;i<NUM_LEDS;i++){
      fill_rainbow(led, i, 0, 5);
      FastLED.show();
       delay(10);
  }
        }
    }
  
}  
  
 
};
