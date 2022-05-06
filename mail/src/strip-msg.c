#include <stdio.h>

char *HeadersToSkip[] = {
  "received:",
  "resent-date:",
  "resent-message-id:",
  "message-id:"
  NULL
};

typedef enum {FALSE, TRUE} Boolean;

char Line[1024];
char LoweredLine[1024];
int Line_len;

Boolean getline()
{
  char *dst=LoweredLine, *src=Line;

  if ( gets(Line) == EOF )
    return FALSE;
  for (Line_len = 0; *dst = *src++; Line_len++)
    {
      if (isupper(*dst))
	*dst = tolower(*dst);
      dst++;
    }
}

Boolean at(char *str)
{
  int str_len = strlen(str);

  if (str_len > Line_len)
    return FALSE;
  return ! strncmp(str, LoweredLine, str_len);
}

int main()
{
  Boolean in_header=TRUE, in_fluff=FALSE;

  for ( getline() ; LineLen != EOF && LineLen > 0 ; )
    if ( bad_header() )
      do
	getline();
      while ( LineLen != EOF && LineLen > 0 && Line[0] != '\t' );
    else
      do {
	puts(Line);
	getline();
      } while ( LineLen != EOF && LineLen > 0 && Line[0] == '\t' );
  if ( LineLen == 0 )
    {
      putchar('\n');
      while ( (c = getchar()) != EOF )
      
}
