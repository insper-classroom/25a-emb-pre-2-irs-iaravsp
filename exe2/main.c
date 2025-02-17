#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED = 4;
const int BTN = 28;
volatile flag_pressed = 0;

void pin_init(void){
  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);
  
  gpio_init(BTN);
  gpio_set_dir(BTN, GPIO_IN);
  gpio_pull_up(BTN);
}

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4) { // fall edge
    flag_pressed = 1;
  } else if (events == 0x8) { // rise edge
  }
}

int main() {
  int is_on = 0;
  stdio_init_all();
  pin_init();

  gpio_set_irq_enabled_with_callback(BTN,GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,true, btn_callback);


  while (true) {
    if (flag_pressed){
      flag_pressed = 0;
      is_on = !is_on;
      gpio_put(LED, is_on);
    }
  }
}