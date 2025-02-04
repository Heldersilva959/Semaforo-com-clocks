#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Define os pinos dos LEDs
#define LED_PIN_GREEN 13 
#define LED_PIN_YELLOW 12
#define LED_PIN_RED 11

// Variável global para armazenar o estado atual do semáforo
int estado_semaforo = 0;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    printf("Mudança de semáforo\n");

    // Alterna entre os estados do semáforo
    switch (estado_semaforo) {
        case 0: // Vermelho
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_YELLOW, 0);
            gpio_put(LED_PIN_GREEN, 0);
            break;

        case 1: // Amarelo
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_YELLOW, 1);
            gpio_put(LED_PIN_GREEN, 0);
            break;

        case 2: // Verde
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_YELLOW, 0);
            gpio_put(LED_PIN_GREEN, 1);
            break;
    }

    // Avança para o próximo estado (0 → 1 → 2 → 0)
    estado_semaforo = (estado_semaforo + 1) % 3;

    return true; // Mantém o temporizador rodando
}

// Inicializa os pinos dos LEDs
void inicializacao() {
    stdio_init_all();
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
}

// Função principal
int main() {
    inicializacao(); // Inicializa os LEDs
    struct repeating_timer timer;

    // Configura o temporizador para mudar o semáforo a cada 3 segundos
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal para exibir mensagens a cada segundo
    while (true) {
        printf("Semáforo rodando...\n");
        sleep_ms(1000);
    }

    return 0;
}
