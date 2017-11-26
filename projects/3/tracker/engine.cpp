#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaySprite.h"
#include "player.h"
#include "greenEnemy.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"

Engine::~Engine() {
  delete player;
  for ( Drawable* sprite : sprites ) {
    delete sprite;
  }
  for ( Drawable* enemy : enemies ) {
    delete enemy;
  }
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  hud( Hud::getInstance() ),
  renderer( rc->getRenderer() ),
  hudTime(Gamedata::getInstance().getXmlInt("hud/time")),
  sky("sky-back", Gamedata::getInstance().getXmlInt("sky-back/factor") ),
  clouds("cloud-back", Gamedata::getInstance().getXmlInt("cloud-back/factor") ),
  mountains("mountain-back", Gamedata::getInstance().getXmlInt("mountain-back/factor") ),
  ground("ground-back", Gamedata::getInstance().getXmlInt("ground-back/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("BirdRight", "BirdLeft", "BlueBullet")),
  sprites(),
  enemies(),
  strategies(),
  currentSprite(0),
  currentStrategy(0),
  collision(),
  showHud(false),
  makeVideo(false)
{
  sprites.push_back(new Sprite("Egg"));

  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  int greenEnemyCount = Gamedata::getInstance().getXmlInt("GreenEnemy/count");
  for(int index=0; index < greenEnemyCount; index++) {
    enemies.push_back(new GreenEnemy("GreenEnemy", pos, w, h));
    player->attach( enemies[index] );
  }
  strategies.push_back( new PerPixelCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  std::stringstream strm;
  strm << "Fps: " << clock.getFps();
  SDL_Color my_color = {102,0,102,0};

  sky.draw();
  clouds.draw();
  mountains.draw();
  ground.draw();

  for(const Drawable* sprite : sprites) {
    sprite->draw();
  }

  player->draw();

  IOmod::getInstance().writeText(strm.str(), 500, 60);
  IOmod::getInstance().writeText("Haritha Rathinakumar",my_color, 30, 410);

  for ( const Drawable* sprite : sprites ) {
    sprite->draw();
  }
  for ( const Drawable* enemy : enemies ) {
    enemy->draw();
  }
  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  }

  if(clock.getSeconds() < hudTime || showHud) {
    hud.displayHud();
  }

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  for ( const Drawable* e : enemies ) {
    auto it = enemies.begin();
    if ( strategies[currentStrategy]->execute(*player, *e) ) {
      collision = true;
      GreenEnemy* doa = *it;
      player->detach(doa);
    }
  }
  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  sky.update();
  clouds.update();
  mountains.update();
  ground.update();
  player->update(ticks);
  for(Drawable* sprite : sprites) {
    sprite->update(ticks);
  }
  for(Drawable* enemy : enemies) {
    enemy->update(ticks);
  }
  viewport.update(); // always update viewport last
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {
          player->shoot();
        }
        if ( keystate[SDL_SCANCODE_F1] && !showHud) {
          showHud = true;
        }
        else if ( keystate[SDL_SCANCODE_F1] && showHud) {
          showHud = false;
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
