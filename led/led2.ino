#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100
#define NUM_CORES   (255*3)  // Corrigido para não ser confundido com número de cores

CRGB leds[NUM_LEDS];        // Correção: ponto e vírgula adicionado
CRGB cores[NUM_CORES];      // Correção: ponto e vírgula adicionado

void gerar_cores() {
  int decr_idx = 0;
  int incr_idx = 1;
  CRGB cor = CRGB(255, 0, 0);
  cores[0] = cor;  // Atribuindo a primeira cor

  for (int i = 1; i < NUM_CORES; i++) {  // Corrigido: iniciando em i = 1
    if (cor[incr_idx] == 255) {
      decr_idx = (decr_idx + 1) % 3;
      incr_idx = (incr_idx + 1) % 3;
    }
    cor[decr_idx] -= 1;
    cor[incr_idx] += 1;
    cores[i] = cor;  // Atribuindo a cor gerada ao índice correspondente
  }
}

void bubbleSort(CRGB arr[], int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      // Calculando a "intensidade" total para comparar
      int total = arr[j].r + arr[j].g + arr[j].b;
      int next = arr[j+1].r + arr[j+1].g + arr[j+1].b;
      if (total > next) {
        // Troca das cores
        CRGB temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;

        FastLED.show();
        delay(50);  // Pequena pausa para efeito visual
      }
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  gerar_cores();  // Gerar a paleta de cores

  // Preencher os LEDs com cores aleatórias do espectro gerado
  for (int i = 0; i < NUM_LEDS; i++) {
    int valorAleatorio = random(NUM_CORES);  // Corrigido: ajuste para NUM_CORES
    leds[i] = cores[valorAleatorio];
  }

  FastLED.show();
  bubbleSort(leds, NUM_LEDS);  // Ordenar os LEDs
}

void loop() {
  delay(5000);
  setup();  // Reexecutar setup após 5 segundos (apenas para fins de teste visual)
}
