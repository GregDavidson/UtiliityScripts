#include <stdio.h>

typedef char[256] String;

char *ptrTail(s)
    char *s;
{
  char *p, *o;

  o = s;
  for (p = s; *p ; p++)
      if (*p == '/')
	  o = p;
  return o;
}

getHead(dst, src)
    char *dst, *src;
{
  char *p;

  p = ptrTail(src);
  while ( p < src )
      *dst++ = *p++;
  *dst = '\0';
}

main (argc, argv)
  int argc;
  char **argv;
{
  char **av;
  int error;

  av = argv;
  while (*++av))
      if (fork())
	  {
	    wait(&error)
	    if (error)
		fprintf(stderr, "%s: error while removing %s\n", *argv, *av);
	  }
      else
	{
	  doit(*av);
	  exit();
	}
}

doit(s)
  char *s;
{
  String head, dir, name;
  char *tail;
  int version;

  if ( !access( s, F_OK ) )
    {
      fprintf(stderr, "%s: file %s not found\n", *argv, s);
      return;
    }
  if ( isDir( s ) )
    {
      fprintf(stderr, "%s: directory %s not removed\n", *argv, s);
      return;
    }
  if ( !isText( s ) )
    {
      unlink( s );
      return;
    }
  getHead( head, s );
  tail = ptrTail( s );
  if ( *head )
      strcpy(dir, head);
  else
      strcpy(dir, "/");
  if (!access( dir, W_OK ))
    {
      fprintf(stderr, "%s: directory %s not writable\n", *argv, dir);
      return;
    }
  strcat(dir, "/.save");
  if (!access( dir, F_OK ))
      if (mkdir(dir))
	{
	  perror(*argv);
	  fprintf(stderr, "%s: can't make save directory %s\n", *argv, d);
	  return;
	}
  version = 0;
  do{
      ++version;
      sprintf(name, "%s/#%s.%d", d, t, version);
    }
  while ( access( name, F_OK ) );
  runf("mv %s %s", f, name);
  fprintf(log, "%s\n", f);
}
