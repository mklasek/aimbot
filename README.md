# aimbot
external csgo aimbot

External aimbot/info beep experiment. 

Aimbot thread avoids writing into localplayer's viewangles to aim (probably an instant ban) 
and instant cursor movement by utilizing an angle P-regulator, converging the angle between forward 
view vector and the vector from camera location to target to 0°. Lots of vector math present due to this

Beeps were a later expansion supposed to provide information about nearby unseen enemies

While only tested in one match, it was working about as well as you'd expect something like this to work (the opposite of subtle)
and it was extremely fun to make with the help of the unknowncheats forums and msdn.microsoft.com win32 API docs




