dnl	Prepare C Program for Publication
dnl	Author: J. Greg Davidson
dnl	Date: 3 December, 1987
dnl
changecom()dnl
dnl
dnl	 Set up for page breaks
dnl
define(`notes_break', ifdef(`for_notes', page_break))dnl
define( `exer_break', ifdef(`for_exer',  page_break))dnl
define( `impl_break', ifdef(`for_impl',  page_break))dnl
define(page_break,`<<<>>>')dnl
dnl
dnl	Z should surround argument prototypes
dnl
define(Z, ifdef(`for_notes', $*, `/*'$*`*/'))dnl
dnl
define(soln_body, ifdef(`for_soln', $1, `  /* * * * * */'))dnl
define(soln_only, ifdef(`for_soln', $1))dnl
define(not_notes, ifdef(`for_notes', , $1))dnl
dnl
dnl	Undefine as much as possible to avoid name collisions
dnl
undefine(`pushdef')dnl
undefine(`popdef')dnl
undefine(`divert')dnl
undefine(`undivert')dnl
undefine(`divnum')dnl
undefine(`incr')dnl
undefine(`decr')dnl
undefine(`eval')dnl
undefine(`index')dnl
undefine(`len')dnl
undefine(`substr')dnl
undefine(`translit')dnl
undefine(`include')dnl
undefine(`sinclude')dnl
undefine(`syscmd')dnl
undefine(`sysval')dnl
undefine(`maketemp')dnl
undefine(`errprint')dnl
undefine(`dumpdef')dnl
undefine(`defn')dnl
undefine(`shift')dnl
undefine(`changecom')dnl
undefine(`m4exit')dnl
undefine(`m4wrap')dnl
undefine(`traceon')dnl
undefine(`traceoff')dnl
undefine(`ifelse')dnl
undefine(`ifdef')dnl
dnl
dnl	and finally:
dnl
undefine(`define')dnl
undefine(`undefine')dnl !
dnl
dnl	The only builtin macros left defined should be:
dnl	dnl	changequote
dnl
changequote(<<<,>>>)dnl
dnl
