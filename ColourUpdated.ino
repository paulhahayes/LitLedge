#include <FastLED.h>
#define NUM_LEDS  119
#define LED_PIN  12
#define NUM_SENSORS 10
#define True 1
#define False 0

CRGB rawleds[NUM_LEDS];
CRGBSet leds(rawleds, NUM_LEDS);
CRGBSet leds1(leds(0, 14));
CRGBSet leds2(leds(15, 26));
CRGBSet leds3(leds(27, 38));
CRGBSet leds4(leds(39, 49));
CRGBSet leds5(leds(50, 60));
CRGBSet leds6(leds(61, 73));
CRGBSet leds7(leds(74, 85));
CRGBSet leds8(leds(86, 97));
CRGBSet leds9(leds(98, 109));
CRGBSet leds10(leds(110, 118));
struct CRGB * ledarray[] = { leds1, leds2, leds3, leds4, leds5, leds6, leds7, leds8, leds9, leds10 }; 

int sizes[10] = {15, 12, 12, 11, 11, 13, 12, 12, 12, 10};
int arr1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int arr2[] = {15,16,17,18,19,20,21,22,23,24,25,26};
int arr3[] = {27,28,29,30,31,32,33,34,35,36,37,38};
int arr4[] = {39,40,41,42,43,44,45,46,47,48,49};
int arr5[] = {50,51,52,53,54,55,56,57,58,59,60};
int arr6[] = {61,62,63,64,65,66,67,68,69,70,71,72,73};
int arr7[] = {74,75,76,77,78,79,80,81,82,83,84,85};
int arr8[] = {86,87,88,89,90,91,92,93,94,95,96,97};
int arr9[] = {98,99,100,101,102,103,104,105,106,107,108,109};
int arr10[] = {110,111,112,113,114,115,116,117,118,119};

int * arr[] = {arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9, arr10 };


uint8_t hue = 0;
CRGB colorActive = CRGB( 255, 90, 0);

//variables
int sensors[NUM_SENSORS] = {0};
int state = 0;
int queue[120];
int count = 0;
int currentLED = 0;
int locator = 0;
unsigned long resetTimer = 0;
unsigned long inputTimes[NUM_SENSORS] = {0};
unsigned long current = 0;
unsigned long colordelay = 0;
unsigned long next = 0;


void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  

}

int firstSensor(int sensors[]);
int checkDoubleTruck(int firstSensor);
int checkSecondInput(int currentSensor, int sensors[]);
void addToQueue(int sensor);
void runQueue();
void reset();

void loop() {
  // light effect
  
  if (count == 0 && state != 0) {
    if (current > colordelay) { 
    for(int i = 0; i < 119; i++) {
      if (rawleds[i] != CRGB(0x000000)) {
          rawleds[i] = CHSV(hue, 255, 255);
          FastLED.show();
      }
    }
    }
  }
  EVERY_N_MILLISECONDS(5) {
    hue++;
  }
  //pick color
 if (count == 0 && state == 0) {
    uint8_t x = random8(0, 255);
    uint8_t y = random8(0, 255);
    uint8_t z = random8(0, 255);
    if (x < 100) {
        x = 0;
    }
    if (y < 100) {
      y = 0;
    }
    if (z < 100) {
      z = 0;
    }
    CRGB newcolor(x,y,z);
    colorActive = newcolor;
  }
 

  
  //SENSOR LOOP
  current =  millis();
  for (int i = 2; i < NUM_SENSORS + 2; i++) {
    if (digitalRead(i) == LOW && sensors[i - 2] == False) {
      colordelay = current + 2000;
      resetTimer = current + 8000;
      // record the time of the input
      inputTimes[i] = millis();
  
      //first sensor
      if (firstSensor(sensors) == True) {
        state = checkDoubleTruck(i);   // needs work
 
      //second input (direction)
      } else if (state == 1 || state == 2) {

        state = checkSecondInput(i, sensors);
      }

      //add sensor to queue
      else {

        
        addToQueue(i);
        
      }
    sensors[i -2] = True;
    }
  }
  runQueue();

  if (current > resetTimer && state != 0) {
    reset();
  }
}
//checks if it is the first sensor
int firstSensor(int sensors[]) {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensors[i] == True) {
      return False;
    }
  }
  return True;
}
// blocking code only for the first sensor
int checkDoubleTruck(int  firstSensor) {
  int x = firstSensor - 2;
  sensors[x] = True;
  unsigned long current = millis();
  const unsigned long event = current + 200;
      
    for (int i = 2; current < event; i++) {
      current = millis();
      if (digitalRead(i) == LOW && i != firstSensor) {

        sensors[i-2] = True;
        if (i == (firstSensor + 2) || i == (firstSensor - 2)) {

          if (i > firstSensor) {
            sensors[x + 1] = True;
            //turn on x3 arrays
            fill_solid(ledarray[x], sizes[x], colorActive);
            fill_solid(ledarray[x + 1], sizes[x + 1], colorActive);
            fill_solid(ledarray[i - 2], sizes[i - 2], colorActive);
            FastLED.show();
          } else if (i < firstSensor) {
            sensors[x - 1] = True;

            fill_solid(ledarray[x], sizes[x], colorActive);
            fill_solid(ledarray[x - 1], sizes[x - 1], colorActive);
            fill_solid(ledarray[i - 2], sizes[i - 2] , colorActive);
            FastLED.show();
          }


          //state 2
          return 2;
      }
      // reset i
      if (i == 12) {
        i = 2;
      }
  }
    }
  fill_solid(ledarray[x], sizes[x], colorActive);
  FastLED.show();
  //state 1
  return 1;
}
int checkSecondInput(int currentSensor, int sensors[]) {

  for (int i = 0; i < NUM_SENSORS; i++) {
    
    if (sensors[i] == True) {
      if (currentSensor - 2 < i) {
        //skateboard is moving right to left
        state = 3;
        
        //skateboard is moving left to right
      } else if (currentSensor - 2 > i) {
       
        state = 4;
        
      }
    }
  
  }
  addToQueue(currentSensor);
  sensors[currentSensor - 2] = True;
  return state;
}

void addToQueue(int sensor) {
  
  int len = sizes[sensor - 2];

  if (state == 3) {
    for (int i = arr[sensor - 2][len - 1]; i >= arr[sensor - 2][0]; i--) {

      queue[locator] = i;
      locator++;
      count++;
      
    }
  } else if (state == 4) {
    
    for (int i = arr[sensor - 2][0]; i <= arr[sensor - 2][len - 1]; i++) {
      queue[locator] = i;
      locator++;
      count++;     
    }
  }
  return;
}


void runQueue() {
  
  if (count > 0) {

    if (currentLED == 0) {
          leds[queue[currentLED]] = colorActive;        
          FastLED.show();
          next = millis() + 15;
          currentLED++;
          count--;
    } else if (currentLED > 0) {
        if (current > next) {
          leds[queue[currentLED]] = colorActive;
          FastLED.show();
          next = millis() + 15;
          currentLED++;
          count--;
        }
    }

    

    //turn on a light then save a time
  }
  return 0;


}


void reset() {
    for (int i = 0; i < NUM_SENSORS; i++) {
      sensors[i] = 0;
    }
      state = 0;
      count = 0;
      currentLED = 0;
      locator = 0;
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      return;
}
