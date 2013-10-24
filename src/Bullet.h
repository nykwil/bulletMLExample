#ifndef command_h_
#define command_h_

#include "bulletmlrunner.h"

class Bullet;
class Mover;
class BulletManager;

class BulletCommand : public BulletMLRunner 
{
public:
    // root bullet
    BulletCommand(BulletMLParser* parser, Mover* bullet, Mover* target, BulletManager* owner);
    // child bullet
    BulletCommand(BulletMLState* state, Mover* bullet, Mover* target, BulletManager* owner);

    virtual double getBulletDirection();
    virtual double getAimDirection();
    virtual double getBulletSpeed();
    virtual double getDefaultSpeed();
    virtual double getRank();
    virtual void createSimpleBullet(double direction, double speed);
    virtual void createBullet(BulletMLState* state, double direction, double speed);
    virtual int getTurn();
    virtual void doVanish();
    virtual void doChangeDirection(double direction);
    virtual void doChangeSpeed(double speed);
    virtual void doAccelX(double speedx);
    virtual void doAccelY(double speedy);
    virtual double getBulletSpeedX();
    virtual double getBulletSpeedY();

	bool isDead();

    // If you want to customize random generator
    //virtual double getRand();

private:
    Mover* mMover;
	Mover* mTarget;
	BulletManager* mOwner;
};

#endif // ! command_h_
