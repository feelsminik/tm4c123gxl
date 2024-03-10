#include <stdbool.h>
#include <stdint.h>

#include "include/tm4c123gh6pm.h"

void wait(int);
void activate_port_f(void);
void turn_led_on(unsigned int);
void turn_led_off(void);
void show_led_gradient(void);

int main(void) {
  activate_port_f();

  show_led_gradient();

  return 0;
}

void show_led_gradient(void) {
  volatile unsigned long color = 0x00;
  while (1) {
    if (color >= 0x0EU) {
      color = 0x02U;
    } else {
      color += 0x02U;
    }
    GPIO_PORTF_DATA_R = color;
    wait(1000000);
  }
}

void activate_port_f(void) {
  SYSCTL_RCGCGPIO_R = 0x20;
  GPIO_PORTF_DIR_R = 0x0EU;
  GPIO_PORTF_DEN_R = 0x0EU;
}

void turn_led_on(unsigned int pin_value) {
  GPIO_PORTF_DATA_R = pin_value;
  wait(1000000);
}

void turn_led_off(void) {
  GPIO_PORTF_DATA_R = 0x00;
  wait(1000000);
}

void wait(int n) {
  volatile int counter = 0;
  while (counter < n) {
    counter++;
  }
}
