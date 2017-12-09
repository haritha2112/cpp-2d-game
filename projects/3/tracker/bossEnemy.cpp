#include "bossEnemy.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

BossEnemy::~BossEnemy() {
  if (explosion) delete explosion;
}

BossEnemy::BossEnemy( const std::string& name ) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(name) ),
  explosion(nullptr),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
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
  Drawable(s),
  images(s.images),
  explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  viewWidth(s.viewWidth),
  viewHeight(s.viewHeight),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight),
  enemyWidth(s.enemyWidth),
  enemyRange(s.enemyRange),
  bulletsToDie(s.bulletsToDie),
  bulletsHit(s.bulletsHit),
  initialPosition(s.initialPosition)
{}

BossEnemy& BossEnemy::operator=(const BossEnemy& s) {
  Drawable::operator=(s);
  images = s.images;
	explosion = s.explosion;
  currentFrame = s.currentFrame;
  numberOfFrames = s.numberOfFrames;
  frameInterval = s.frameInterval;
  timeSinceLastFrame = s.timeSinceLastFrame;
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

void BossEnemy::restartGame() {
  explosion = NULL;
  bulletsHit = 0;
  setPosition(initialPosition);
}

void BossEnemy::draw() const {
	if ( explosion ) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void BossEnemy::explode() {
  if ( !explosion ) {
		Vector2f velocity(100, 100);
    Sprite sprite(getName(), getPosition(), velocity, images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void BossEnemy::reset() {
  setPosition(Vector2f(worldWidth + enemyWidth + 1000, 1000));
  if ( explosionDone() ) {
    delete explosion;
    explosion = NULL;
    bulletsHit = 0;
  }
}

bool BossEnemy::explosionDone() {
	return explosion && explosion->chunkCount() == 0;
}

void BossEnemy::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void BossEnemy::update(Uint32 ticks) {
  if ( explosion ) {
    explosion->update(ticks);
		this->reset();
    return;
  }
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
