#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include <vector>

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  //void switchSprite();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  Hud& hud;

  SDL_Renderer * const renderer;
  unsigned int hudTime;
  World sky;
  World clouds;
  World mountains;
  World ground;
  Viewport& viewport;

  Player* player;
  std::vector<Drawable* > sprites;
  std::vector<Drawable* > enemies;
  std::vector<CollisionStrategy*> strategies;
  int currentSprite;
  int currentStrategy;
  bool collision;
  bool showHud;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
