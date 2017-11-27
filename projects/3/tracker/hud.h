#ifndef HUD__H
#define HUD__H
#include <string>
#include <SDL.h>
#include <stdint.h>
#include "clock.h"
#include "ioMod.h"
#include "player.h"

class Hud {
public:
  static Hud& getInstance(Player*);
  ~Hud();
  void displayHud() const;

private:
  Player* player;
  const int width;
  const int height;
  int hudx;
  int hudy;
  SDL_Rect hudRect;
  SDL_Renderer* renderer;
  Hud(Player*);
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  const IOmod& io;
  SDL_Color textFontColor;
  int fontSize()const;
};
#endif
