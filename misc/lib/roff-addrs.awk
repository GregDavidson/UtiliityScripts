BEGIN { RS="" ; FS = "\n" }
{ print ".(b" ; print $0 ; print ".)b" ; print "" }
