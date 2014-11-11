#include "Screen.h"

Screen::Screen() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Surf_Display = SDL_SetVideoMode((GRID_WIDTH * 1), (GRID_HEIGHT * 1), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	SDL_ShowCursor(0);
	Background_Color = SDL_MapRGB(Surf_Display->format, 255, 255, 255);
	Background_Color2 = SDL_MapRGB(Surf_Display->format, 0, 255, 127);
	Surf_Cell = this->LoadImage("cell.png");
	//Surf_False = this->LoadImage("false.png");

	this->fill(Surf_Display, Background_Color);
	SDL_Flip(Surf_Display);
}

void Screen::draw(bool** world) {
	this->fill(this->Surf_Display, this->Background_Color);
	SDL_Rect rect;
	
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			rect.w = 5;
			rect.h = 5;
			rect.y = y * 1;
			rect.x = x * 1;

			bool current = world[y][x];
			if (current == true)
				SDL_BlitSurface(this->Surf_Cell, NULL, this->Surf_Display, &rect);
		}
	}

	SDL_Flip(SDL_GetVideoSurface());
}

SDL_Surface* Screen::LoadImage(char* Filename) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	char* fullpath = (char*) malloc(sizeof(char) * 260);
	sprintf(fullpath, "%s\\%s", PATH, Filename);

	if((Surf_Temp = IMG_Load(fullpath)) == NULL)
		return NULL;

	Surf_Return = SDL_ConvertSurface(Surf_Temp, this->Surf_Display->format, 0);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

void Screen::fill(SDL_Surface* surface, Uint32 color) {
	SDL_Rect rect;

	rect.h = surface->h;
	rect.w = surface->w;
	rect.x = rect.y = 0;

	SDL_FillRect(surface, &rect, color);
}

void Screen::set_path(const char* p) {
	this->path = (char*) malloc(sizeof(p));
	std::string full = p;
	std::string temp = (char*) strrchr(p, '\\');

	strncpy(this->path, p, full.length() - temp.length());
}

void OnEvent(SDL_Event* Event, bool* Running) {
	switch(Event->type) {
	case SDL_QUIT:
		*Running = false;
	case SDL_KEYDOWN:
		SDL_KeyboardEvent* Key = &Event->key;
		if (Key->keysym.sym == SDLK_ESCAPE)
			*Running = false;
	}
}