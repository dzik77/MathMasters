#include "Text.h"
#pragma once

constexpr int ZERO = 48;
constexpr int NINE = 57;

class GKeyboard
{
public:

	GKeyboard();
	GKeyboard(SDL_Renderer* Renderer, std::vector<TTF_Font*>* Fonts, SDL_Event* Event);
	~GKeyboard();
	void Init(SDL_Renderer* Renderer, std::vector<TTF_Font*>* Fonts, SDL_Event* Event);
	inline std::string* GetText() { return &Text; }
	void Update();
	void Render();
	void ResetText();
	void TyperUpdate();
	// return nullptr when user didn't ended typing or returns std::strign when user pressed enter
	bool typing;
	

	int MaxTextSize;
	int Font;
	int SpaceBeetwenLetters;
	SDL_FRect Typer;
	SDL_Color Color;
	SDL_Rect Rect;

private:
	
	SDL_Renderer* Renderer;
	SDL_Event *Event;
	std::vector<TTF_Font*>* Fonts;
	std::vector <SDL_Texture*> TextTextures;
	std::string Text;
	Uint32 Timer;
	Uint32 NotBlinkingTime;

};

