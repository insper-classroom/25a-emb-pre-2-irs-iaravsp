#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
const int LED_VERM = 4;
const int LED_VERD = 6;
const int BTN_VERM = 28;
const int BTN_VERD = 26;

volatile int flag_verde = 0;
volatile int flag_verm = 0;

void init_pin(void){
  gpio_init(LED_VERM);
  gpio_set_dir(LED_VERM, GPIO_OUT);

  gpio_init(LED_VERD);
  gpio_set_dir(LED_VERD, GPIO_OUT);

  gpio_init(BTN_VERM);
  gpio_set_dir(BTN_VERM, GPIO_IN);
  gpio_pull_up(BTN_VERM);

  gpio_init(BTN_VERD);
  gpio_set_dir(BTN_VERD, GPIO_IN);
  gpio_pull_up(BTN_VERD);
}

void btn_callback(uint gpio, uint32_t events){
  if(events == 0x4 && gpio == BTN_VERM){//fall edge
      flag_verm = 1;
  }
  if(events == 0x8 && gpio == BTN_VERD){//rise edge
      flag_verde = 1;
  }
}
int main() {
  stdio_init_all();
  init_pin();
  int is_on_verm = 0;
  int is_on_verde = 0;

  
  // callback led vermelho setado c/ função
  gpio_set_irq_enabled_with_callback(BTN_VERM, GPIO_IRQ_EDGE_FALL, true,
    &btn_callback);

  // callback led verde q usa o msm callback já configurado
  gpio_set_irq_enabled(BTN_VERD, GPIO_IRQ_EDGE_RISE, true);


  while (true) {
    if (flag_verm){
      flag_verm = 0;
      is_on_verm = !is_on_verm;
      gpio_put(LED_VERM, is_on_verm);
    }
    if (flag_verde){
      flag_verde = 0;
      is_on_verde = !is_on_verde;
      gpio_put(LED_VERD, is_on_verde);
    }
  }
}
