#include <SDL.h>
#include "ballscreen.h"

static SDL_Surface *sfScreen = NULL;

static void BallScreen_embedInWindow(char *windowID);
static void BallScreen_clear(void);

int
BallScreen_init(char *windowID, int width, int height, int depth)
{
  char buf[50];

  snprintf(buf, 50, "SDL_WINDOWID=%s", windowID);
  SDL_putenv(buf);

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return 0;
  }

  sfScreen = SDL_SetVideoMode(width, height, depth,
                              SDL_NOFRAME|SDL_SWSURFACE|SDL_ANYFORMAT);
  if (sfScreen == NULL) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return 0;
  }

  BallScreen_clear();

  return 1;
}

void
BallScreen_destroy(void)
{
  SDL_Quit();
}

void
BallScreen_refresh(void)
{
  if (sfScreen != NULL)
    SDL_Flip(sfScreen);
}

SDL_Surface *
BallScreen_getScreenSurface(void)
{
  return sfScreen;
}

static void
BallScreen_clear(void)
{
  SDL_FillRect(sfScreen, NULL, 0);
  SDL_Flip(sfScreen);
}
