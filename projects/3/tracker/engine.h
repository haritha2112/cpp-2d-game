#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "helpMenu.h"
#include "gameOverBox.h"
#include "movingEnemy.h"
#include "bossEnemy.h"
#include "tree.h"
#include "sound.h"
#include <vector>

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  unsigned int helpMenuTime;
  World sky;
  World clouds;
  World mountains;
  World mountains2;
  World ground;
  Viewport& viewport;

  Player* player;
  BossEnemy* bossEnemy;
  Tree* tree;
  std::vector<Drawable* > bigBlackBirds;
  std::vector<Drawable* > smallBlackBirds;
  std::vector<Drawable* > eggs;
  std::vector<Drawable* > enemies;
  std::vector<CollisionStrategy*> strategies;
  int currentSprite;
  int currentStrategy;
  bool showHelpMenu;

  Hud& hud;
  HelpMenu& helpMenu;
  GameOverBox& gameOverBox;

  SDLSound* sound;

  bool makeVideo;
  bool gameOverSoundPlayed;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
