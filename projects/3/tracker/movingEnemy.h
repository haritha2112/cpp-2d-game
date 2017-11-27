#ifndef MOVINGENEMY_H
#define MOVINGENEMY_H

#include "multisprite.h"

class MovingEnemy : public MultiSprite {
public:
	MovingEnemy( const std::string& name, const Vector2f& pos, int w, int h );
	MovingEnemy(const MovingEnemy&);
	MovingEnemy& operator=(const MovingEnemy&);
	
	virtual void update(Uint32 ticks);
	void setPlayerPos(const Vector2f& p) { playerPos = p; }
private:
	enum MODE {NORMAL, PURSUE};
	Vector2f playerPos;
	int playerWidth;
	int playerHeight;
	MODE currentMode;
	float safeDistance;
	int viewWidth;
	int viewHeight;
	int worldWidth;
	int enemyWidth;
	int enemyRange;

	void goUp(Uint32 ticks);
	void goDown(Uint32 ticks);
};
#endif
