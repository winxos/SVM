#include "public.h"
enum INPUT_STATE {SHELL, INPUT_CODE};
INPUT_STATE input_state = SHELL;
void help(void)
{
  puts("ARDUINO VM HELP");
  puts("ls [list inner files]");
  puts("load xx[load and run inner file]");
  puts("code xx[run machine code xx]");
  puts("input [interactive mode]");
  puts("dump [show vm memory]");
}

void shell(void)
{
  struct FRAME *fbuf = get_frame();
  if (input_state == SHELL)
  {
    u8 *buf = fbuf->data;
    char dst[3][80] = {{0}, {0}, {0}};
    split(dst, (char *) buf, " ");
    puts(buf);
    if (0 == strcmp(dst[0], "ls") || 0 == strcmp(dst[0], "dir"))
    {

    }
    else if (0 == strcmp(dst[0], "help"))
    {
      help();
    }
    else if (0 == strcmp(dst[0], "load"))
    {

    }
    else if (0 == strcmp(dst[0], "code"))
    {

    }
    else if (0 == strcmp(dst[0], "input"))
    {
      puts("\nEnter -1 to end input.\n");
      init_SML();
      printf("00 ? ");
      input_state = INPUT_CODE;
    }
    else if (0 == strcmp(dst[0], "dump"))
    {
      dump();
    }
    else if (0 == strcmp(dst[0], "p")) //protocol
    {
    }
  }
  else if (input_state == INPUT_CODE)
  {
    if(!input_single_code(atol(fbuf->data)))
    {
      input_state = SHELL;
    }
  }
}
