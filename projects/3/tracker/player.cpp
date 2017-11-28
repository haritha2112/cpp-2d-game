#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player( const std::string& right, const std::string& left, const std::string& bullet ) :
  TwoWaySprite(right, left),
  collision(false),
  facing(RIGHT),
  initialVelocity(getVelocity()),
  observers(),
  bulletName(bullet),
  bulletInterval(Gamedata::getInstance().getXmlInt(bullet+"/bulletInterval")),
  timeSinceLastBullet(0),
  minBulletSpeed(Gamedata::getInstance().getXmlInt(bullet+"/minBulletSpeed")),
  rightOffset(Vector2f(
    Gamedata::getInstance().getXmlInt(bullet+"/rightOffset/x"),
    Gamedata::getInstance().getXmlInt(bullet+"/rightOffset/y")
  )),
  leftOffset(Vector2f(
    Gamedata::getInstance().getXmlInt(bullet+"/leftOffset/x"),
    Gamedata::getInstance().getXmlInt(bullet+"/leftOffset/y")
  )),
  bullets(BulletPool(bullet))
{ }

Player::Player(const Player& s) :
  TwoWaySprite(s),
  collision(s.collision),
  facing(s.facing),
  initialVelocity(s.getVelocity()),
  observers( s.observers ),
  bulletName( s.bulletName ),
  bulletInterval( s.bulletInterval ),
  timeSinceLastBullet( s.timeSinceLastBullet ),
  minBulletSpeed( s.minBulletSpeed ),
  rightOffset( s.rightOffset ),
  leftOffset( s.leftOffset ),
  bullets( s.bullets )
  { }

Player& Player::operator=(const Player& s) {
  TwoWaySprite::operator=(s);
  collision = s.collision;
  facing = s.facing;
  initialVelocity = s.initialVelocity;
  observers = s.observers;
  bulletName = s.bulletName;
  bulletInterval = s.bulletInterval;
  timeSinceLastBullet = s.timeSinceLastBullet;
  minBulletSpeed = s.minBulletSpeed;
  rightOffset = s.rightOffset;
  leftOffset = s.leftOffset;
  bullets = s.bullets;
  return *this;
}

void Player::stop() {
  setVelocity(Vector2f(0,0));
}

void Player::draw() const {
  TwoWaySprite::draw();
  bullets.draw();
}

void Player::right() {
  facing = RIGHT;
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
}
void Player::left()  {
  facing = LEFT;
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::destroyIfShot( MovingEnemy* enemy ) {
  if ( bullets.collided(enemy) ) {
    enemy->gotShot();
    if (enemy->canDie()) {
      enemy->explode();
    }
  }
}

void Player::destroyIfShot( BossEnemy* enemy ) {
  if ( bullets.collided(enemy) ) {
    enemy->gotShot();
    if (enemy->canDie()) {
      enemy->explode();
      std::list<MovingEnemy*>::iterator ptr = observers.begin();
      while ( ptr != observers.end() ) {
        (*ptr)->explode();
        ++ptr;
      }
    }
  }
}

void Player::shoot() {
  if (timeSinceLastBullet > bulletInterval) {
    Vector2f bulletPosition = getPosition();
    Vector2f bulletVelocity = Vector2f(initialVelocity[0], 0);
    switch(facing) {
      case LEFT:
        bulletPosition[0] += leftOffset[0];
        bulletPosition[1] += leftOffset[1];
        bulletVelocity[0] = -(minBulletSpeed + bulletVelocity[0]);
        break;
      case RIGHT:
        bulletPosition[0] += rightOffset[0];
        bulletPosition[1] += rightOffset[1];
        bulletVelocity[0] += minBulletSpeed;
        break;
    }
    bullets.shoot(bulletPosition, bulletVelocity);
    timeSinceLastBullet = 0;
  }
}

void Player::reset() {
  setPosition(Vector2f(getX(), -1000));
  if ( explosionDone() ) {
    TwoWaySprite::reset();
    std::list<MovingEnemy*>::iterator ptr = observers.begin();
    while ( ptr != observers.end() ) {
      (*ptr)->moveToInitialPosition();
      ++ptr;
    }
    setPosition(Vector2f(Gamedata::getInstance().getXmlInt(rightsprite+"/startLoc/x"),
                         Gamedata::getInstance().getXmlInt(rightsprite+"/startLoc/y")));
  }
}

void Player::update(Uint32 ticks) {
  TwoWaySprite::update(ticks);

  bullets.update(ticks);
  timeSinceLastBullet += ticks;
  switch(facing) {
    case LEFT: setImages( RenderContext::getInstance()->getImages(getLeftSprite()) ); break;
    case RIGHT: setImages( RenderContext::getInstance()->getImages(getRightSprite()) ); break;
  }

  std::list<MovingEnemy*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }

  stop();
}

void Player::detach( MovingEnemy* o ) {
  std::list<MovingEnemy*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}
