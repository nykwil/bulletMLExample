#include "Controller.h"
#include "Ship.h"

Controller::Controller(Ship* ship, int id) 
{
	mShip = ship;
	iID = id;
}

Controller::~Controller()
{
}

void Controller::tick() 
{
}

PlayerController::PlayerController( Ship* ship, int id ) : Controller(ship, id)
{
    mStick = SDL_JoystickOpen(iID);
    if (iID == 0)
    {
        idU = SDL_SCANCODE_UP;
        idD = SDL_SCANCODE_DOWN;
        idL = SDL_SCANCODE_LEFT;
        idR = SDL_SCANCODE_RIGHT;
        idB[0] = SDL_SCANCODE_U;
        idB[1] = SDL_SCANCODE_I;
        idB[2] = SDL_SCANCODE_O;
        idB[3] = SDL_SCANCODE_P;
    }
    else
    {
        idU = SDL_SCANCODE_W;
        idD = SDL_SCANCODE_S;
        idL = SDL_SCANCODE_A;
        idR = SDL_SCANCODE_D;
        idB[0] = SDL_SCANCODE_H;
        idB[1] = SDL_SCANCODE_J;
        idB[2] = SDL_SCANCODE_K;
        idB[3] = SDL_SCANCODE_L;
    }

    buttons[0] = 0;
    buttons[1] = 0;
    buttons[2] = 0;
    buttons[3] = 0;

    nextShot = 0;
}

void PlayerController::tick()
{
    Controller::tick();

    --nextShot;

	double x = 0;
    double y = 0;

	int ifire = -1;

    if (mStick) {
        x = ((float)SDL_JoystickGetAxis(mStick, 0) - 0.5f) / 32767.5f;
        y = ((float)SDL_JoystickGetAxis(mStick, 1) - 0.5f) / 32767.5f;
        for (int i = 0; i < NUM_BUTTONS; ++i) {
            if (SDL_JoystickGetButton(mStick, buttons[i]) && nextShot <= 0) {
                ifire = i;
                break;
            }
        }
    }
    else {
		const Uint8* ks = SDL_GetKeyboardState(0);
        if (ks[idU]) 
            y = -2;
        else if (ks[idD]) 
            y = 2;

		if (ks[idR]) 
            x = 2;
        else if (ks[idL]) 
            x = -2;

		for (int i = 0; i < NUM_BUTTONS; ++i) {
            if (ks[idB[i]] && nextShot <= 0) {
                ifire = i;
                break;
            }
        }
    }

	if (ifire >= 0) {
		mShip->fire(ifire);
		nextShot = 20;
	}

    mShip->velocityX = x;
    mShip->velocityY = y;
}

PlayerController::~PlayerController()
{
    SDL_JoystickClose(mStick);
}

BossController::BossController( Ship* ship, int id ) : Controller(ship, id)
{
    mNextShot.push_back(0);
    mTime.push_back(800);
    mNextShot.push_back(200);
    mTime.push_back(800);
    mNextShot.push_back(400);
    mTime.push_back(800);
    mNextShot.push_back(600);
    mTime.push_back(800);
}

void BossController::tick()
{
    Controller::tick();

    if (mShip->x > 200)
         mShip->velocityX = -0.5;
     else if (mShip->x < 100)
         mShip->velocityX = 0.5;

    if (mShip->y > 60)
        mShip->velocityY = -0.1f;
    else if (mShip->y < 40)
        mShip->velocityY = 0.1f;

    for (uint i = 0; i < mNextShot.size(); ++i) {
        mNextShot[i]--;
        if (mNextShot[i] <= 0) {
            mShip->fire(i);
            mNextShot[i] = mTime[i];
        }
    }
}

BossController::~BossController()
{

}