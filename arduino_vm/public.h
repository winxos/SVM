#pragma once
#include <arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"
#define BAUD 250000
typedef uint8_t u8;

/* public.cpp     */
extern int serial_putc( char c, struct __file * );
extern int split(char dst[][80], char *str, const char *spl);

extern void vm_init();
extern void serialEvent();
extern void vm_run_command();
/* protocol.cpp   */
#define BUF_MAX_LEN 80

struct FRAME {
  u8 len;
  u8 data[BUF_MAX_LEN];
};
extern void receive_data(u8 data);
extern bool frame_ready;
extern struct FRAME * get_frame();

/* shell.cpp    */
extern void shell();

extern void dump();
extern void init_SML();
extern bool step_SML();
extern bool input_single_code(int code);

extern long total_instructions;
extern bool RUN_VM;
