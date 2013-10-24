#include "Mover.h"

Mover::Mover(double x0, double y0, double d0, double s0, SDL_Color c)
: x(x0), y(y0), d(d0), s(s0), col(c)
{}

void Mover::tick() 
{
    x += s * sin(d);
    y -= s * cos(d);
}

void Mover::draw(SDL_Renderer* renderer) 
{
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

	SDL_Rect rect;
	rect.x = (int)x-3; rect.y = (int)y-3; rect.w = 6; rect.h = 6;
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Color gColBlue = { 0, 0, 255};

Shot::Shot(double x, double y, double d, double s) : Mover(x, y, d, s, gColBlue)
{}
