#ifndef BOSSENEMY_H
#define BOSSENEMY_H

#include "multisprite.h"

class BossEnemy : public MultiSprite {
public:
	BossEnemy( const std::string& name );
	BossEnemy(const BossEnemy&);
	BossEnemy& operator=(const BossEnemy&);

	virtual void update(Uint32 ticks);
	virtual void reset();
	void setOriginalState() {
		setPosition(initialPosition);
		bulletsHit = 0;
	}

	void gotShot() { ++bulletsHit; }
	bool canDie() { return bulletsToDie == bulletsHit; }
private:
	int viewWidth;
	int viewHeight;
	int worldWidth;
	int worldHeight;
	int enemyWidth;
	int enemyRange;
	unsigned int bulletsToDie;
	unsigned int bulletsHit;
	Vector2f initialPosition;
};
#endif
