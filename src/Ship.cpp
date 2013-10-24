#include "Ship.h"
#include "BulletManager.h"

#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml.h"

SDL_Color gColRed = {255, 0, 0};

Ship::Ship(double x_, double y_) : Mover(x_, y_, 0, 0, gColRed )
{
	freeTarget = new Shot(x, y, d, s);
	mEnemy = 0;
	dead = false;
    velocityX = 0;
    velocityY = 0;
}

void Ship::tick() 
{
	x += velocityX;
	y += velocityY;
}

PlayerShip::PlayerShip(double x_, double y_) : Ship(x_, y_)
{

}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::fire( int i )
{
    bulletManager.createProjectile(x, y, 0, 10); 

    /*
    if (mEnemy == 0)
        bulletManager.createBullet(mBulletParsers[i], this, freeTarget);
    else
        bulletManager.createBullet(mBulletParsers[i], this, mEnemy);
        */
}

void PlayerShip::hit( Mover* hit )
{
    hit->dead = true;
}

void PlayerShip::tick()
{
    __super::tick();
    bulletManager.tick();
    if (bulletManager.mShots.size() > 0)
        bulletManager.checkCollision(static_cast<Ship*>(mEnemy), 20);
}

void PlayerShip::draw(SDL_Renderer* renderer)
{
    __super::draw(renderer);
    bulletManager.draw(renderer);
}

BossShip::BossShip(double x_, double y_) : Ship(x_, y_)
{
    mBulletParsers.push_back(new BulletMLParserTinyXML("xml/[Progear]_round_1_boss_grow_bullets.xml"));
    mBulletParsers.push_back(new BulletMLParserTinyXML("xml/[XEVIOUS]_garu_zakato.xml"));
    mBulletParsers.push_back(new BulletMLParserTinyXML("xml/[Psyvariar]_X-B_colony_shape_satellite.xml"));
    mBulletParsers.push_back(new BulletMLParserTinyXML("xml/[Progear]_round_3_boss_wave_bullets.xml"));

    for (uint i = 0; i < mBulletParsers.size(); ++i)
    {
        mBulletParsers[i]->parse();
    }
    velocityX = 1;
    velocityY = 0.1f;
}

BossShip::~BossShip()
{
    for (int i = 0; i < mBulletParsers.size(); ++i)
    {
        delete mBulletParsers[i];
    }
}

void BossShip::fire( int i )
{
    if (mEnemy == 0)
        bulletManager.createBullet(mBulletParsers[i], this, freeTarget);
    else
        bulletManager.createBullet(mBulletParsers[i], this, mEnemy);
}

void BossShip::hit( Mover* hit )
{
    hit->dead = true;
}

void BossShip::tick()
{
    __super::tick();
    bulletManager.tick();
    bulletManager.checkCollision(static_cast<Ship*>(mEnemy), 5);
}

void BossShip::draw(SDL_Renderer* renderer)
{
    __super::draw(renderer);
    bulletManager.draw(renderer);
}