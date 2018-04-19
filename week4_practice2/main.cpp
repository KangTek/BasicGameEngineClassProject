//This program contains Task1 and Task2
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include <list>

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Window* m_pWindow = NULL; SDL_Renderer* m_pRenderer;// New data member for drawing
SDL_Texture* m_pTexture = NULL;
SDL_Rect m_sourceRectangle;
SDL_Rect m_destinationRectangle;

int main(int lashiren, char **chishiren)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "failed to initialize !!!!!!!\n";
		return -1;
	}
	else
	{
		cout << "succeed in initializing !!!!! \n";
	}

	window = SDL_CreateWindow("Practice1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (window != NULL)
	{
		cout << "Window created! \n";
	}
	else
	{
		cout << "Failed to create window!\n";
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL)
	{
		cout << "renderer created ! \n";
	}
	else
	{
		cout << "Failed to create renderer!\n";
		return -1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}


	//SDL_Delay(5000);

	//Load an image using
	SDL_Texture *spriteSheet = IMG_LoadTexture(renderer, "assets/run.png");

	//m_sourceRectangle.w = 32;
	//m_sourceRectangle.h = 32;
	SDL_Rect runClipRect = { 0, 0, 32, 32 };
	SDL_Rect runDestRect = { 0, 0, 640, 480 };

	SDL_Surface * runSurface = IMG_Load("assets/run.png");

	//params: surface, 1/0 to set or unset color key, rgb value to make colour key. mapRGB just does its best to find closest match to a surfaces pixel formate e.g 8bit, 16bit, 32bit and what colours are in that set
	SDL_SetColorKey(runSurface, 1, SDL_MapRGB(runSurface->format, 128, 128, 255));

	//now convert to texture
	SDL_Texture * runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);
	//free the surface: 0
	SDL_FreeSurface(runSurface);

	//new texture for task2
	SDL_Texture * deerSpriteSheet = IMG_LoadTexture(renderer, "assets/deer.png");

	//Animation Object
	Animation anim1(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.1);
	Animation anim2(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.2);
	Animation anim3(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.3);
	Animation anim4(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.5);
	Animation anim5(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.4);
	//this anim6 is for task2
	Animation anim6(deerSpriteSheet, renderer, 7, 279, 456, 0.1);

	//setup time stuff
	Uint32 lastUpdate = SDL_GetTicks();// set last update to current time(millisecond  to reach this bit of code)

	list<Entity*> entities;
	Hero* hero = new Hero();
	hero->setAnimation(&anim1);
	hero->setRenderer(renderer);
	hero->setXY(30,200);
	//add our hero to the list
	entities.push_back(hero);


	bool loop = true;
	while (loop)
	{
		//The time range
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert into deltaTime(decimal)
		float DT = timeDiff / 1000.0;
		//Now update lastUpdate to the current time so the next loop calculates correctly
		lastUpdate = SDL_GetTicks();
		//set drawing color for the renderer, numbers are: RGBA(alpha, transparency). All values between 0-255
		SDL_SetRenderDrawColor(renderer, 255, 0, 168, 255);
		//clear screen with current draw color
		SDL_RenderClear(renderer);
		//TODO draw stuff to renderer here, like game images, colours, ui whatever
		//set drawing color to babyblue
		SDL_SetRenderDrawColor(renderer, 214, 144, 14, 255);
		//draw current frame to screen
		//SDL_RenderCopy(renderer, spriteSheet,&runClipRect,&runDestRect);

		//update animation
		/*
		anim1.update(DT);
		anim2.update(DT);
		anim3.update(DT);
		anim4.update(DT);
		anim5.update(DT);
		anim6.update(DT);

		//draw from animations
		anim1.draw(50, 300, 3.0f);
		anim2.draw(50, 100, 4.0f);
		anim3.draw(200, 300, 2.5f, true);
		anim4.draw(200, 250, 1.5f, true);
		anim5.draw(300, 300, 3.5f, true);

		anim6.draw(400, 150, 0.5f);
		*/
		for (list<Entity*>::iterator eIt = entities.begin(); eIt != entities.end(); eIt++)
		{
			(*eIt)->update(DT);
			(*eIt)->draw();
		}
		


		//Make a rectangle,ractental x,y,w,h
		//SDL_Rect rect = { 100, 50, 300, 240 };

		//SDL_RenderFillRect(renderer, &rect);

		//lets do animation stuff here
		//int const runNumOfFrame = 4;
		//runClipRect.x = runClipRect.w * int((SDL_GetTicks() / 100) % runNumOfFrame);

		//SDL_RenderCopy(renderer,spriteSheet,&runClipRect,&runDestRect);


		SDL_RenderPresent(renderer);

		if (SDL_GetTicks() > 5000)
			loop = false;
	}



	//get renderer to output to the window
	//SDL_RenderPresent(renderer);
	//SDL_Delay pauses game for x many milliseconds;
	//SDL_Delay(5000);

	//clean up any game objects
	delete hero;
	//clean up renderer and window properly (aka clean up dynamic)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down subsystems and clean up any setup it did earlier in sdl_init
	SDL_Quit();

	system("pause");
	return 0;
}