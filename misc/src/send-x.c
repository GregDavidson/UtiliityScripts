#include <stdio.h>

int Port;

main(argc, argv)
  int argc;
  char **argv;
{
  FILE *text;

  Port = open("/dev/ttyb", 2);

  ++argv;
  if (!argv)
    send(stdin);
  else
    while (argv)
      {
	text = fopen(argv++, "r");
	if (text)
	  send(text);
      }
}

send(f)
  FILE *f;
{
  int c;
  char in, out;
  while ( (in = c = getc(f)) != EOF )
    {
      write(Port, in, 1);
      read(Port, in, 1);
    }
}
