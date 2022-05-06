1i\
\\input /home/greg/SW/ics/etc/xics.tex
#
# Translate special characters in the original text
/^[^	]/s=\\=\\backslash=g
/^[^	]/s=[$]=\\&=g
/^[^	]/s=[{}]=$\\&$=g
/^[^	]/s=[|<>]=$&$=g
/^[^	]/s=\\backslash=$&$=g
/^[^	]/s=\.\.\.=\\dots{}=g
/^[ 	]*$/d
/^% /d
# emphasized operators
/_[&%]/s/_\([&%]\)/\\C{\1}/g
# _emphasized _words , _(emphasized words)_ _<italicised text>_
/@[\.-a-zA-Z]/s/@\([\.-a-zA-Z][-\.a-zA-Z_0-9]*\)/{\\bf \1}/g
/\^/s/\^\([^^]*\)\^/\\C{\1}/g
/_(/s/_(\([^)]*\))_/\\C{\1}/g
/_</s/_<\([^>]*\)>_/{\\sl \1}/g
/_[\.-a-zA-Z]/s/_\([\.-a-zA-Z][-\.a-zA-Z_0-9]*\)/\\C{\1}/g
#
/^!!/s=^!!\([0-9][0-9]*\)  *\(.*\)$=\\Chapter{\1}{\2}=
/^![0-9]/s=^!\([0-9]\)  *\(.*\)$=\\Section{\1}{\2}=
/^\*\*\*\*\*  *\(.*\)$/s||\\Section{5}{\1}|
/^\*\*\*\*  *\(.*\)$/s||\\Section{4}{\1}|
/^\*\*\*  *\(.*\)$/s||\\Section{3}{\1}|
/^\*\*  *\(.*\)$/s||\\Section{2}{\1}|
/^\*\([0-9][0-9]*\) \(.*\)/s||\\Chapter{\1}{\2}|
#
/^# /s=^# *\(.*\)$=\\N{\1}=
/^o /s=^o *\(.*\)$=\\B{\1}=
/^	/s=^	\(.*\)$=\\myexample{\1}=
/^-  */s==\\D =
/^:  */s==\\P =
/^\\\$  */s==\\P \\C{\\$}\ =
/^\$  */s==\\P \\C{\\$}\ =
#
/^+c /s=^+c  *\(.*\)$=\\Cfile \1/=
/^+o /s=^+o  *\(.*\)$=\\Outfile \1/=
/^+d /s=^+d  *\(.*\)$=\\vfil\\vfil{\\bf REPLACE THIS PAGE WITH DIAGRAM:}\\vfil{\\bf ``\1''=
# Translate remaining special characters:
# These could have meant something to earlier rules
/^[^	]/s=[&%^]=\\&=g
/_/s//\\&/g
/\#/s//\\&/g
/^[^	]/s=\\\^=\\v{ }=g
/C-\([A-Z]\)/s==\\^\1=g
$a\
\\vfil\\eject\\end
