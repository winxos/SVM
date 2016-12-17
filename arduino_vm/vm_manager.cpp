#include "public.h"
void vm_init()
{
  fdevopen( &serial_putc, 0 );
  Serial.begin(BAUD);
  printf("AISTLAB VM v%s\n",VERSION);
  printf("BAUD:%ld\n",BAUD);
}
void serialEvent()
{
  while (Serial.available()) {
    receive_data(Serial.read());
  }
}
void vm_run_command()
{
  if (frame_ready)
  {
    shell();
  }
}

