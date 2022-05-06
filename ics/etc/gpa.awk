NF != 2 || $1 !~ /[0-4n]/ || $2 !~ /[0-4n]/ {
  print "Rejecting record: " $0
  skip
}
{
  if ($1 != "n") { course += $1; ncourse++ }
  if ($2 != "n") { instr  += $2; ninstr++ }
}
END {
  printf("Course GPA = %.2f (%d), Instructor GPA = %.2f (%d)\n", course/ncourse, ncourse, instr/ninstr, ninstr)
}
