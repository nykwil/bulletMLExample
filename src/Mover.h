#pragma once

#include "Common.h"

class Mover 
{
protected:
    Mover(double x, double y, double d, double s, SDL_Color c);

public:
    virtual ~Mover() {};

    virtual void tick();
    virtual void draw(SDL_Renderer* renderer);

    double x, y;
    double d, s;
    SDL_Color col;
	bool dead;
};

class Shot : public Mover 
{
public:
    Shot(double x, double y, double d, double s);
};
