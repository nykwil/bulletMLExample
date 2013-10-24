#pragma once

#include "common.h"
#include "Mover.h"

class BulletMLState;
class BulletMLParser;
class BulletCommand;

class Ship;

class BulletManager
{
public:
	BulletManager();
	std::vector<BulletCommand*> mCommands;
	std::vector<Shot*> mShots;
	std::vector<Shot*> mPool;

	BulletCommand* createBullet(BulletMLState* state, double x, double y, double d, double s, Mover* target);
	BulletCommand* createBullet(BulletMLParser* parser, Mover* origin, Mover* target);
	Shot* createProjectile(double x, double y,double d, double s);
	void destroyProjectile(Shot* projectile);

	void tick();
	void draw(SDL_Renderer* renderer);
    void checkCollision(Ship* target, double hitDistSq);
};
