#ifndef GREENENEMY_H
#define GREENENEMY_H

#include "multisprite.h"

class GreenEnemy : public MultiSprite {
public:
	GreenEnemy(const std::string&);
	GreenEnemy(const GreenEnemy&);
	virtual void update(Uint32 ticks);

	GreenEnemy& operator=(const GreenEnemy&);
};
#endif
