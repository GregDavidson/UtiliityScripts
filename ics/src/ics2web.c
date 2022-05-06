/*
 * ics2web - replace tab indented text with text surround by .nf and .fi
 */


#include <stdio.h>
#include <string.h>

#define STR_SIZE 1000		/* better be enough, hey! */
char LineBuf[STR_SIZE];

#define TRUE 1
#define FALSE 0

int InCode = FALSE;

main()
{
  while ( gets(LineBuf) )
    {
      if ( *LineBuf == '\t' )
	{
	  if (!InCode)
	    {
	      InCode = TRUE;
	      puts(".lp");
	      puts(".nf");
	      puts(".sp");
	    }
	}
      else if ( *LineBuf != '\0' )
	{
	  if (InCode)
	    {
	      InCode = FALSE;
	      puts(".fi");
	    }
	}
      if ( InCode && *LineBuf == '\0' )
	  puts(".sp");
      else
	  puts(LineBuf);
    }
}
