#include <stdio.h>

#define LINE_LEN 1024

FILE *new_file(char *line)
{
  char dirname[LINE_LEN];

  if (*line == '/')
    {
      printf("line = 
    }
}

main()
{
  FILE *in = stdin, *out = stdout;
  int line=1, c;
  char linebuf[LINE_LEN];

  while ((c = getc(in)) != EOF)
    {
      if (c == '\n')
	{
	  c = getc(in);
	  if (c != '\n')
	    {
	      fprintf(stderr, "line %d, c == \'%c\'!\n", line, c);
	      putc('\n', out);
	    }
	  line++;
	}
      putc(c, out);
    }
  fprintf(stderr, "Processed %d lines\n", line);

  fclose(in);
  fclose(out);
  exit(0);
}
