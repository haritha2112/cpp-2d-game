#include "greenEnemy.h"


GreenEnemy::GreenEnemy( const std::string& name) :
  MultiSprite(name)
{ 
  setX(rand()%(5000-800)+800);
  setY(rand()%351);
}

GreenEnemy::GreenEnemy(const GreenEnemy& s) :
  MultiSprite(s)
  { }

GreenEnemy& GreenEnemy::operator=(const GreenEnemy& s) {
  MultiSprite::operator=(s);
  return *this;
}


void GreenEnemy::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getX() < -60) {
    setX(worldWidth);
    setY(rand()%351);
  }

}

