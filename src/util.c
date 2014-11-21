#include <pebble.h>
#include "util.h"

void format_time(uint16_t timer_time, bool showHours, char* str, int str_len) {
  int hours = timer_time / 3600;
  int minutes = (showHours ? (timer_time % 3600) : timer_time) / 60;
  int seconds = (showHours ? (timer_time % 3600) : timer_time) % 60;
  if (showHours) {
    snprintf(str, str_len, "%01d:%02d:%02d", hours, minutes, seconds);
  }
  else {
    snprintf(str, str_len, "%02d:%02d", minutes, seconds);
  }
}
