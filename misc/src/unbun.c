#include <stdio.h>

#define NAME(s) ((s)[0] == '!' && (s)[1] == ':' )
#define NAME_LEN 2

main()
{
  int c;
  FILE *out = stdout;
  char line[1024];
  
  while (gets(line))
      if NAME(line)
	{
	  if (out != stdout)
	      fclose(out);
	  if ((out = fopen(line+NAME_LEN, "w")) == NULL)
	    {
	      fprintf(stderr, "Can't open file %s\n", line+NAME_LEN);
	      out = stdout;
	      fputs(line, out);
	      putc('\n', out);
	    }
	}
      else
	{
	  fputs(line, out);
	  putc('\n', out);
	}
}

      
