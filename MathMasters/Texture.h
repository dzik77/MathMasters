 #include <SDL.h>
#include <SDL_image.h>
#include <string>

#pragma once


class GTexture
{

public:
	GTexture();
	GTexture(SDL_Renderer* renderer);
	~GTexture();
	inline SDL_Texture* GetTexture() { return Texture;  }
	inline bool InitRenderer(SDL_Renderer* Renderer) { this->Renderer = Renderer; return Renderer; }
	SDL_Texture* IMG_LoadTexture(std::string path);
	SDL_Texture* BMP_LoadTextue(std::string path);
	SDL_Rect Rect;

private:
	
	SDL_Texture* Texture;
	SDL_Renderer* Renderer;

};

