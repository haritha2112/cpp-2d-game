#include "twowaySprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void TwoWaySprite::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

TwoWaySprite::~TwoWaySprite( ) { if (explosion) delete explosion; }

TwoWaySprite::TwoWaySprite(const std::string& right, const std::string& left) :
  Drawable(right,
           Vector2f(Gamedata::getInstance().getXmlInt(right+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(right+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(right+"/speedX"),
                    Gamedata::getInstance().getXmlInt(right+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(right) ),
  explosion(nullptr),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(right+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(right+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  rightsprite(right),
  leftsprite(left)
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s),
  images(s.images),
  explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  rightsprite(s.rightsprite),
  leftsprite(s.leftsprite)
  { }

TwoWaySprite& TwoWaySprite::operator=(const TwoWaySprite& s) {
  Drawable::operator=(s);
  images = s.images;
  explosion = s.explosion;
  currentFrame = s.currentFrame;
  numberOfFrames = s.numberOfFrames;
  frameInterval = s.frameInterval;
  timeSinceLastFrame = s.timeSinceLastFrame;
  worldWidth = s.worldWidth;
  worldHeight = s.worldHeight;
  rightsprite = s.rightsprite;
  leftsprite = s.leftsprite;
  return *this;
}

void TwoWaySprite::draw() const {
  if ( explosion ) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWaySprite::explode() {
  if ( !explosion ) {
    Vector2f velocity(100, 100);
    Sprite sprite(getName(), getPosition(), velocity, images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void TwoWaySprite::reset() {
    delete explosion;
    explosion = NULL;
}

bool TwoWaySprite::explosionDone() {
  return explosion && explosion->chunkCount() == 0;
}

void TwoWaySprite::update(Uint32 ticks) {
  if ( explosion ) {
    explosion->update(ticks);
    this->reset();
    return;
  }

  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}
