#pragma once

#include "Common.h"
#include "Mover.h"
#include "BulletManager.h"

class BulletMLParser;

class Ship : public Mover 
{
public:
    Ship(double x_, double y_);

    virtual void tick();
    virtual void fire(int i) = 0;
    virtual void hit(Mover* hit) = 0;

    double velocityX;
    double velocityY;

    Mover* mEnemy;
    Mover* freeTarget;
};

class BossShip : public Ship
{
public:
    BossShip(double x_, double y_);
    ~BossShip();

    virtual void fire(int i);
    virtual void hit(Mover* hit);
    virtual void tick();
    virtual void draw(SDL_Renderer* renderer);

    BulletManager bulletManager;
    std::vector<BulletMLParser*> mBulletParsers;
};

class PlayerShip : public Ship
{
public:
    PlayerShip(double x_, double y_);
    ~PlayerShip();

    virtual void fire(int i);
    virtual void hit(Mover* hit);
    virtual void tick();
    virtual void draw(SDL_Renderer* renderer);

    BulletManager bulletManager;
    std::vector<BulletMLParser*> mBulletParsers;
};
