#include "public.h"
void startup_code()
{
  FILE_INFO f;
  if (FILE_SUCCESS == get_file_by_index(0, &f))
  {
    u8 *fbuf = malloc(f.size);
    read_file(f, fbuf);
    printf("default running code '%s' size:%d\n", f.name, f.size);
    run_code((u16*)fbuf, f.size / 2);
  }
}
void vm_init()
{
  fdevopen( &serial_putc, 0 );
  Serial.begin(BAUD);
  printf("AISTLAB VM v%s\n", VERSION);
  printf("BAUD:%ld\n", BAUD);
  init_shell();
  init_file_system();
  int buf[13] = {0x2201, 0x6200, 0x700d, 0x2200, 0x6200, 0x710d, 0x8050, 0x2201, 0x6200, 0x710d, 0x8050, 0x4003, 0x4300};
  int c = write_file("blink", (u8*)buf, 26);
  if (c == FILE_SUCCESS)
  {
    puts("default write blink code\n");
  }
  startup_code();
}
void serialEvent()
{
  while (Serial.available()) {
    receive_data(Serial.read());
  }
}
unsigned long st = 0;
void vm_run_command()
{
  if (frame_ready)
  {
    shell();
  }
  if (RUN_VM)
  {
    if (st == 0)
    {
      st = millis();
    }
    if (!step_SML())
    {
      RUN_VM = false;
      printf("\nTotal run %ld instructions. used %ld ms.\n", total_instructions, millis() - st);
      st = 0;
      dump();
    }
  }
}

