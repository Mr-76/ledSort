#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    30

CRGB leds[NUM_LEDS];

// Bubble Sort function with LED updates on every swap
void bubbleSort(int arr[], int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      // Swap if the element is greater than the next
      if (arr[j] > arr[j+1]) {
        // Swap values
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;

        // Update LEDs to reflect the swap
        for (int k = 0; k < n; k++) {
          // Set each LED to a combination of red and blue colors with varying intensity
          leds[k] = CRGB(255, 0, arr[k]);  // Full red, varying blue intensity
        }
        FastLED.show();
        delay(50);  // Wait for 100ms to visualize the change
      }
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // Set up a gradient from maximum blue to minimum blue (initial state)
  int values[NUM_LEDS]; // Array to hold the blue intensity values
  
  for (int i = 0; i < NUM_LEDS; i++) {
    // Map the LED index (i) to control the brightness of blue from 255 to 0
    values[i] = map(i, 0, NUM_LEDS - 1, 255, 0);  // Max blue to min blue

    // Set each LED to a combination of red and blue color with varying intensity (from max blue to min blue)
    leds[i] = CRGB(255, 0, values[i]);  // Full red, varying blue intensity
  }
  FastLED.show();
  delay(50);  // Wait for a moment to display the initial pattern
  
  // Perform the bubble sort on the blue intensity values
  bubbleSort(values, NUM_LEDS);
}

void loop() {
  // The sorting happens in setup, so loop is not used
}

