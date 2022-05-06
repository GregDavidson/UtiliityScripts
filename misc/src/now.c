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
typedef StrPtr StrArray[];

const StrArray Month = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

const StrArray Day = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const StrPtr Hour(int hour) 
{
  const StrArray Name = {
    "One", "Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Eleven"
  };
  assert(hour >= 0 && hour < 24);
  switch (hour) {
  case 0: return "Midnight";
  case 12: return "Noon";
  default: return Name[hour%12 - 1];
  }
}

const StrPtr Period(int hour) 
{
  assert(hour >= 0 && hour < 24);
  if (hour < 12) return "Morning";
  if (hour < 18) return "Afternoon";
  return "Evening";
}

#define WHEN break; case
#define OR : case
#define ELSE break; default

void mydate(int hour, int minutes, StrPtr weekday,
	    int day, StrPtr month, int year)
{
  printf("%d minutes past %s, %s %s, %d %s %d\n",
	 minutes, Hour(hour), weekday, Period(hour), day, month, year);
  #if 0
  switch (hour) 
    {
    WHEN 0:
      printf("%d minutes past Midnight, %s %s, %d %s %d\n",
	     minutes, weekday, "Morning", day, month, year);
    WHEN 1 OR 2 OR 3 OR 4 OR 5 OR 6 OR 7 OR 8 OR 9 OR 10 OR 11:
      printf("%d:%02d, %s %s, %d %s %d\n",
	     hour, minutes, weekday, "Morning", day, month, year);
    WHEN 12:
      printf("%d minutes past Noon, %s %s, %d %s %d\n",
	     minutes, weekday, "Afternoon", day, month, year);
    WHEN 13 OR 14 OR 15 OR 16 OR 17:
      printf("%d:%02d %s %s, %d %s %d\n",
	     hour - 12, minutes, weekday, "Afternoon", day, month, year);
    WHEN 18 OR 19 OR 20 OR 21 OR 22 OR 23:
      printf("%d:%02d %s %s, %d %s %d\n",
	     hour - 12, minutes, weekday, "Evening", day, month, year);
    ELSE:
      assert(!"Bad hour");
    }
  #endif
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
  time_t now, the_time = time(&now);
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
