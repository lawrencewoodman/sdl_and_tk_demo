#include <SDL.h>
#include <tcl.h>
#include <tk.h>

#include "ball.h"
#include "ballscreen.h"
#include "tkwin.h"

const int screen_width = 400;
const int screen_height = 400;
const int screen_depth = 8;
const int ball_step = 4;

void
event_loop()
{
  SDL_Event event;

  while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT)) {
    Tk_DoOneEvent(TK_ALL_EVENTS|TK_DONT_WAIT);
  }
}

int
main(int argc, char *argv[])
{
  if (!TkWin_init()) {
    return 1;
  }

  if (!BallScreen_init(TkWin_getWindowID(), screen_width,
        screen_height, screen_depth)) {
    return 1;
  }

  if (!Ball_init(BallScreen_getScreenSurface(),
                 screen_width/2, screen_height/2, ball_step)) {
    return 1;
  }

  event_loop();

  return 0;
}
