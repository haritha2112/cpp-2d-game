#ifndef TREE__H
#define TREE__H

#include <string>
#include "drawable.h"

class Tree : public Drawable {
public:
  Tree(const std::string&);
  Tree(const Tree&);
  virtual ~Tree() { }
  Tree& operator=(const Tree&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const { return image->getSurface(); }
  int getScaledWidth()  const { return getScale()*image->getWidth();  }
  int getScaledHeight() const { return getScale()*image->getHeight(); }

private:
  const Image * image;
};
#endif
