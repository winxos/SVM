/*
  PROTOCOL finite machine
  MARK_START LEN CMD CHECKSUM
  WINXOS 2014-05-05
*/
#include "public.h"

#define RAW_INPUT true
#define ENABLE_CHECKSUM false

#define FRAME_START 0xE5
#define CHECK_SUM_OFFSET 0xD3

enum {NOT_READY, SUCCESS} RECEIVE_STATE;
enum {S_READY, S_LEN, S_DATA, S_VERIFY} STATE;

struct FRAME frame_buf;
u8 receive_state = S_READY;
bool frame_ready = false;

bool checksum(u8 n) //validate
{
  u8 sum = CHECK_SUM_OFFSET;
  for (u8 i = 0; i < frame_buf.len; i++)
  {
    sum ^= frame_buf.data[i];
  }
  return (n == sum);
}
u8 counter = 0;
//receive the frame
void receive_data(u8 data)
{
  if (frame_ready) return;
  if (RAW_INPUT)
  {
    if (data == '\n')
    {
      frame_buf.len = counter;
      frame_ready = true;
      counter = 0;
    }
    else
    {
      if (counter == 0)
      {
        memset(frame_buf.data, 0, BUF_MAX_LEN);
      }
      frame_buf.data[counter++] = data;
    }
  }
  else
  {
    switch (receive_state)
    {
      case S_READY:
        if (data == FRAME_START)
          receive_state = S_LEN;
        break;
      case S_LEN:
        frame_buf.len = data;
        counter = 0;
        receive_state = S_DATA;
        break;
      case S_DATA:
        frame_buf.data[counter++] = data;
        if (counter == frame_buf.len)
          receive_state = S_VERIFY;
        break;
      case S_VERIFY:
        if (ENABLE_CHECKSUM)
        {
          if (checksum(data) == true)
          {
            frame_ready = true;
          }
        }
        else
        {
          frame_ready = true;
        }
        receive_state = S_READY;
        break;
      default: break;
    }
  }
}
struct FRAME * get_frame()
{
  frame_ready = false;
  return &frame_buf;
}

