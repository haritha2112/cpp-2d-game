#ifndef BOSSENEMY_H
#define BOSSENEMY_H

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class BossEnemy : public Drawable {
public:
	BossEnemy(const std::string&);
	BossEnemy(const BossEnemy&);
	BossEnemy& operator=(const BossEnemy&);
  ~BossEnemy();

	virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Image* getImage() const { return images[currentFrame]; }
  virtual const SDL_Surface* getSurface() const { return images[currentFrame]->getSurface(); }
  int getScaledWidth()  const { return getScale()*images[currentFrame]->getWidth(); }
  int getScaledHeight()  const { return getScale()*images[currentFrame]->getHeight(); }

	void reset();
	void restartGame();
	bool explosionDone();
  void explode();
	void setOriginalState() {
		setPosition(initialPosition);
		bulletsHit = 0;
	}
	void gotShot() { ++bulletsHit; }
	bool canDie() { return bulletsToDie == bulletsHit; }

private:
	std::vector<Image *> images;
  ExplodingSprite* explosion;
	unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
	int viewWidth;
	int viewHeight;
	int worldWidth;
	int worldHeight;
	int enemyWidth;
	int enemyRange;
	unsigned int bulletsToDie;
	unsigned int bulletsHit;
	Vector2f initialPosition;

	void advanceFrame(Uint32 ticks);
};
#endif
