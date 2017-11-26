#ifndef BULLET__H
#define BULLET__H

#include <iostream>
#include "multisprite.h"

class Bullet : public MultiSprite {
public:
  Bullet( const std::string& name, const Vector2f& pos, const Vector2f& vel );
  Bullet( const Bullet& );
  Bullet& operator=( const Bullet& );

  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset();

private:
  float distance;
  float maxDistance;
  bool tooFar;
};
#endif
