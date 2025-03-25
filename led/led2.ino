#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100
#define NUM_CORES   256  // Ajuste para variação maior de cores

CRGB leds[NUM_LEDS];
CRGB cores[NUM_CORES];

// Gerar um espectro de cores suave
void gerar_cores() {
  for (int i = 0; i < NUM_CORES; i++) {
    cores[i] = CHSV(i, 255, 255);  // Hue variando de 0 a 255, máxima saturação e brilho
  }
}

// Função modificada para ordenar com pesos diferentes para RGB
void bubbleSort(CRGB arr[], int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      // Aplicando pesos diferenciados para cada canal
      int total = arr[j].r * 0.3 + arr[j].g * 0.59 + arr[j].b * 0.11;   // Ponderação perceptual
      int next = arr[j+1].r * 0.3 + arr[j+1].g * 0.59 + arr[j+1].b * 0.11;

      if (total > next) {
        // Troca
        CRGB temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;

        FastLED.show();
        delay(10);  // Reduzi o delay para suavizar o efeito
      }
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

  gerar_cores();  // Criar a paleta de cores

  // Preencher LEDs com cores do espectro
  for (int i = 0; i < NUM_LEDS; i++) {
    int valorAleatorio = random(NUM_CORES);
    leds[i] = cores[valorAleatorio];
  }

  FastLED.show();
  bubbleSort(leds, NUM_LEDS);  // Ordenar visualmente
}

void loop() {
  delay(5000);
  setup();  // Reinicia para novo efeito
}
