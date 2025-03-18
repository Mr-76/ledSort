#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100

CRGB leds[NUM_LEDS];

void bubbleSort(CRGB arr[], int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      // Swap if the element is greater than the next
      int total = arr[j].r + arr[j].g + arr[j].b;
      int next = arr[j+1].r + arr[j+1].g + arr[j+1].b;
      if (total > next) {
        CRGB temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;

        FastLED.show();
        delay(50);
      }
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(40); 

  int values[NUM_LEDS]; 
  for (int i = 0; i < NUM_LEDS; i++) {
    int randomVerde = random(0, 255); 
    int randomAzul = random(0,255);
    int randomVermelho = random(0,255);
    leds[i] = CRGB(randomVermelho, randomVerde, randomAzul);  
  }
  FastLED.show();
  delay(50);
  
  bubbleSort(leds, NUM_LEDS);
}

void loop() {
  delay(5000);
  setup();
}

