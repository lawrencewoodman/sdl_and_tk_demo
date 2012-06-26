#include <SDL.h>

static int step;
static SDL_Surface *sfBall;
static SDL_Rect rcBall;
static int max_x, max_y;
static int min_x, min_y;
static SDL_Surface *sfScreen;

static void Ball_moveTo(int x, int y);
static void Ball_draw(void);

int
Ball_init(SDL_Surface *_sfScreen, int x, int y, int _step)
{
  if ((sfBall = SDL_LoadBMP("ball.bmp")) == NULL) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return 0;
  }

  rcBall.x = x;
  rcBall.y = y;
  rcBall.h = sfBall->h;
  rcBall.w = sfBall->w;
  sfScreen = _sfScreen;
  step = _step;

  max_x = sfScreen->w - sfBall->w;
  max_y = sfScreen->h - sfBall->h;
  min_x = 0;
  min_y = 0;

  Ball_draw();

  return 1;
}

void
Ball_destroy(void)
{
  SDL_FreeSurface(sfBall);
}

void
Ball_up(void)
{
  Ball_moveTo(rcBall.x, rcBall.y-step);
}

void
Ball_down(void)
{
  Ball_moveTo(rcBall.x, rcBall.y+step);
}

void
Ball_left(void)
{
  Ball_moveTo(rcBall.x-step, rcBall.y);
}

void
Ball_right(void)
{
  Ball_moveTo(rcBall.x+step, rcBall.y);
}

static void
Ball_moveTo(int x, int y)
{
  SDL_FillRect(sfScreen, &rcBall, 0);

  rcBall.x = x;
  rcBall.y = y;

  if (rcBall.x < min_x) {
    rcBall.x = min_x;
  } else if (rcBall.x > max_x) {
    rcBall.x = max_x;
  }

  if (rcBall.y < min_y) {
    rcBall.y = min_y;
  } else if (rcBall.y > max_y) {
    rcBall.y = max_y;
  }

  Ball_draw();
}

static void
Ball_draw(void)
{
  SDL_BlitSurface(sfBall, NULL, sfScreen, &rcBall);
  SDL_Flip(sfScreen);
}
