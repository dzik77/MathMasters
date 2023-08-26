#include "Texture.h"

GTexture::GTexture() : Texture{ nullptr }, Renderer{ nullptr }, Rect()
{
}

GTexture::GTexture(SDL_Renderer* renderer) : Texture{ nullptr }, Renderer{renderer} , Rect()
{
	if (!renderer) SDL_Log("Invalid Renderer");
	// constructor 
}

GTexture::~GTexture()
{
	SDL_DestroyTexture(Texture);
}

SDL_Texture* GTexture::IMG_LoadTexture(std::string path) {

	SDL_Surface* Surf = IMG_Load(path.c_str());
	Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
	SDL_FreeSurface(Surf);

	return Texture;
}

SDL_Texture* GTexture::BMP_LoadTextue(std::string path) {

	SDL_Surface* Surf = SDL_LoadBMP(path.c_str());
	Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
	SDL_FreeSurface(Surf);

	return Texture;

}
