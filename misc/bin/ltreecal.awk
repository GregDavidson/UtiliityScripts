#! /bin/awk -f
BEGIN {OFS=FS="\t"}
$4=="NAO" && NF == 5 { print $3, $5 ; next }
$4==4 && NF == 8 { print $3, $8, $5, $7 ; next }
$4==4 && NF == 7 { date=$3; number=$5; title=$7 ; next }
NF==1 { print date, $1, number, title ; date=""; number=""; title="" ; next }
date != "" || title != "" || number != "" { print date, number, title }
{print}
END { if (date != "" || title != "" || number != "")  print date, number, title }

