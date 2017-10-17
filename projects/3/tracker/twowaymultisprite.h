#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class TwoWayMultiSprite : public Drawable {
public:
	TwoWayMultiSprite(const std::string&, const std::string&, const std::string&);
	TwoWayMultiSprite(const TwoWayMultiSprite&);
	//virtual ~TwoWayMultiSprite();

	virtual void draw() const;
	virtual void update(Uint32 ticks);
	
	virtual const Image* getImage() const;
	const std::vector<Image *> getimagesBasedOnDirection() const;

protected:
	std::vector<Image *> images;
	const std::vector<Image *> image1;
	const std::vector<Image *> image2;
	int worldWidth;
	int worldHeight;

	unsigned currentFrame;
	unsigned numberOfFrames;
	unsigned frameInterval;
	float timeSinceLastFrame;
	int frameWidth;
	int frameHeight;

	void advanceFrame(Uint32 ticks);
	TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};
#endif