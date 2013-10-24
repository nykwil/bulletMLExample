#include "Main.h"
#include "Common.h"
#include "Ship.h"
#include "Controller.h"
#include "Mover.h"
#include <SDL.h>
#include <stdio.h>
#include <string>

using namespace std;

int turn;

class Game
{
public:
	void init();
	void draw(SDL_Renderer* renderer);
	void tick();
	void close();

	Ship* ship1;
	Ship* ship2;
	Controller* controller1;
	Controller* controller2;
};

void Game::init() 
{
    turn = 0;

	ship1 = new PlayerShip(150, 350);
	controller1 = new PlayerController(ship1, 0);

	ship2 = new BossShip(150, 50);
    controller2 = new BossController(ship2, 1);

	ship1->mEnemy = ship2;
	ship2->mEnemy = ship1;
}

void Game::tick()
{
	controller1->tick();
	controller2->tick();
	ship1->tick();
	ship2->tick();
}

void Game::draw(SDL_Renderer* renderer)
{
	ship1->draw(renderer);
	ship2->draw(renderer);

	turn++;
}

void Game::close()
{
	delete controller1;
	delete ship1;

	delete controller2;
	delete ship2;
}


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) {
			printf("Warning: VSync not enabled!");
		}

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Uint32 mTimeLastFrame = 0;
Uint32 mTimeAcumulator = 0;

Uint32 gDesiredFrameTime = (Uint32)(1.f / 30.f * 1000.f);

int main(int argc, char* args[])
{
	Game game;

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		game.init();

		bool quit = false;
		while (!quit) {
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) 
					quit = true;
			}

			Uint32 timeCurrentFrame = SDL_GetTicks();
			Uint32 timeSinceLastFrame = timeCurrentFrame - mTimeLastFrame;
			mTimeLastFrame = timeCurrentFrame;
			mTimeAcumulator += timeSinceLastFrame;

			while (mTimeAcumulator >= gDesiredFrameTime) {
				game.tick();
				mTimeAcumulator -= gDesiredFrameTime;
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			game.draw(gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}

	game.close();

	//Free resources and close SDL
	close();

	return 0;
}