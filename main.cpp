#include "main.h"

int main(int argc, char **argv) {
	
	PATH = (char*) malloc(sizeof(argv[0]));
	std::string full = argv[0];
	std::string temp = (char*) strrchr(argv[0], '\\');
	strncpy(PATH, argv[0], full.length() - temp.length());

	bool running = true;
	Life* world = new Life();
	Screen* screen = new Screen();

	screen->draw(world->WorldGrid);

	Uint32 last_tick = SDL_GetTicks();

	while(running) {
		SDL_Event Event;
		if(SDL_PollEvent(&Event))
			OnEvent(&Event, &running);

		world->update();
		screen->draw(world->WorldGrid);
		//SDL_Delay(1000/FPS);
	}

	return 0;
}