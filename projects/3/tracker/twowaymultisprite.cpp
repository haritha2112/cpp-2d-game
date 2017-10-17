#include "twowaymultisprite.h"
#include "gamedata.h"
//#include "imageFactory.h"
#include "renderContext.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks)
{
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval)
	{
		currentFrame = (currentFrame + 1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

const Image* TwoWayMultiSprite::getImage() const
{
	return getimagesBasedOnDirection()[currentFrame];
}

const std::vector<Image *> TwoWayMultiSprite::getimagesBasedOnDirection() const
{
	if (getVelocityX() > 0)
		return image1;
	else if (getVelocityX() < 0)
		return image2;
	else
		return images;
}

TwoWayMultiSprite::TwoWayMultiSprite(const std::string& name, const std::string& name1, const std::string& name2)
	:Drawable(name, Vector2f(Gamedata::getInstance().getXmlInt(name + "/startLoc/x"), Gamedata::getInstance().getXmlInt(name + "/startLoc/y")), Vector2f(Gamedata::getInstance().getXmlInt(name + "/speedX"), Gamedata::getInstance().getXmlInt(name + "/speedY"))),
	images(),
	image1(RenderContext::getInstance()->getImages(name1)),
	image2(RenderContext::getInstance()->getImages(name2)),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	currentFrame(0),
	numberOfFrames(Gamedata::getInstance().getXmlInt(name + "/frames")),
	frameInterval(Gamedata::getInstance().getXmlInt(name + "/frameInterval")),
	timeSinceLastFrame(0),
	frameWidth(image1[0]->getWidth()),
	frameHeight(image1[0]->getHeight())
{
	images = image1;
}

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s)
	:Drawable(s),
	images(s.images),
	image1(s.image1),
	image2(s.image2),
	worldWidth(s.worldWidth),
	worldHeight(s.worldHeight),
	currentFrame(s.currentFrame),
	numberOfFrames(s.numberOfFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
	frameWidth(s.frameWidth),
	frameHeight(s.frameHeight)
{

}

void TwoWayMultiSprite::draw() const {
	Uint32 x = static_cast<Uint32>(getX());
	Uint32 y = static_cast<Uint32>(getY());
	getimagesBasedOnDirection()[currentFrame]->draw(x, y);
}

void TwoWayMultiSprite::update(Uint32 ticks) {
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks)* 0.001;
	setPosition(getPosition() + incr);

	if (getY() < 0) {
		setVelocityY(fabs(getVelocityY()));
	}
	if (getY() > worldHeight - frameHeight) {
		setVelocityY(-fabs(getVelocityY()));
	}

	if (getX() < 0) {
		setVelocityX(fabs(getVelocityX()));
	}
	if (getX() > worldWidth - frameWidth) {
		setVelocityX(-fabs(getVelocityX()));
	}
}
