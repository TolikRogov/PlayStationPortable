#include <Arduino.h>

hw_timer_t * timer = NULL;
volatile bool gameTick = false;

void IRAM_ATTR onTimer() {
  gameTick = true;
}