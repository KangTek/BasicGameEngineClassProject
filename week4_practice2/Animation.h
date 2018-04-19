#pragma once

#include <SDL.h>
class Animation
{
public:
	//basic information we need
	int numberOfFrames;
	int frameWidth, frameHeight;
	float frameDuration; // how long a frame stays on screen for
	SDL_Texture * spriteSheet;
	SDL_Renderer * renderer;

	//current state of animation
	int currentFrame;
	float frameTimer;

	Animation(SDL_Texture * spriteSheet, SDL_Renderer * renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);

	void update(float dt);
	void draw(int x, int y);
	void draw(int x, int y, float scale);
	void draw(int x, int y, bool flip);
	void Animation::draw(int x, int y, float scale, bool flip);
};