#include "Window.h"
#include "Keyboard.h"
#include <SDL_image.h>
#include "MathMasterError.hpp"
#include "GamemodeGeneralPractise.h"
#include <stdexcept>


GWindow Window;
SDL_Event Event;
bool running = true;

void EventPoll();  
void Exit();

// main loop entry
int main(int argc, char *argv []) {
	
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING)) {
			SDL_Log("SDL didn't initialize");
			throw MMerr::SDL_Init;
		}
		if (TTF_Init()) {
			SDL_Log("TTF didn't initialize");
			throw MMerr::TTF_Init;
		}
		if (IMG_Init(IMG_INIT_PNG)) {
			SDL_Log("IMG didn't initialize");
			//throw MMerr::IMG_Init;
		}

		if (!Window.InitWindow("MathMasters", 0, 0, 1920, 1080, NULL)) {
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
			throw MMerr::Window_Init;
		}
		if (!Window.InitRenderer(-1, SDL_RENDERER_ACCELERATED)) {
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
			throw MMerr::Renderer_Init;
		}

	}
	catch (MMerr& error) {
		std::terminate();
	}


	GGamemodeGeneralPractise TestGamemode(Window.GetRenderer());

	 TestGamemode.MainGame();


	//game loop
	while (running) {

		//event
		EventPoll();
		
		//update

		//render
		SDL_RenderClear(Window.GetRenderer());
		SDL_SetRenderDrawColor(Window.GetRenderer(), 255, 255, 255, 255);
		SDL_RenderPresent(Window.GetRenderer());

	}



	Exit();
	return 0;
}

void EventPoll() {
	SDL_PollEvent(&Event);
	switch (Event.type) {
	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}
	switch (Event.key.keysym.sym) {
	case SDLK_q:
	case SDLK_ESCAPE:
		running = false;
		break;
	default:
		break;
	}

}

void Exit() {
	Window.~GWindow();
}