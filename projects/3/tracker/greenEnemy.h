#ifndef GREENENEMY_H
#define GREENENEMY_H

#include "multisprite.h"

class GreenEnemy : public MultiSprite {
public:
	GreenEnemy( const std::string& name, const Vector2f& pos, int w, int h );
	GreenEnemy(const GreenEnemy&);
	virtual void update(Uint32 ticks);

	GreenEnemy& operator=(const GreenEnemy&);
	void setPlayerPos(const Vector2f& p) { playerPos = p; }
private:
	enum MODE {NORMAL, PURSUE};
	Vector2f playerPos;
	int playerWidth;
	int playerHeight;
	MODE currentMode;
	float safeDistance;

	void goUp(Uint32 ticks);
	void goDown(Uint32 ticks);
};
#endif
