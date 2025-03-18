#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100


CRGB leds[NUM_LEDS];

// Bubble Sort function with LED updates on every swap
void bubbleSort(CRGB arr[], int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      // Swap if the element is greater than the next
      int total = arr[j].r + arr[j].g + arr[j].b;
      int next = arr[j+1].r + arr[j+1].g + arr[j+1].b;
      if (total > next) {
        // Swap values
        CRGB temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;

        FastLED.show();
        delay(50);  // Wait for 100ms to visualize the change
      }
    }
  }
}



void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50); 

    // Preencher os LEDs com um gradiente seguindo o espectro visível
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t hue = map(i, 0, NUM_LEDS - 1, 0, 170);  // De vermelho (0) a violeta (170)
        leds[i] = CHSV(hue, 255, 255); // Cor cheia, saturação máxima, brilho máximo
    }

    for (int i = 0 ; i < NUM_LEDS; i ++){
      int change = random(0,NUM_LEDS);
        CRGB temp = leds[i];
        leds[i] = leds[change];
        leds[change] = temp;
      
    }
    bubbleSort(leds,100);

    FastLED.show();
}


void loop() {
  delay(5000);
  setup();
  // The sorting happens in setup, so loop is not used
}

