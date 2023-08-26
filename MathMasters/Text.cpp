#include "Text.h"

GText::GText(SDL_Renderer* renderer, std::vector<TTF_Font*>* Fonts) : TextTexture{ nullptr }, Rect{}, Renderer{ renderer }, Fonts{ Fonts }, Text{"Lorem ipsum"}
{
	if (!renderer) throw MMerr::Renderer_Init;
}

GText::~GText()
{
	SDL_DestroyTexture(TextTexture);
}

SDL_Texture* GText::LoadText(std::string Text,int Font, SDL_Color color)
{
	this->Text = Text;
	SDL_Surface* Surf = TTF_RenderText_Solid((*Fonts)[Font], Text.c_str(), color);
	if (!Surf) {
		SDL_Log("Surface didn't Load");
		SDL_Log(SDL_GetError());
		return nullptr;
	}
	TextTexture = SDL_CreateTextureFromSurface(Renderer, Surf);
	if (!TextTexture) {
		SDL_Log("Texture didn't Load");
		SDL_Log(SDL_GetError());
		SDL_FreeSurface(Surf);
		return nullptr;
	}

	SDL_FreeSurface(Surf);

	return TextTexture;
}

SDL_Texture* GText::LoadText(SDL_Renderer* Renderer, std::string Text, TTF_Font* Font, SDL_Color color)
{
	SDL_Surface* Surf = TTF_RenderText_Solid(Font, Text.c_str(), color);
	if (!Surf) {
		SDL_Log("Surface didn't Load");
		SDL_Log(SDL_GetError());
		return nullptr;
	}
	SDL_Texture *ReturnTexture = SDL_CreateTextureFromSurface(Renderer, Surf);
	if (!ReturnTexture) {
		SDL_Log("Texture didn't Load");
		SDL_Log(SDL_GetError());
		SDL_FreeSurface(Surf);
		return nullptr;
	}

	SDL_FreeSurface(Surf);

	return ReturnTexture;
}

TTF_Font* LoadFont(std::string Path, int Size)
{
	TTF_Font* Font = TTF_OpenFont(Path.c_str(), Size);
	if (!Font) {
		SDL_Log("Font not loaded");
		SDL_Log(SDL_GetError());
		return nullptr;
	}
	return Font;
}

void DefaultSize(std::string Text, SDL_Rect& Rect)
{
	Rect.h = 200;
	Rect.w = Text.size() * 100;
}
