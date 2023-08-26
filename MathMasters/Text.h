 #include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "MathMasterError.hpp"

#pragma once

#define ARIAL 0

class GText
{
public:

	GText(SDL_Renderer* renderer, std::vector<TTF_Font*>*Fonts);
	~GText();
	inline SDL_Texture* GetTexture() { return TextTexture; }
	inline std::string* GetText() { return &Text; }
	inline bool InitRenderer(SDL_Renderer* Renderer) { this->Renderer = Renderer; return Renderer;}
	SDL_Texture* LoadText(std::string Text, int Font,  SDL_Color color);
	static SDL_Texture* LoadText(SDL_Renderer* Renderer, std::string Text, TTF_Font* Font, SDL_Color color);

	SDL_Rect Rect;

private:

	std::string Text;
	std::vector <TTF_Font*> *Fonts;
	SDL_Texture* TextTexture;
	SDL_Renderer* Renderer;

};

TTF_Font* LoadFont(std::string Path, int Size);
void DefaultSize(std::string Text, SDL_Rect& Rect);