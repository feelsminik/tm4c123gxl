#include <stdbool.h>
#include <stdint.h>

#include "../include/tm4c123gh6pm.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_OFF (0U)

void wait(int);
void activate_port_f(void);
void turn_led_on(unsigned int);
void turn_led_off(void);
void show_led_gradient(void);

int main(void) {
  activate_port_f();

  /* while (1) { */
  /*   turn_led_on(LED_BLUE); */
  /*   turn_led_off(); */
  /* } */
  show_led_gradient();

  return 0;
}

void show_led_gradient(void) {
  volatile unsigned long color = LED_OFF;
  while (1) {
    if (color >= (LED_RED | LED_BLUE | LED_GREEN)) {
      color = LED_RED;
    } else {
      color = color + LED_RED;
    }
    GPIO_PORTF_DATA_R = color;
    wait(2000000);
  }
}

void activate_port_f(void) {
  SYSCTL_RCGCGPIO_R |= (1U << 5);
  GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
}

void turn_led_on(unsigned int pin_value) {
  GPIO_PORTF_DATA_R |= pin_value;
  wait(1000000);
}

void turn_led_off(void) {
  GPIO_PORTF_DATA_R = LED_OFF;
  wait(1000000);
}

void wait(int n) {
  volatile int counter = 0;
  while (counter < n) {
    counter++;
  }
}
