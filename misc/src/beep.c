/*
Date: 10-Jan-86 15:28:34-PST
From: Mark Gerolimatos <gerolima@FORD-WDL1.arpa>
UUCP: {sun,fortune}!wdl1!gerolima
Subject: how to beep a sun

So You want to beep a Sun? Well, I got this from Sun, and it works. 
However, I'd like to know WHY it works!
	*	*	*	*	*	*	*
One very basic reason that there are no beeps in suntools: How could
you tell which window is doing the beeping? Suntools catches all ^Gs
and turns them into a flash on the correct window.

If you really MUST beep, and have a beepable workstation (50, 120,
etc...) an application program can make it beep.  (Suntools itself will
still flash, e.g., "echo '^G'" to a window will make it flash.) Compile
and run the following program to hear the beep.

This is unsupported, of course!

This program lets you to ring the bell. Along with this program you
need to create a device in /dev with the same major # as ttya & ttyb,
but with an unused minor number, e.g., 

	/etc/mknod bell c 12 2	(or other appropriate major,minor #s)

crw-rw-rw-  1 root      12,   0 Mar 23 13:16 /dev/ttya
crw-rw-rw-  1 root      12,   1 Mar  6 10:51 /dev/ttyb
crw-rw-rw-  1 root      12,   2 Mar  6 10:51 /dev/bell

*/

#include <sys/time.h>

#define	RING_ON		0x02	/* Control-B */
#define RING_OFF	0x03	/* Control-C */
#define NULL		0

main()
{
	int	bell;
	char	outbuf[1];
	static  struct  timeval  ring_time  =  {0, 125000};

	if ( (bell = open("/dev/bell",2)) < 0 )
		{
		perror("ring:failed opening /dev/bell");
		exit(1);
		}

	outbuf[0] = RING_ON;
	if ( write(bell,outbuf,1) < 0 )  /*turn bell on*/
		{
		perror("ring:failed writing RING_ON");
		exit(1);
		}

	select(0, NULL, NULL, NULL, &ring_time);

	outbuf[0] = RING_OFF;
	if ( write(bell,outbuf,1) < 0 )	/*turn bell off--very important*/
		{
		perror("ring:failed writing RING_OFF");
		exit(1);
		}
}
