#ifndef EGG__H
#define EGG__H

#include <string>
#include "drawable.h"

class Egg : public Drawable {
public:
  Egg(const std::string&);
  Egg(const Egg&);
  virtual ~Egg() { }
  Egg& operator=(const Egg&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const { return image->getSurface(); }
  int getScaledWidth()  const { return getScale()*image->getWidth();  }
  int getScaledHeight() const { return getScale()*image->getHeight(); }

  void removeFromScreen() { setPosition(Vector2f(-500, -500)); }
  void restartGame();

private:
  const Image * image;
  int worldWidth;
  int worldHeight;
  Vector2f initialPosition;
};
#endif
