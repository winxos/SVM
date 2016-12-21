#pragma once
#include <arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define VERSION "0.2"
#define BAUD 250000
typedef unsigned char u8;
typedef unsigned short u16;

/* public.cpp     */
extern int serial_putc( char c, struct __file * );
extern int split(char dst[][10], char *str, const char *spl);

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

/* vm.cpp       */
extern void dump();
extern void init_SML();
extern bool step_SML();
extern bool input_single_code(int code);
extern void init_shell();
extern unsigned long total_instructions;
extern bool RUN_VM;
extern void run_code(u16 *fbuf, u8 sz);
/* fs.cpp       */
enum RETURN_CODE {
  FILE_SUCCESS, FILE_NOT_EXIST = -1, FILE_ALREADY_EXIST = -2, FILE_REACH_MAX = -3, DISK_NOT_ENOUGH = -4, DISK_FULL = -5,
};
enum FILE_STATE {
  NORMAL = 0x01, READ_ONLY = 0x02, HIDE = 0x04, OPENING = 0x08, DELETED = 0x10
};
#define MAX_NAME_LEN 8
struct FILE_INFO {
  char name[MAX_NAME_LEN];
  u16 start_address;
  u16 size;
  u8 state; //normal, read only, hide, opening delete?
  u8 xor_sum; //
};
extern int init_file_system();
extern int get_file(char name[],FILE_INFO *fout);
extern int read_file(FILE_INFO FI, u8 buf[]);
extern int write_file(char name[], u8 buf[], u8 len);
extern int delete_file(char name[]);
extern void test_fs();
extern int get_file_by_index(u8 index, FILE_INFO *out);
extern u8 max_file_number;
