#include <cmath>
#include <random>
#include <functional>
#include "egg.h"
#include "gamedata.h"
#include "renderContext.h"

Egg::Egg(const std::string& name) :
  Drawable(name, Vector2f(0, 0), Vector2f(0, 0)),
  image( RenderContext::getInstance()->getImage(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  initialPosition(Vector2f(rand()%(worldWidth-200)+200, rand()%(worldHeight)))
{
  setPosition(initialPosition);
}

Egg::Egg(const Egg& s) :
  Drawable(s),
  image(s.image),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight),
  initialPosition(s.initialPosition)
{}

Egg& Egg::operator=(const Egg& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  initialPosition = rhs.initialPosition;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void Egg::restartGame() {
  setPosition(Vector2f(rand()%(worldWidth + 200), rand()%(worldHeight)));
}

void Egg::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  image->draw(getX(), getY(), getScale());
}

void Egg::update(Uint32 ticks) {}
