p()	{ pick=`pick +inbox $*`; }
to()	{ p -to $*; }
cc()	{ p -cc $*; }
r()	{
		[ X"$pick" -ne X ] &&
		[ X"$pick" -ne X0 ] &&
		refile -src +inbox $p $* &&
		echo "${*}: $p" > /dev/tty
}
reed() { r "+read/$*"; }
to BISEXU-L;		r +read.bisexu-l +old/bisexu-l
to gaynet;		reed gaynet
to alternates;		r +read/alternates +news/alternates
p --Sender GUTNBERG;	reed gutnberg
to greg -or -to jgd;	reed greg
to sdsysmgr;		reed sdsysmgr
to slug;		reed sdslug
to league;		reed league
to postgres;		reed postgres
to gutnberg;		reed gutnberg
to litprog;		reed litprog
to haskld-l;		reed haskell
to haskell;		reed haskell
to sml-list;		reed ml
cc BISEXU-L;		r +read/bisexu-l +old/bisexu-l
cc gaynet;		reed gaynet
cc alternates;		r +read/alternates +news/alternates
cc greg -or -to jgd;	reed greg
cc sdsysmgr;		reed sdsysmgr
cc slug;		reed sdslug
cc league;		reed league
cc postgres;		reed postgres
cc gutnberg;		reed gutnberg
cc litprog;		reed litprog
cc haskld-l;		reed haskell
cc haskell;		reed haskell
cc sml-list;		reed ml
p;			reed misc
