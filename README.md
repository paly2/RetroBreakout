# RetroBreakout

## How to compile it ?

Just type these commands in a terminal :  
`git clone https://github.com/paly2/RetroBreakout.git`  
`cd RetroBreakout`  
`sudo apt-get install libsdl1.2-dev`  
`make`

## How to use it ?

### Run the program

To run the program, just excute the `RetroBreakout` executable. You don't need to run it in a terminal, however that's recommanded to see the text messages printed.  
If you are in the program directory, you can do :  
`./RetroBreakout`  
or, if you want the game to be in full screen :  
`./RetroBreakout --fullscreen`  
Press return to begin the game.

### Controls

- Mouse motion : move the racquet
- Escape : Quit the program
- P : pause
- G : mouse grabbing activation/deactivation (default value : deactivate)
- F5 : fullscreen (only works with X11) (default value : no, but you can change it by using the `--fullscreen` option (see `Run the program`))
- Return : throw (again) the ball (Use this key to begin. You can also use it when the ball doesn't come back to the racquet.)
- Keypad numbers : change difficulty (ball speed) (1 = 100 pixels per second ; 2 = 200 pixels per second ; 3 = 300 pixels per second...) (default value : 4)
