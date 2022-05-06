#include <stdio.h>

int Chapter;
#define Signal '!'

int Col, Row;

int Level[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

main(argc, argv)
  int argc;
  char *argv[];
{
  int c, level;

  Chapter = StrToInt( argv[1] );

  Col = 0;
  while ( (c = getchar()) != EOF )
    {
      if (c == '\n')
	{
	  Col = 0;
	  Row++;
	}
      else
	Col++;

      if (Col == 1 && c == Signal)
	{
	  level = GetInt();
	  PutLevel(level);
	}
      else
	  putchar(c);
    }
}

PutLevel(l)
  int l;
{
  int i;

  l = l - 2;

  Level[l]++;
  for (i=(l+1);i<10;i++)
    Level[i] = 0;
  
  PutInt(Chapter);
  for (i = 0; i<= l; i++)
    {
      putchar('.');
      PutInt(Level[i]);
    }
}

int StrToInt( s )
  char *s;
{
  int i;
  
  i = 0;
  while ( *s >= '0' && *s <= '9' )
    {
      i = i * 10 + *s - '0';
      s++;
    }
  return i;
}

int GetInt()
{
  int c;
  int i;

  i = 0;
  while ( (c = getchar()) >= '0' && c <= '9' )
      i = i * 10 + c - '0';

  return i;
}

PutInt(i)
  int i;
{
  if (i > 0)
    {
      PutInt(i / 10);
      PutDigit(i % 10);
    }
}

PutDigit(i)
  int i;
{
  putchar( i + '0' );
}
