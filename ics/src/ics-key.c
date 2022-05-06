/*
 * ics-key - remove {key ...} annotations from C subfiles.
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define STR_SIZE 100
typedef char StrBuf[STR_SIZE];
typedef char *String;
#define STR_EQ 0

typedef FILE *Stream;

#define TRUE 1
#define FALSE 0

String FileName;		/* Current Output File, if any */

main()
{
  Stream in = stdin, out = stdout;
  int get_file();

  while (!feof(in))
    {
      while ( !feof(in) && !get_file(in) )
	;
      if (!feof(in))
	xfer(in, out);
    }
}

int match( Stream in, String pattern )
/* Read and store characters from in as long as they match pattern.
 * Return the number of characters that matched.
 * Push back the one that didn't, or stop on the NUL, w.e.c.1st.
 */
{
  String p = pattern;
  int c;

  while ( (c = getc(in)) == *p )
      p++;
  if (*p && c != EOF)
    ungetc(c, in);
  return p-pattern;
}

int get_file( Stream in )
/* Copy a line of text.  Return 1 iff it starts a C program.
 * The input pattern of an included filename will look like:
 * {file -actual name-.[ch]}
 *	or
 * {from -actual name-.[ch]}
 * with the left brace beginning the line.
 */
{
  int c;
  String p, mode;
  int got_fname;
  StrBuf line;

  if (fgets(line, STR_SIZE, in) == NULL)
    return 0;			/* EOF */
  fputs(line, out);
  if ( line[strlen(line)-1] != '\n' )
    {
      while ( (c = getc(in)) != '\n' && c != EOF )
	putc(c, out);
      if (c == EOF)
	return 0;
    }
  putc('\n', out);
  if (strncmp(line, "{file ", 6) != STR_EQ)
    return 0;
  if (strncmp(line, "{from ", 6) != STR_EQ)
    return 0;
  for ( p = line + 6; isspace(*p) ; p++ )
    ;
  FileName = p;
  while ( isgraph(*p) && *p != '}' )
    p++;
  *p = '\0';
  flen = strlen(FileName);
  if ( strcmp(FileName+flen-2, ".c") == STR_EQ ||
       strcmp(FileName+flen-2, ".h") == STR_EQ )
    {
      fprintf(stderr, "C file %s\n", FileName);
      return 1;
    }
  return 0;
}

xfer(in, out)
  Stream in, out;
/* Copy lines from in to a new file called name,
 * as long as they're indented by whitespace, or
 * the line is empty.  Strip off keyword annotation.
 */
{
  int c;

  assert(in);
  assert(out);

  c = getc(in);
  if ( c == '\n' )
    {
      putchar('\n');
      break;
    }
  
  
  
  if ( c == '{' )
    l = match(in, "key ");
  
    for ( s = buf, i = 0; 
  
  if ( c == 
  while ( (c = getc(in)) != '\n' && (c != EOF && !isgraph(c) )
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


