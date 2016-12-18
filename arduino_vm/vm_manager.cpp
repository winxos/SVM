#include "public.h"
void vm_init()
{
  fdevopen( &serial_putc, 0 );
  Serial.begin(BAUD);
  printf("AISTLAB VM v%s\n", VERSION);
  printf("BAUD:%ld\n", BAUD);
}
void serialEvent()
{
  while (Serial.available()) {
    receive_data(Serial.read());
  }
}
unsigned long st;
void vm_run_command()
{
  if (frame_ready)
  {
    shell();
  }
  if (RUN_VM)
  {
    if (total_instructions == 0)
    {
      st = millis();
    }
    if (step_SML())
    {
      total_instructions++;
    }
    else
    {
      RUN_VM = false;
      printf("\nTotal run %ld instructions. used %ld ms.\n", total_instructions, millis() - st);
      total_instructions = 0;
      dump();
    }
  }
}

