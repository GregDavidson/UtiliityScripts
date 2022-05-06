#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define STR_SIZE 100
typedef char String[STR_SIZE];
typedef char *Strptr;
#define STR_EQ 0

typedef FILE *Stream;

#define TRUE 1
#define FALSE 0

Strptr FileName;		/* Current Output File, if any */

main()
{
  Stream in = stdin, out, get_file();

  for (;;)
    {
      while ( !feof(in) && (out = get_file(in)) == NULL )
	;
      if (feof(in))
	break;
      xfer(in, out);
      fclose(out);
    }
}



Stream get_file(in)
  Stream in;
/* Read and skip a line of text.  If it contains the name of an
 * included file, return the filename in name and return 1.
 * The input pattern of an included filename will look like:
 * {file -actual name-}
 *	or
 * {from -actual name-}
 * with the left brace beginning the line.
 */
{
  int c;
  Stream out = NULL;
  Strptr p, mode;
  int got_fname;
  String line;

  if (fgets(line, STR_SIZE, in) == NULL)
    return 0;			/* EOF */
  if ( line[strlen(line)-1] != '\n' )
    {
      while ( (c = getc(in)) != '\n' && c != EOF )
	;
      if (c == EOF)
	return 0;
    }
  if (strncmp(line, "{file ", 6) == STR_EQ)
    mode = "w";
  else if (strncmp(line, "{from ", 6) == STR_EQ)
    mode = "a";
  else
    return 0;			/* not a file header */
  for ( p = line + 6; isspace(*p) ; p++ )
    ;
  FileName = p;
  while ( isgraph(*p) && *p != '}' )
    p++;
  *p = '\0';
  out = fopen(FileName, mode);
  fprintf(stderr, "fopen(%s, %s) ", FileName, mode);
  if (out)
    fputs("succeeded\n", stderr);
  else
    fputs("failed!\n", stderr);
  return out;
}

xfer(in, out)
  Stream in, out;
/* Copy lines from in to a new file called name,
 * as long as they're indented by whitespace, or
 * the line is empty.  Strip off one indentation
 * character, but warn if its not a tab.
 */
{
  int c;

  assert(out);
#ifdef VIS_COPYRIGHT
  fputs(
  "Copyright (c) 1988 by Virtual Infinity Systems.  All rights reserved.\n\n",
	out);
#endif
  while ( (c = getc(in)) != EOF && !isgraph(c) )
      if (c == '\n')
	putc(c, out);
      else if (c == '\t' || c == ' ')
	{
	  if (c == ' ')
	    fprintf(stderr,
		    "Warning: blank indented line in file %s\n", FileName);
	  while ( (c = getc(in)) != EOF && c != '\n' )
	    putc(c, out);
	  putc('\n', out);
	}
  if (c != EOF)
    ungetc(c, in);
}


