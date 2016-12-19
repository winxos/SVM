#include "public.h"
enum INPUT_STATE {SHELL, INPUT_CODE};
INPUT_STATE input_state = SHELL;
u8 cmd_count = 0;
#define MAX_CMD_COUNT 15
static struct CMD {
  char *_name;
  char *_help;
  void (*execute)();
} CMDS[MAX_CMD_COUNT];
static void _help()
{
  printf("COMMANDS COUNT (%d)\n", cmd_count);
  for (int i = 0; i < cmd_count; i++)
  {
    printf("%s\t\t\t%s\n", CMDS[i]._name, CMDS[i]._help);
  }
}
static void _input()
{
  puts("\nEnter -1 to end input.\n");
  init_SML();
  printf("00 ? ");
  input_state = INPUT_CODE;
}
static void _dump()
{
  dump();
}
static void _stop()
{
  RUN_VM = false;
  puts("VM STOPED");
}
static void _ls()
{
  FILE_INFO tmp;
  printf("%8s\t\t%s\n","NAME","SIZE");
  int i, total_size = 0;
  for (i = 0; i < max_file_number; i++)
  {
    if (get_file_by_index(i, &tmp) == FILE_SUCCESS)
    {
      printf("%8s\t\t%d\n", tmp.name, tmp.size);
      total_size += tmp.size;
    }
    else
    {
      break;
    }
  }
  printf("\t\t%d FILES\t\t%d BYTES\n", i, total_size);
}
static void _rm()
{
  puts("NOT FINISHED");
}
static void _ps()
{
  puts("NOT FINISHED");
}
static void _kill()
{
  puts("NOT FINISHED");
}
static void _pmode()
{
  puts("NOT FINISHED");
}
static void _dread()
{
  puts("NOT FINISHED");
}
static void _dwrite()
{
  puts("NOT FINISHED");
}
static void _aread()
{
  puts("NOT FINISHED");
}
static void _awrite()
{
  puts("NOT FINISHED");
}
static int cmd_index(char *s)
{
  for (int i = 0; i < cmd_count; i++)
  {
    if (strcmp(CMDS[i]._name, s) == 0)
    {
      return i;
    }
  }
  return -1;
}
void shell(void)
{
  struct FRAME *fbuf = get_frame();
  if (input_state == SHELL)
  {
    char *buf = fbuf->data;
    //char dst[3][80] = {{0}, {0}, {0}};
    //split(dst, (char *) buf, " ");
    int cmdi = cmd_index(buf);
    if (cmdi >= 0)
    {
      CMDS[cmdi].execute();
    }
    else
    {
      printf("'%s' NOT EXIST, TYPE help FOR SUPPORTED COMMANDS\n", buf);
    }
  }
  else if (input_state == INPUT_CODE)
  {
    if (!input_single_code(atol(fbuf->data)))
    {
      input_state = SHELL;
    }
  }
}
static void add_command(char *cname, void(*f)(), char * chelp)
{
  assert(chelp != NULL);
  CMDS[cmd_count]._name = cname;
  CMDS[cmd_count].execute = f;
  CMDS[cmd_count]._help = chelp;
  cmd_count++;
}
void init_shell()
{
  add_command("ls", _ls, "LIST FILES");
  add_command("rm", _rm, "REMOVE FILES");
  add_command("ps", _ps, "PROCESS STATUS");
  add_command("kill", _rm, "KILL PROCESS");
  add_command("dump", _dump, "SHOW VM MEMORIES");
  add_command("stop", _stop, "STOP THE VM RIGHT NOW");
  add_command("input", _input, "SWITCH TO INTERACTIVE MODE");
  add_command("pmode", _pmode, "SET PIN MODE, 0 INPUT,1 OUTPUT,2 PULLUP");
  add_command("dread", _dread, "DIGITAL READ");
  add_command("dwrite", _dwrite, "DIGITAL WRITE");
  add_command("aread", _aread, "ANALOG READ");
  add_command("awrite", _awrite, "ANALOG WRITE");
  add_command("help", _help, "HELP");
}

