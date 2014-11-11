#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "Globals.h"
#include "Life.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Screen {
public:
	SDL_Surface* Surf_Display;
	SDL_Surface* Surf_Cell;
	SDL_Surface* Surf_False;
	Uint32 Background_Color;
	Uint32 Background_Color2;

	Screen();
	void draw(bool** world);
	void set_path(const char* path);
private:
	char* path;
	void fill(SDL_Surface* dest, Uint32 color);
	SDL_Surface* LoadImage(char* Filename);
};

void OnEvent(SDL_Event* Event, bool* running);

#endif