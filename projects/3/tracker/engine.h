#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include <vector>

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World sky;
  World clouds;
  World mountains;
  World ground;
  Viewport& viewport;

  std::vector<Drawable* > sprites;
  //Drawable* egg;
  //Drawable* birdRight;
  //Drawable* bird;
  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
