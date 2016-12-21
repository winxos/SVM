#include "public.h"
char STR_MEM_BUF[80]{0};
char *get_flash_str(char *str)
{
  strcpy_P(STR_MEM_BUF, str);
  return STR_MEM_BUF;
}
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}

int split(char dst[][10], char *str, const char *spl)//for single line chars split to words
{
    int n = 0;
    char *result = NULL;
    result = strtok(str, spl);
    while (result != NULL)
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }
    return n;
}
