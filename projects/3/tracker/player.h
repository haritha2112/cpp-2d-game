#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <list>
#include <cmath>
#include "multisprite.h"
#include "smartSprite.h"

class SmartSprite;

class Player : public MultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();

  void update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );

  void stop();
private:
  bool collision;
  Vector2f initialVelocity;
  std::list<SmartSprite*> observers;
};
#endif
