#include <SDL.h>
#include <string>
#include <cstring>

#pragma once

class GWindow
{
public:

	GWindow();
	~GWindow();
	inline SDL_Window* GetWindow() { return Window; }
	inline SDL_Renderer* GetRenderer() { return Renderer; }
	bool InitWindow(std::string title,int x,int y, int w, int h, Uint32 FLAGS);
	bool InitRenderer(int index, Uint32 FLAGS);

	int
		X_SCRREN,
		Y_SCREEN,
		WIDTH_SCREEN,
		HEIGHT_SCREEN,
		Index;
	Uint32
		WindowFLAGS,
		RendererFLAGS;

private:
	//Window variables
	SDL_Window* Window;

	//Renderer variables
	SDL_Renderer* Renderer;
};

