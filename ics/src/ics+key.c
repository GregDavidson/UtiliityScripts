/* Process a .ics file, putting {key ...} around any keywords
 * in an embedded C program (subfile ending in .c or .h)
 */

int CopyToken()
{
  char chunk[CHUNK_SIZE];
  String s = chunk;
  int c;

  c = getchar();
  if ( !isspace(c) )
    {
      ungetc(c, stdin);
      return 0;
    }
  if (c == '\n')
    {
      putchar('\n');
      return 1;
    }
  switch (c = getchar())
    {
      WHEN '\'':
      putchar(c);
      while ( (c = getchar()) != '\'' )
	{
	  putchar(c);
	  if (c == '\\')
	    {
	      putchar(c);
	      putchar(getchar());
	    }
	}
      WHEN '/':
      putchar('/');
      c = getchar();
      if (c != '*')
	ungetc(c, stdin);
      else
	{
	  while (c != 
	      
    }
}
