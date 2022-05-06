#! /usr/bin/wish8.5 -f

# Turn the monitor off and keep it off until button is pushed

set seconds 1000
set dpms_interval [expr 60 * $seconds]
proc dpms_suspend {} {
  exec xset dpms force suspend
}

proc dpms_suspend_bg {} {
  dpms_suspend
  global dpms_interval
  bg_go
  bg $dpms_interval dpms_suspend
} 

set bg_loop 1
proc bg_go {} { global bg_loop; set bg_loop 1; }
proc bg_stop {} { global bg_loop; set bg_loop 0; }
proc bg_repeat {interval task} {
    eval $task
    after $interval [list bg $interval $task]
}
proc bg {interval task} {
    global bg_loop
    if {$bg_loop} {
       after idle bg_repeat $interval $task
    }
}

set font {helvetica 24}

button .pause  -text "Pause" -font $font -command { bg_stop }
button .suspend  -text "Power off monitor" -font $font -command {
  dpms_suspend_bg
}
button .quit  -text "Quit" -font $font -command { exit 0 }

# Make the buttons visible
pack .suspend -fill x
pack .pause .quit -side left -expand 1 -fill x

dpms_suspend_bg
