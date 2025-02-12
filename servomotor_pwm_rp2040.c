#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVOMOTOR_PIN 22
#define LED_PIN 12
#define TEMPO_ESPERA 5000
#define ATRASO_AJUSTE 10
static const float DIVISOR_CLOCK = 100.0f;
static const uint16_t WRAP = 25000;

int main()
{
    stdio_init_all();
    // Configuração do PWM para o servomotor
    gpio_set_function(SERVOMOTOR_PIN, GPIO_FUNC_PWM);
    uint slice_num_servomotor = pwm_gpio_to_slice_num(SERVOMOTOR_PIN);
    pwm_config config_servomotor = pwm_get_default_config();
    // Di = 100, Df = 0
    // Wrap = 25000
    // Frequência do pwm = 125MHz / (100 + 0/16) x 25000 + 1 = ~50Hz
    // Período do pwm = 1 / 50hz = 0.02s = 20ms = 20000µs
    pwm_config_set_clkdiv(&config_servomotor, DIVISOR_CLOCK);
    pwm_config_set_wrap(&config_servomotor, WRAP);
    pwm_init(slice_num_servomotor, &config_servomotor, true);

    // Configuração do PWM para o led
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num_led = pwm_gpio_to_slice_num(LED_PIN);
    pwm_config config_led = pwm_get_default_config();
    pwm_config_set_clkdiv(&config_led, DIVISOR_CLOCK);
    pwm_config_set_wrap(&config_led, WRAP);
    pwm_init(slice_num_led, &config_led, true);
    // Frequência do clock = 125MHz
    /*  Ciclos ativos para cada posição
        0° = 2400µs
        90° = 1470µs
        180° = 500µs
    */
    const uint16_t positions[] = {2400, 1470, 500};
    uint16_t last_position;
    bool sentido = true; // Sentido horário
    // Aplica cada posição por 5 segundos (requisitos 2,3,4)
    for (int i = 0; i < 3; i++)
    {
        last_position = positions[i];
        // 0.8 = 20000 / 25000 = 1 / 1.25
        pwm_set_gpio_level(SERVOMOTOR_PIN, last_position / 0.8);
        pwm_set_gpio_level(LED_PIN, last_position / 0.8);
        sleep_ms(TEMPO_ESPERA);
    }
    // Movimentação suave entre 0° e 180°
    uint16_t passos = 5; // Passo de 5µs
    while (true)
    {
        sentido = (last_position == positions[0] || last_position == positions[2]) ? !sentido : sentido;
        if (sentido)
        {
            // Vai para 180° 500 µs
            last_position -= passos;
        }
        else
        {
            // Volta para 0° 2400 µs
            last_position += passos;
        }
        pwm_set_gpio_level(SERVOMOTOR_PIN, last_position / 0.8);
        pwm_set_gpio_level(LED_PIN, last_position / 0.8);
        sleep_ms(ATRASO_AJUSTE);
    }
}