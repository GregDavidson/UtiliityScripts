/* Author: J. Greg Davidson
 * Date:
 * Copyright (c) 1994 Virtual Infinity Systems (VIS).
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided 
 * that the above copyright notice appear in all copies and that both that 
 * copyright notice and this permission notice appear in supporting 
 * documentation, and that the name of VIS not be used in advertising
 * or publicity pertaining to distribution of the software without specific, 
 * written prior permission. VIS makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

#include <stdio.h>
#include <assert.h>
#include <time.h>

typedef const char *StrPtr;

const StrPtr Month[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

const StrPtr Day[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

#define WHEN break; case
#define OR : case
#define DEFAULT break; default

void mydate(int hour, int minutes, StrPtr weekday,
	    int day, StrPtr month, int year)
{
  switch (hour) 
    {
    WHEN 0:
      printf("%d minutes past Midnight, %s, %d %s, %d\n", minutes, weekday, day, month, year);
    WHEN 1 OR 2 OR 3 OR 4 OR 5 OR 6 OR 7 OR 8 OR 9 OR 10 OR 11:
      printf("%d:%02d a.m., %s, %d %s, %d\n",
	     hour, minutes, weekday, day, month, year);
    WHEN 12:
      printf("%d minutes past Noon, %s, %d %s, %d\n", minutes, weekday, day, month, year);
    WHEN 13 OR 14 OR 15 OR 16 OR 17 OR 18 OR 19 OR 20 OR 21 OR 22 OR 23:
      printf("%d:%02d p.m., %s, %d %s, %d\n",
	     hour - 12, minutes, weekday, day, month, year);
    DEFAULT:
      assert(!"Bad hour");
    }
}

void print(char *word, struct tm *t)
{
#if 0
  while ( *word )
    if (*word != '%')
      putchar(*word++)
    else {
      int caps=0, width=0, pad=0, right=1, stop=1;
      do
	switch (*++word)
	  {
	  WHEN '^': caps++;
	  WHEN '0': pad='0';
	  WHEN ' ': pad=' ';
	  WHEN '\t': pad='\t';
	  WHEN '-': pad++;
	  WHEN '1' OR '2' OR '3' OR '4' OR '5' OR '6' OR '7' OR '8' OR '9':
	    width=strtol(word, &word, 10);
	  DEFAULT: stop=1;
	  }
      while (!stop);
      switch (*++word)
	{
	WHEN 'a': putstr(Day[t->tm_wday], width, pad, right, caps);
	WHEN 'b': putstr(Day[t->tm_mon],  width, pad, right, caps);
	WHEN 'd': putint(
      }
    }
#endif
}

int main(int argc, char **argv)
{
  time_t *now, the_time = time(&now);
  struct tm *t = localtime(&now);

  if (argc > 1)
    while (--argc) {
      print(*--argv, t);
      putchar(' ');
    }
  else
    mydate(t->tm_hour, t->tm_min, Day[t->tm_wday],
	   t->tm_mday, Month[t->tm_mon], t->tm_year+1900);
  return 0;
}
