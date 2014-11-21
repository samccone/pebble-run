#include <pebble.h>
#include "random_run.h"

int main(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "RANDOM RUN INIT");
  init();
  app_event_loop();
  deinit();
}
