#include "bossEnemy.h"
#include "gamedata.h"


BossEnemy::BossEnemy( const std::string& name ) :
  MultiSprite(name),
  viewWidth(Gamedata::getInstance().getXmlFloat("view/width")),
  viewHeight(Gamedata::getInstance().getXmlFloat("view/height")),
  worldWidth(Gamedata::getInstance().getXmlFloat("world/width")),
  worldHeight(Gamedata::getInstance().getXmlFloat("world/height")),
  enemyWidth(Gamedata::getInstance().getXmlFloat(name+"/imageWidth")),
  enemyRange(Gamedata::getInstance().getXmlFloat("view/enemyRange")),
  bulletsToDie(Gamedata::getInstance().getXmlFloat(name+"/bulletsToDie")),
  bulletsHit(0),
  initialPosition(Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                           Gamedata::getInstance().getXmlInt(name+"/startLoc/y")))
{
  setPosition(initialPosition);
}

BossEnemy::BossEnemy(const BossEnemy& s) :
  MultiSprite(s),
  viewWidth(s.viewWidth),
  viewHeight(s.viewHeight),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight),
  enemyWidth(s.enemyWidth),
  enemyRange(s.enemyRange),
  bulletsToDie(s.bulletsToDie),
  bulletsHit(s.bulletsHit),
  initialPosition(s.initialPosition)
  { }

BossEnemy& BossEnemy::operator=(const BossEnemy& s) {
  MultiSprite::operator=(s);
  viewWidth = s.viewWidth;
  viewHeight = s.viewHeight;
  worldWidth = s.worldWidth;
  worldHeight = s.worldHeight;
  enemyWidth = s.enemyWidth;
  enemyRange = s.enemyRange;
  bulletsToDie = s.bulletsToDie;
  bulletsHit = s.bulletsHit;
  initialPosition = s.initialPosition;
  return *this;
}

void BossEnemy::reset() {
  setPosition(Vector2f(worldWidth + enemyWidth + 1000, 1000));
  if ( explosionDone() ) {
    MultiSprite::reset();
    bulletsHit = 0;
    setPosition(initialPosition);
  }
}

void BossEnemy::update(Uint32 ticks) {
  MultiSprite::update(ticks);
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }
}
