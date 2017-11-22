#include "player.h"
#include "renderContext.h"

Player::Player( const std::string& right, const std::string& left) :
  TwoWaySprite(right, left),
  collision(false),
  facing(RIGHT),
  initialVelocity(getVelocity()),
  observers()
{ }

Player::Player(const Player& s) :
  TwoWaySprite(s),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  observers( s.observers )
  { }

Player& Player::operator=(const Player& s) {
  TwoWaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  observers = s.observers;
  return *this;
}

void Player::stop() {
  setVelocity(Vector2f(0,0));
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

void Player::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  switch(facing) {
    case LEFT: setImages( RenderContext::getInstance()->getImages(getLeftSprite()) ); break;
    case RIGHT: setImages( RenderContext::getInstance()->getImages(getRightSprite()) ); break;
  }

  std::list<GreenEnemy*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }

  stop();
}

void Player::detach( GreenEnemy* o ) {
  std::list<GreenEnemy*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}
