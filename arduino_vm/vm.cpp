/*
  SIMPLE MACHINE LANGUAGE v5
  This version added timer
  winxos 2016-11-14
*/
#include "public.h"

#define MAX_MEM 100
int MEM[MAX_MEM] = {0};
long ADDER = 0; //ONLY MAX_MEN MEMORY, ONE REGISTER ADDER
u8 rega, regb, regc, regd;
#define MAX_STACK 30
int STACK[MAX_STACK] = {0};
bool RUN_VM = false;

int operand, pcode, pstack;
unsigned long total_instructions;
long slp_ct = 0;

enum
{
  _INPUT = 10, PRINT,
  LOAD = 20, STORE, SET,
  ADD = 30, SUB, MUL, DIV, MOD, INC, _DEC, NEG,
  JMP = 40, JMPN, JMPZ, HALT,
  AND = 50, OR, XOR,
  PUSH = 60, POP, SREGA, SREGB, SREGC, SREGD,
  PMOD = 70, DWP, DRP, AWP, ARP,
  SLP = 80,
};

#define COLS 10
#define TITLE_FORMAT "%6X"
#define DATA_FORMAT "%6d"
#define COL_HEADER_FORMAT "\n%3d"

void dump() //Pretty Show Memory For Debugging
{
  int i;
  printf("\nSystem started %ld ms ago, runned %ld Instructions\n", millis(), total_instructions);
  printf("ADDER:%4d, MEMORY:\n%3s", ADDER, "");
  for (i = 0; i < COLS; i++)
  {
    printf(TITLE_FORMAT, i);
  }
  for (i = 0; i < MAX_MEM; i++)
  {
    if (i % COLS == 0)
    {
      printf(COL_HEADER_FORMAT, i / COLS);
    }
    printf(DATA_FORMAT, MEM[i]);
  }
  puts("\n");
}


void init_SML()
{
  operand = 0, pcode = 0, pstack = 0, total_instructions = 0;
  memset(MEM, 0, sizeof(int) * MAX_MEM);
}
bool START_CLOCK = false;
bool step_SML() //
{
  total_instructions++;
  u8 *op = (u8*)&MEM[pcode];    //xxbb
  operand = *(op + 1);
  switch (*op)
  {
    case JMP: pcode = operand - 1;
      break;
    case LOAD: ADDER = MEM[operand];
      break;
    case STORE: MEM[operand] = ADDER;
      break;
    case SET: ADDER = operand;
      break;
    case JMPN: ADDER < 0 ? pcode = operand - 1 : 0;
      break;
    case JMPZ: ADDER == 0 ? pcode = operand - 1 : 0;
      break;
    case ADD: ADDER += MEM[operand];
      break;
    case SUB: ADDER -= MEM[operand];
      break;
    case MUL: ADDER *= MEM[operand];
      break;
    case DIV: ADDER /= MEM[operand];
      break;
    case MOD: ADDER %= MEM[operand];
      break;
    case SREGA: rega = ADDER;
      break;
    case SREGB: regb = ADDER;
      break;
    case SREGC: regc = ADDER;
      break;
    case SREGD: regd = ADDER;
      break;
    case PMOD:
      pinMode(operand, ADDER);
      break;
    case DWP:
      digitalWrite(operand, ADDER);
      break;
    case DRP:
      ADDER = digitalRead(operand);
      break;
    case AWP:
      analogWrite(operand, ADDER);
      break;
    case ARP:
      ADDER = analogRead(operand);
      break;
    case SLP://sleep
      if (!START_CLOCK)
      {
        START_CLOCK = true;
        slp_ct = millis();
        total_instructions--; //not finished , so can't caculate the count.
        return true;//
      }
      else
      {
        if (millis() - slp_ct < operand * 10)
        {
          total_instructions--; //not finished , so can't caculate the count.
          return true;
        }
        else //sleep finished
        {
          START_CLOCK = false;
        }
      }
      break;
    case INC: MEM[operand]++;
      break;
    case _DEC: MEM[operand]--;
      break;
    case NEG: MEM[operand] = -MEM[operand];
      break;
    case AND: ADDER = ADDER & MEM[operand];
      break;
    case OR: ADDER = ADDER | MEM[operand];
      break;
    case XOR: ADDER = ADDER ^ MEM[operand];
      break;
    case PUSH: pstack < MAX_STACK ? STACK[pstack++] = ADDER : puts("[warning] STACK OVERFLOW.");
      break;
    case POP: pstack > 0 ? ADDER = STACK[--pstack] : puts("[warning] STACK EMPTY.");
      break;
    case HALT: return false;
      break;
    case _INPUT:
      break;
    case PRINT: printf("%d ", MEM[operand]);
      break;
    default: break;
  }
  if (++pcode >= MAX_MEM)
    return false;
  return true;
}

int li = 0;
bool input_single_code(int code)
{
  if (code == -1)
  {
    puts("-1");
    li = 0;
    RUN_VM = true;
    return false;
  }
  MEM[li++] = (code / 100) | (code % 100 << 8);
  printf("%d\n%02d ? ", code, li);
  return true;
}
void help_vm()
{
  printf("THIS MACHINE HAVE %d(int)MEMORY, %d(int)STACK\n", MAX_MEM, MAX_STACK);
  puts("INSTRUCTION IS 4 DECIMAL DIGITS, FORMAT: AABB");
  puts("AA IS OPERATOR, BB IS OPERAND");
  puts("ONLY HAVE ONE REGISTER\n");
  puts("INSTRUCTIONS:");
  puts("\tINPUT:10\tPRINT:11\tLOAD:20\tSTORE:21\tSET:22");
  puts("\tADD:30\tSUB:31\tMUL:32\tDIV:33\tMOD:34\tINC:35\tDEC:36\tNEG:37");
  puts("\tJMP:40\tJMPN:41\tJMPZ:42");
  puts("\tAND:50\tOR:51\tXOR:52");
  puts("\tPUSH:60\tPOP:61");
  puts("\tHALT:-1\n");
  puts("THIS SHELL SUPPORTED COMMAND:");
  puts("ls\t\t\t[list SML source codes]");
  puts("help | ? \t\t[help]");
  puts("load name.sml\t\t[load and run source code]");
  puts("input\t\t\t[open code input mode]");
  puts("exit\t\t\t[exit program]");
  puts("dump\t\t\t[show memories]\n");
}

