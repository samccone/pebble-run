#include <pebble.h>
#include "timer.h"

uint16_t current_time = 0;
static void (* on_tick_cb)(uint16_t);

void timer_tick(struct tm* tick_time, TimeUnits units_changed) {
  current_time++;
  on_tick_cb(current_time);
}

void start_timer(void (* on_tick)(uint16_t)) {
  on_tick_cb = on_tick;
  clear_timer();
  tick_timer_service_subscribe(SECOND_UNIT, &timer_tick);
}

void stop_timer() {
  tick_timer_service_unsubscribe();
}

void clear_timer() {
  current_time = 0;
}
