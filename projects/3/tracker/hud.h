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
  void draw(const Vector2f& pos) const;

private:
  Player* player;
  Image* heartImage;
  Image* eggImage;
  std::vector<Image *> deadGreenEnemy;
  std::vector<Image *> deadRedEnemy;
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
  void drawHealthBar(int x, int y, int w, int h, float percent) const;
};
#endif
