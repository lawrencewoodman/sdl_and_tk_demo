proc handleKey {key} {
  switch -regexp -- $key {
    .*Up$ {ball up}
    .*Down$ {ball down}
    .*Left$ {ball left}
    .*Right$ {ball right}
  }
}

wm title . {Demo of using SDL embedded in a Tk Window}
wm protocol . WM_DELETE_WINDOW {destroy_window}

frame .screen -width 400 -height 400 -background ""
pack .screen

frame .buttons
frame .buttons.lr
ttk::button .buttons.up -text {Up} -command {ball up}
ttk::button .buttons.down -text {Down} -command {ball down}
ttk::button .buttons.lr.left -text {Left} -command {ball left}
ttk::button .buttons.lr.right -text {Right} -command {ball right}
ttk::button .quit -text {Quit} -command {destroy_window}

pack .buttons.lr.left -side left -expand 1 -fill both
pack .buttons.lr.right -side left -expand 1 -fill both

pack .buttons.up -side top -expand 1 -fill both
pack .buttons.lr -side top -expand 1 -fill both
pack .buttons.down -side top -expand 1 -fill both
pack .buttons -side left -expand 1 -fill both
pack .quit -side left -expand 1 -fill both

bind all <KeyRelease> {handleKey %K}
bind . <Expose> {screen_refresh}
