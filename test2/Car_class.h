class Car_class{

public:

int now=0;    // where is the car



#define ctsPin 19
int sensorValue  = 0;

void testMethod(int& sensorValue, int& now, CRGB led[], int NUM_LEDS){
      if (sensorValue > 900)   //modify this threshold and relaunchVel to adjust sensitivity
    { int count=0;
      if(now == 20 || now == 21 || now == 22 || now == 23 || now == 24 || now == 25){
            led[now].setRGB(0,0,220);
                   FastLED.show();
                   delay(1000);
      now = now + 1 ;
        } else {
      led[now].setRGB(220,62,220);
      FastLED.show();
      now = now + 1 ;
        }
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
