#include "public.h"

void setup() {
  vm_init();
  //test_fs();
}

void loop() {
  vm_run_command();
}


