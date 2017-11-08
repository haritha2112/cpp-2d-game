#include "greenEnemy.h"
#include "gamedata.h"


GreenEnemy::GreenEnemy( const std::string& name, const Vector2f& pos, int w, int h ) :
  MultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  viewWidth(Gamedata::getInstance().getXmlFloat("view/width")),
  viewHeight(Gamedata::getInstance().getXmlFloat("view/height")),
  worldWidth(Gamedata::getInstance().getXmlFloat("world/width")),
  enemyWidth(Gamedata::getInstance().getXmlFloat("GreenEnemy/imageWidth")),
  enemyRange(Gamedata::getInstance().getXmlFloat("view/enemyRange"))
{ 
  setX(rand()%(worldWidth-viewWidth)+viewWidth);
  setY(rand()%(viewHeight-enemyRange)+1);
}

GreenEnemy::GreenEnemy(const GreenEnemy& s) :
  MultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  viewWidth(s.viewWidth),
  viewHeight(s.viewHeight),
  worldWidth(s.worldWidth),
  enemyWidth(s.enemyWidth),
  enemyRange(s.enemyRange)
  { }

GreenEnemy& GreenEnemy::operator=(const GreenEnemy& s) {
  MultiSprite::operator=(s);
  playerPos = s.playerPos;
  playerWidth = s.playerWidth;
  playerHeight = s.playerHeight;
  currentMode = s.currentMode;
  safeDistance = s.safeDistance;
  viewWidth = s.viewWidth;
  viewHeight = s.viewHeight;
  worldWidth = s.worldWidth;
  enemyWidth = s.enemyWidth;
  enemyRange = s.enemyRange;
  return *this;
}

void GreenEnemy::goUp(Uint32 ticks) { 
  float incr = getVelocityY() * static_cast<float>(ticks) * 0.001;
  setY( getY()-incr ); 
}
void GreenEnemy::goDown(Uint32 ticks) { 
  float incr = getVelocityY() * static_cast<float>(ticks) * 0.001;
  setY( getY()+incr ); 
}


void GreenEnemy::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  Vector2f currentPos = getPosition();
  setX(currentPos[0]+incr[0]);

  if ( getX() < -(enemyWidth) ) {
    setX(worldWidth);
    setY(rand()%(viewHeight-enemyRange+1));
  }

  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float px= playerPos[0]+playerWidth/2;
  float py= playerPos[1]+playerHeight/2;
  float distanceToEnemy = std::abs(x-px);

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = PURSUE;
  }
  else if  ( currentMode == PURSUE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      if ( y < py ) goDown(ticks);
      if ( y > py ) goUp(ticks);
    }
  }

}

