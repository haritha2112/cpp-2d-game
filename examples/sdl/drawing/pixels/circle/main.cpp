#include <SDL2/SDL.h>

const int NO_OF_POINTS = 360;
const double PI = 3.1415926535897;
const double RAD2DEG = (180/PI);
const double DEG2RAD = (PI/180);

#define DegToRad(x) ((x)*DEG2RAD)
#define RadToDeg(x) ((x)*RAD2DEG)

const int WINDOW_WIDTH = 600;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
    WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer
  );

  SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  int x = 320;
  int y = 240;
  int radius = 50;

  int step = 360/NO_OF_POINTS;
  for (int theta = 0; theta < 360; theta += step) {
    SDL_RenderDrawPoint(renderer, 
      x+radius*cos(DegToRad(theta)), 
      y+radius*sin(DegToRad(theta))
    );
  }


  SDL_RenderPresent(renderer);

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
