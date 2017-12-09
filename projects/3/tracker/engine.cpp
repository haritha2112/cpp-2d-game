#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "egg.h"
#include "player.h"
#include "movingEnemy.h"
#include "bossEnemy.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"

Engine::~Engine() {
  delete player;
  delete bossEnemy;
  delete tree;
  for ( Drawable* egg : eggs ) {
    delete egg;
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
  renderer( rc->getRenderer() ),
  helpMenuTime(Gamedata::getInstance().getXmlInt("helpMenu/time")),
  sky("sky-back", Gamedata::getInstance().getXmlInt("sky-back/factor") ),
  clouds("cloud-back", Gamedata::getInstance().getXmlInt("cloud-back/factor") ),
  mountains("mountain-back", Gamedata::getInstance().getXmlInt("mountain-back/factor") ),
  ground("ground-back", Gamedata::getInstance().getXmlInt("ground-back/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("BlueBird", "BlueBullet")),
  bossEnemy(new BossEnemy("YellowBee")),
  tree(new Tree("Tree")),
  eggs(),
  enemies(),
  strategies(),
  currentSprite(0),
  currentStrategy(0),
  showHelpMenu(false),
  hud( Hud::getInstance(player) ),
  helpMenu( HelpMenu::getInstance() ),
  gameOverBox( GameOverBox::getInstance(player) ),
  makeVideo(false)
{
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  int eggCount = Gamedata::getInstance().getXmlInt("Egg/count");
  int greenEnemyCount = Gamedata::getInstance().getXmlInt("GreenEnemy/count");
  int redEnemyCount = Gamedata::getInstance().getXmlInt("RedEnemy/count");
  for(int index=0; index < eggCount; index++) {
    eggs.push_back(new Egg("Egg"));
  }
  for(int index=0; index < greenEnemyCount; index++) {
    enemies.push_back(new MovingEnemy("GreenEnemy", pos, w, h));
  }
  for(int index=0; index < redEnemyCount; index++) {
    enemies.push_back(new MovingEnemy("RedEnemy", pos, w, h));
  }
  for(unsigned long index=0; index < enemies.size(); index++) {
    player->attach( static_cast<MovingEnemy*>(enemies[index]) );
  }
  strategies.push_back( new PerPixelCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
  clouds.draw();
  mountains.draw();
  ground.draw();
  tree->draw();
  player->draw();
  bossEnemy->draw();
  for ( const Drawable* egg : eggs ) { egg->draw(); }
  for ( const Drawable* enemy : enemies ) { enemy->draw(); }
  hud.draw(viewport.getPosition());
  if(clock.getSeconds() < helpMenuTime || showHelpMenu) {
    helpMenu.draw();
  }
  if (player->hasReachedTree() && bossEnemy->isDead()) {
    gameOverBox.draw(viewport.getPosition(), true);
  }
  else if (player->getRemainingLives() <= 0) {
    gameOverBox.draw(viewport.getPosition(), false);
  }
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  for ( Drawable* d : eggs ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      player->addEgg();
      Egg* egg = static_cast<Egg*>(d);
      egg->removeFromScreen();
    }
  }
  for ( Drawable* e : enemies ) {
    MovingEnemy* enemy = static_cast<MovingEnemy*>(e);
    if ( strategies[currentStrategy]->execute(*player, *e) ) {
      enemy->explode();
      if (player->isInvincible()) {
        player->incrementEnemiesDestroyed();
      } else {
        player->explode();
        bossEnemy->setOriginalState();
      }
    }
    else {
      player->destroyIfShot(enemy);
    }
  }
  if ( strategies[currentStrategy]->execute(*player, *bossEnemy) ) {
    if (player->isInvincible()) {
      bossEnemy->explode();
      for ( Drawable* e : enemies ) {
        MovingEnemy* enemy = static_cast<MovingEnemy*>(e);
        enemy->explode();
        enemy->setRespawn(false);
      }
    } else {
      player->explode();
    }
  }
  else {
    player->destroyIfShot(bossEnemy);
  }
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  if (bossEnemy->isDead()) {
    for ( Drawable* d : eggs ) {
      static_cast<Egg*>(d)->removeFromScreen();
    }
  }
  sky.update();
  clouds.update();
  mountains.update();
  ground.update();
  tree->update(ticks);
  player->update(ticks);
  bossEnemy->update(ticks);
  for(Drawable* egg : eggs) {
    egg->update(ticks);
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
        if ( keystate[SDL_SCANCODE_R] ) {
          player->restartGame();
          bossEnemy->restartGame();
          for(Drawable* egg : eggs) {
            static_cast<Egg*>(egg)->restartGame();
          }
          for(Drawable* enemy : enemies) {
            static_cast<MovingEnemy*>(enemy)->restartGame();
          }
        }
        if ( keystate[SDL_SCANCODE_G] ) {
          player->toggleGodMode();
        }
        if ( keystate[SDL_SCANCODE_F1] && !showHelpMenu) {
          showHelpMenu = true;
        }
        else if ( keystate[SDL_SCANCODE_F1] && showHelpMenu) {
          showHelpMenu = false;
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
