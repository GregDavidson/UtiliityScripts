#!/bin/sh
# J. Greg Davidson
# Copyright (c) 1992, 1993, 1994 Virtual Infinity Systems.  All rights reserved.

[ -z "$hostname" ] && hostname=`hostname`

if [ -z "$wm" ] ; then 
  case $hostname in
    vis) wm=tvtwm ;;
    *)   wm=twm   ;;
  esac
fi

[ -z "$DISPLAY"  ] && DISPLAY=unix:0
export DISPLAY

for d in /sw/X/bin ; do
  if [ -d $d ] ; then
    expr ":${PATH}:" : ":${d}:" >/dev/null || PATH="$PATH:$d"
  else
    echo .xinitrc: Directory $d not found!
  fi
done
export PATH

case $hostname in
vis) wait=10 ;;
bar) echo "I'll start up slow for bar" ; wait=30 ;;
*)   echo .xinitrc: Hostname $hostname not recognized ; wait=20 ;;
esac

sleep=$wait
sleep_add(){ sleep=`expr $sleep + $1` ; }
delay(){ (sleep $1 ; shift ; exec $*) & }
launch(){ delay $sleep $@ ; sleep_add $wait ; }
ow_launch(){ launch OPENWINHOME=/usr/openwin LD_LIBRARY_PATH=/usr/openwin/lib:/usr/lib $* ; }

xrdb -load $HOME/.Xdefaults
xmodmap $HOME/.xmodmaprc

launch xterm -ls -geometry 80x18-0-0 -C
launch /local/bin/emacs/emacs -w =81x67+150-0
launch xterm -geometry 80x24-0+0

width=130 inc_height=20 ypos=0
left(){
  height=$1 ; program=$2 ; shift 2
  launch $program -geometry ${width}x$height+0+$ypos $*
  ypos=`expr $height + $ypos + $inc_height`
}

left 130 xclock -analog
#left 90 xcalendar
if [ $hostname != bar ] ; then
  left  60 xpostit
fi
left 100 xman -bw 2
left 200 xcalc

launch xhost +
launch xsetroot -gray
$wm

xsetroot -solid white
kbd_mode -a # fixes up Sun workstation keyboard
