#include <stdio.h>

#define MyCatPath /z/bin/MyCat

main()
{
  include(stdio);
}

include( fd )
{
  int c, l;
  char command[128], *s;

  while ( CopyLine( fd ) )
    ;
}

CopyLine( in )
  FILE *in;
{
  c = getc( fd );
  if ( c == EOF )
      return;
  switch( c )
    {
      case '<':
	  strcpy(command, MyCatName);
	  l = length(command);
	  s = &(command + l);
	  GetStr(s, 128 - l, '\n);
	  system(command);
	break;
      case '$':
	  GetStr(command, 128, '\n');
	  system(command)
	break;
    }
  
}
