#include "public.h"
enum INPUT_STATE {SHELL, INPUT_CODE};
INPUT_STATE input_state = SHELL;
u8 cmd_count = 0;
#define MAX_CMD_COUNT 15

static struct CMD {
  char *_name;
  char *_help;
  void (*execute)(char args[2][10]);
} CMDS[MAX_CMD_COUNT];
static void _help(char args[2][10])
{
  printf(get_flash_str(MSG_HELP_HEADER_FMT), cmd_count);
  for (int i = 0; i < cmd_count; i++)
  {
    printf(get_flash_str(MSG_HELP_ITMES_FMT), CMDS[i]._name, CMDS[i]._help);
  }
}
static void _input(char args[2][10])
{
  puts(get_flash_str(MSG_INPUT_HINT));
  RUN_VM = false;
  init_SML();
  puts("00 ? ");
  input_state = INPUT_CODE;
}
static void _dump(char args[2][10])
{
  dump();
}
static void _stop(char args[2][10])
{
  RUN_VM = false;
  puts(get_flash_str(MSG_VM_STOPPED));
}
static void _ls(char args[2][10])
{
  FILE_INFO tmp;
  puts(get_flash_str(MSG_LS_HEADER));
  int i, total_size = 0;
  for (i = 0; i < max_file_number; i++)
  {
    if (get_file_by_index(i, &tmp) == FILE_SUCCESS)
    {
      printf(get_flash_str(MSG_LS_ITEMS_FMT), tmp.name, tmp.size);
      total_size += tmp.size;
    }
    else
    {
      break;
    }
  }
  printf(get_flash_str(MSG_LS_SUMMARY_FMT), i, total_size);
}
static void _cat(char args[2][10])
{

}
static void _rm(char args[2][10])
{
  int ret = delete_file(args[0]);
  printf(get_flash_str(MSG_RM_RETURN_CODE_FMT), args[0], ret);
}
static void _ps(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _kill(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _pmode(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _dread(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _dwrite(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _aread(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
}
static void _awrite(char args[2][10])
{
  puts(get_flash_str(MSG_NOT_FINISHED));
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
    char dst[3][10] = {{0}, {0}, {0}};
    split(dst, (char *) buf, " ");
    int cmdi = cmd_index(dst[0]);
    if (cmdi >= 0)
    {
      CMDS[cmdi].execute((char [2][10])&dst[1]);
    }
    else
    {
      printf(get_flash_str(MSG_COMMAND_NOT_EXIST_FMT), buf);
    }
  }
  else if (input_state == INPUT_CODE)
  {
    if (atoi(fbuf->data) == -1)
    {
      puts("-1");
      RUN_VM = true;
      input_state = SHELL;
    }
    else
    {
      char tmp[7] = "0x";
      memcpy(&tmp[2], fbuf->data, 4);
      tmp[6] = 0;
      if (!input_single_code(strtoul(tmp, 0, 16)))
      {
        input_state = SHELL;
      }
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
  add_command("ls", _ls, LS_HELP);
  add_command("cat", _cat, CAT_HELP);
  add_command("rm", _rm, RM_HELP);
  add_command("ps", _ps, PS_HELP);
  add_command("kill", _rm, KILL_HELP);
  add_command("dump", _dump, DUMP_HELP);
  add_command("stop", _stop, STOP_HELP);
  add_command("input", _input, INPUT_HELP);
  add_command("pmode", _pmode, PMOD_HELP);
  add_command("dread", _dread, DREAD_HELP);
  add_command("dwrite", _dwrite, DWRITE_HELP);
  add_command("aread", _aread, AREAD_HELP);
  add_command("awrite", _awrite, AWRITE_HELP);
  add_command("help", _help, HELP_HELP);
}

