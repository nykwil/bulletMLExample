#pragma once

#include "Common.h"
#include "Mover.h"

class Ship;

#define NUM_BUTTONS 4

class Controller
{
public:
    Controller(Ship* ship, int id);
    virtual ~Controller();
    virtual void tick();

protected:
    Ship* mShip;
    int iID;
};

class PlayerController : public Controller
{
public:
    PlayerController(Ship* ship, int id);
    virtual ~PlayerController();
    virtual void tick();

protected:
    int nextShot;
	SDL_Joystick* mStick;
	SDL_Keycode idU;
	SDL_Keycode idD;
	SDL_Keycode idL;
	SDL_Keycode idR;
	SDL_Keycode idB[NUM_BUTTONS];
	int buttons[NUM_BUTTONS];
};

class BossController : public Controller
{
public:
    BossController(Ship* ship, int id);
    virtual ~BossController();
    virtual void tick();

protected:
    vector<int> mTime;
    vector<int> mNextShot;
};




