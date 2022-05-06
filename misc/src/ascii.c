#include <stdio.h>
#include <assert.h>
#include <ctype.h>

typedef struct put_int_format
{
  int base;
  int sign;
  int pad;
}
  *PutIntFormat;

char Digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

void put_pos_int(int i, int width, PutIntFormat format)
{
  if (width || i > 0)
      if (i > 0)
	{
	  put_pos_int(i / format->base, width - 1, format);
	  putchar(Digits[i % format->base]);
	}
      else if (i < 0)
	{
	  put_pos_int(i, width - 1, format);
	  putchar(format->pad);
	}
      else if (format->sign)
	{
	  put_pos_int(-1, width - 1, format);
	  putchar(format->sign);
	}
      else
	  put_pos_int(-1, width, format);
}

void put_int(int i, int width, int base, int pad)
{
  struct put_int_format format;

  format.base = base;
  format.pad = pad;
  
  if (i > 0)
    {
      format.sign = pad;
      put_pos_int(i, width, &format);
    }
  else if (i < 0)
    {
      format.sign = '-';
      put_pos_int(-i, width, &format);
    }
  else
    {
      format.sign = '0';
      put_pos_int(i, width, &format);
    }
}

void print_ascii(void)
{
  int c;

  for (c = 0; c < 128; c++)
      {
	put_int(c, 3, 10, ' ');
	put_int(c, 9, 2, ' ');
	if (isgraph(c))
	  {
	    putchar(' ');
	    putchar(' ');
	    putchar(c);
	  }
	putchar('\n');
      }
}

main(void)
{
  print_ascii();
}

