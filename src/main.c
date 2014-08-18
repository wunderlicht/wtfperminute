#include <pebble.h>
#include "wtfpm.h"
  
//forward declaration
void handle_init();
void handle_deinit();

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

void handle_init() {
  show_wtfpm();
}

void handle_deinit() {
  hide_wtfpm();
}