/* start-su-konsole.c --
 * 
 * The name says it all.
 * Be sure to install the binary suid root.
 * 
 * Draft - WIP - Bugs:
 *	Setting of PATH and PS1 don't work.
 *	Should lookup Greg by name.
 *	Should build env carefully.
 *	Want to design options.
 */

/* Author: J. Greg Davidson
 * Date:
 * Copyright (c) 2001p Virtual Infinity Systems (VIS).
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided 
 * that this C comment appear unchanged in all copies and that both the
 * copyright notice and this paragraph appear in supporting 
 * documentation, and that the name of VIS not be used in advertising
 * or publicity pertaining to distribution of the software without specific, 
 * written prior permission.  VIS makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

/* REVISION MACRO MIGHT BE PUT IN A STRING */

typedef const char *const String;

int main(int argc, char **argv) {
  String name = "/usr/bin/konsole";
  String command[] = {name, strrchr(name, '/')+1, "--ls", 0 };
  String  path = "/usr/local/sbin:/usr/sbin:/sbin:/usr/kerberos/sbin:/usr/kerberos/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/bin/X11:/usr/X11R6/bin:/root/bin";
  
  if (geteuid() != 0) {
	fprintf(stderr, "%s error: This program must be run suid root!\n", argv[0]);
	return 1;
  }

  if (getuid() != 500) {
	fprintf(stderr, "%s error: This program must be run by Greg!\n", argv[0]);
	return 1;
  }
  
  setenv("PATH", path, 1);
  setenv("PS1", "\\! # ", 1);

  if (fork() == 0) {			/* the child */
	String *av;
	
	execv(command[0], command+1);
	perror(command[0]);
	fprintf(stderr, "%s error: Can't exec", argv[0]);
	for (av = command; *av; av++)
	  fprintf(stderr, "%s", *av);
	fprintf(stderr, "!\n");
	return 1;
  }
  return 0;
}
