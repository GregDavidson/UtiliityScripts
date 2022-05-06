#!/usr/bin/awk
# input looks like:
# Filesystem           1K-blocks      Used Available Use% Mounted on
# /dev/sdb2             33024248  15258308  16088404  49% /
# udev                   2023864       220   2023644   1% /dev

function p_int(n, p) {
    if (n < 1)	return ""
    if (p == 3)	return p_int(n, 0) ","
    			return p_int( int((n/10) ), p+1) n%10
}

BEGIN{
    fmt4="%20s %11s %11s %11s "
    fmt6=fmt4 "%4s %-10s\n"
    fmt5=fmt4 "%3.0f%%\n"
}
$1!~/\//{
    printf(fmt6, $1, $2, $3, $4, $5, $6 " " $7)
}
$1~/\//{
    kblocks += $2; used += $3; free += $4
    printf(fmt6, $1, p_int($2), p_int($3), p_int($4), $5, $6)
}
END{
    printf(fmt5, "TOTAL", p_int(kblocks), p_int(used), free, used*100/(free+used))
}