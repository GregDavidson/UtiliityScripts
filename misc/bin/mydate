echo Sunday:Monday:Tuesday:Wednesday:Thursday:Friday:Saturday January:February:March:April:May:June:July:August:September:October:November:December `date '+%r %w:%d:%m:%y'` |
awk '{
  OFS=", "
  split($1,day,":")
  split($2,month,":")
  split($3,time,":")
# meridian = ($4 == "AM") ? "a.m." : "p.m."
  if ($4 == "AM") meridian = "a.m." ; else meridian = "p.m."
  split($5,date,":")
  print (time[1]+0) ":" time[2] " " meridian, day[date[1]+1], (date[2]+0) " " month[date[3]+0] " " (date[4]+2000)
}'
