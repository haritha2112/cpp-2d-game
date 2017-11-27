#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite(const std::string&, const std::string&);
  TwoWaySprite(const TwoWaySprite&);
  ~TwoWaySprite();

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { return images[currentFrame]; }
  int getScaledWidth()  const { return getScale()*images[currentFrame]->getWidth(); }
  int getScaledHeight()  const { return getScale()*images[currentFrame]->getHeight(); }
  virtual const SDL_Surface* getSurface() const { return images[currentFrame]->getSurface(); }
  void setImages(std::vector<Image *> newImages) { images = newImages; }

  std::string const getLeftSprite() const { return leftsprite; }
  std::string const getRightSprite() const { return rightsprite; }

  bool explosionDone();
  virtual void explode();
  virtual void reset();

protected:
  std::vector<Image *> images;
  ExplodingSprite* explosion;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  std::string rightsprite;
  std::string leftsprite;

  void advanceFrame(Uint32 ticks);
  TwoWaySprite& operator=(const TwoWaySprite&);
};
#endif
