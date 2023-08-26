#include "Window.h"



GWindow::GWindow() : X_SCRREN{} ,
Y_SCREEN {},
WIDTH_SCREEN{},
HEIGHT_SCREEN{},
WindowFLAGS{},
Index{},
RendererFLAGS{}
{
	// constructor
}

GWindow::~GWindow()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
}

bool GWindow::InitWindow(std::string title, int x, int y, int w, int h, Uint32 FLAGS)
{
	X_SCRREN = x;
	Y_SCREEN = y;
	WIDTH_SCREEN = w;
	HEIGHT_SCREEN = h;
	WindowFLAGS = FLAGS;
	Window = SDL_CreateWindow(title.c_str(), x, y, w, h, FLAGS);
	if (Window == nullptr) {
		return false;
	}
	return true; // success
}

bool GWindow::InitRenderer(int index, Uint32 FLAGS)
{
	Index = index;
	RendererFLAGS = FLAGS;
	Renderer = SDL_CreateRenderer(Window, index, FLAGS);
	if (Renderer == nullptr) {
		return false;
	}
	return true; // success
}
