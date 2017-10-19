#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaySprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  for(auto& s : sprites) delete s;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  sky("sky-back", Gamedata::getInstance().getXmlInt("sky-back/factor") ),
  clouds("cloud-back", Gamedata::getInstance().getXmlInt("cloud-back/factor") ),
  mountains("mountain-back", Gamedata::getInstance().getXmlInt("mountain-back/factor") ),
  ground("ground-back", Gamedata::getInstance().getXmlInt("ground-back/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  makeVideo(false)
{
  sprites.push_back(new Sprite("Egg"));
  sprites.push_back(new MultiSprite("EvilFlower"));
  sprites.push_back(new TwoWaySprite("BirdRight","BirdLeft"));
  Viewport::getInstance().setObjectToTrack(sprites[0]);
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

  for(auto sprite : sprites) {
    sprite->draw();
  }

  IOmod::getInstance().writeText(strm.str(), 30, 60);
  IOmod::getInstance().writeText("Haritha Rathinakumar",my_color, 30, 410);

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  sky.update();
  clouds.update();
  mountains.update();
  ground.update();

  for(auto sprite : sprites) {
    sprite->update(ticks);
  }
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 3;
  switch(currentSprite) {
    case 0:
      Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
      break;
    case 1:
      Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
      break;
    case 2:
      Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
      break;
  }
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
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
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

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
