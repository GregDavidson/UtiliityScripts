#include <stdio.h>


main(ac, ap)
  int ac;
  char **ap;
{
  FILE *in;
  char *name;
  int c, d, i;

  setbuf(stdout, NULL);
  setbuf(stdin,  NULL);

  if (ac == 1)
      name = "send";
  else if (ac == 2)
      name = ap[1];
  else
    {
      fprintf(stderr,
	      "sendit error: Expected 0 or 1 args, got %d\n",
	      ac-1);
      fflush(stderr);
      exit(1);
    }

  in = fopen(name,"r");

  if (in == NULL)
    {
      fprintf(stderr, "sendit: Error opening %s\n", name);
      fflush(stderr);
      exit(1);
    }
  do
    {
      for (i=0; (c = getc(in)) != '\n' && c != EOF; i++)
	{
	  putchar(c);
	  if (c == ' ')
	      usleep((unsigned)150000L);
	}
      putchar('\r');
      fflush(stdout);
      while (--i && (d = getchar()) != '\n' && d != '\r')
	  ;
    }
  while (c != EOF);
}
