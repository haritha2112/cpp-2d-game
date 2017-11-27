#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <list>
#include <cmath>
#include "twowaySprite.h"
#include "movingEnemy.h"
#include "bulletPool.h"

class MovingEnemy;

class Player : public TwoWaySprite {
public:
  enum Facing { LEFT, RIGHT };
  Player(const std::string&, const std::string&, const std::string&);
  Player(const Player&);
  Player& operator=(const Player&);

  void collided() { collision = true; }
  void missed() { collision = false; }
  virtual void draw() const;

  void right();
  void left();
  void up();
  void down();
  void shoot();

  unsigned int bulletCount() const { return bullets.bulletCount(); }
  unsigned int freeCount() const { return bullets.freeCount(); }

  void update(Uint32 ticks);
  void attach( MovingEnemy* o ) { observers.push_back(o); }
  void detach( MovingEnemy* o );
  void destroyIfShot( Drawable* o );

  void stop();
private:
  bool collision;
  Facing facing;
  Vector2f initialVelocity;
  std::list<MovingEnemy*> observers;

  std::string bulletName;
  float bulletInterval;
  float timeSinceLastBullet;
  float minBulletSpeed;
  Vector2f rightOffset;
  Vector2f leftOffset;
  BulletPool bullets;
};
#endif
