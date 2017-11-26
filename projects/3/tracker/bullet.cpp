#include <iostream>
#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "imageFactory.h"

Bullet::Bullet( const std::string& name, const Vector2f& pos, const Vector2f& vel ) :
  MultiSprite(name, pos, vel),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
  tooFar(false)
{}

Bullet::Bullet( const Bullet& b ) :
  MultiSprite( b ),
  distance( b.distance ),
  maxDistance( b.maxDistance ),
  tooFar( b.tooFar )
{}

Bullet& Bullet::operator=( const Bullet& b ) {
  MultiSprite::operator=(b);
  distance = b.distance;
  maxDistance = b.maxDistance;
  tooFar = b.tooFar;
  return *this;
}

void Bullet::reset() {
  tooFar = false;
  distance = 0;
}

void Bullet::update(Uint32 ticks) {
  Vector2f pos = getPosition();
  MultiSprite::update(ticks);

  if ( getY() < 0 || getY() + getScaledHeight() > worldHeight ) {
    tooFar = true;
  }
  if ( getX() < 0 || getX() > worldWidth ) {
    tooFar = true;
  }
  distance += ( hypot( getX()-pos[0], getY()-pos[1]) );
  if ( distance > maxDistance ) {
    tooFar = true;
  }
}
