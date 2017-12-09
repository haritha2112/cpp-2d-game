#include <cmath>
#include <random>
#include <functional>
#include "tree.h"
#include "gamedata.h"
#include "renderContext.h"

Tree::Tree(const std::string& name) :
  Drawable(name,
          Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                   Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
          Vector2f(0, 0)
          ),
  image( RenderContext::getInstance()->getImage(name) )
{}

Tree::Tree(const Tree& s) :
  Drawable(s),
  image(s.image)
{}

Tree& Tree::operator=(const Tree& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
  return *this;
}

void Tree::draw() const {
  image->draw(getX(), getY(), 0.5);
}

void Tree::update(Uint32 ticks) {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}
