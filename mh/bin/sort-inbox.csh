#!/bin/csh -f
alias p 'set p = (`pick +inbox \!*`)'
alias to 'p -to'
alias cc 'p -cc'
#alias rr '(refile -src +inbox $p \!* ; echo $#p in \!* "< $p >") > /dev/tty'
alias r 'test $#p -ne 0 && r1'
alias r1 'test "$p[1]" -ne 0 && echo about to call r2 && r2'
#alias r2 'echo calling r2'
alias r2 'refile -src +inbox $p \!* ; echo $#p in \!* "< $p >" > /dev/tty'
alias read 'r +read/\!*'
to BISEXU-L;		read bisexu-l +old/bisexu-l
to gaynet;		read gaynet
to alternates;		read alternates +news/alternates
p --Sender GUTNBERG;	read gutnberg
to greg -or -to jgd;	read greg
to sdsysmgr;		read sdsysmgr
to slug;		read sdslug
to league;		read league
to postgres;		read postgres
to gutnberg;		read gutnberg
to litprog;		read litprog
to haskld-l;		read haskell
to haskell;		read haskell
to sml-list;		read ml
cc BISEXU-L;		read bisexu-l +old/bisexu-l
cc gaynet;		read gaynet
cc alternates;		read alternates +news/alternates
cc greg -or -to jgd;	read greg
cc sdsysmgr;		read sdsysmgr
cc slug;		read sdslug
cc league;		read league
cc postgres;		read postgres
cc gutnberg;		read gutnberg
cc litprog;		read litprog
cc haskld-l;		read haskell
cc haskell;		read haskell
cc sml-list;		read ml
p;			read misc
