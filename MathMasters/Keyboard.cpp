#include "Keyboard.h"

GKeyboard::GKeyboard() :
	Renderer(nullptr), Event(), Fonts(nullptr), TextTextures(), Text{ "" }, typing{ true }, MaxTextSize{ 9 },
	Typer(), Color{0,0,0,0}, Rect{0,0,0,0}, Font{ARIAL}, SpaceBeetwenLetters{95}, Timer{}, NotBlinkingTime{500}
{
	TyperUpdate();
}

GKeyboard::GKeyboard(SDL_Renderer* Renderer, std::vector<TTF_Font*>*Fonts, SDL_Event* Event) :
	Renderer(Renderer), Event(Event), Fonts(Fonts), TextTextures(), Text{ "" }, typing{ true }, MaxTextSize{ 9 }, 
	Typer(), Color{ 0,0,0,0 }, Rect{ 0,0,0,0 }, Font{ ARIAL }, SpaceBeetwenLetters{ 95 }, Timer {}, NotBlinkingTime{ 500 }
{
	GText Text(Renderer, Fonts);
	DefaultSize("1", Rect);
	for (int i = 0; i <= 10; i++) {
		TextTextures.push_back(Text.LoadText(std::to_string(i), Font, Color));
	}
	TyperUpdate();
}

GKeyboard::~GKeyboard()
{
	for (SDL_Texture* Texture : TextTextures) {
		SDL_DestroyTexture(Texture);
	}
}

void GKeyboard::Init(SDL_Renderer* Renderer, std::vector<TTF_Font*>* Fonts, SDL_Event* Event)
{
	this->Renderer = Renderer;
	this->Fonts = Fonts;
	this->Event = Event;
	GText Text(Renderer, Fonts);
	DefaultSize("1", Rect);
	for (int i = 0; i <= 10; i++) {
		TextTextures.push_back(Text.LoadText(std::to_string(i), Font, Color));
	}
}

void GKeyboard::Update()
{
	if (!typing) return;
	//SDL_PollEvent(Event);
	if (Event->type == SDL_KEYDOWN) {
		switch (Event->key.keysym.sym) {
		case SDLK_RETURN:
			if (Text.size() != 0) {
				typing = false;
			}
			break;
		case SDLK_DELETE:
		case SDLK_BACKSPACE:
			if (Text.size() > 0) {
				Text.pop_back();
				Typer.x -= SpaceBeetwenLetters;
				Timer = SDL_GetTicks();
			}
			break;
		case SDLK_0:
			if (Text.size() == 0) break;
		case SDLK_1:
		case SDLK_2:
		case SDLK_3:
		case SDLK_4:
		case SDLK_5:
		case SDLK_6:
		case SDLK_7:
		case SDLK_8:
		case SDLK_9:
			if (Text.size() != MaxTextSize) {
				Text += std::to_string((int)Event->key.keysym.sym - 48);
				Typer.x += SpaceBeetwenLetters;
				Timer = SDL_GetTicks();
			}
			break;
		default:
			break;
		}
	}
	     

}

void GKeyboard::Render()
{
	//Keyboard render
	int start_pos = Rect.x;
	if (Text.size() != 0) {
		for (int i = 0; i < Text.size(); i++) {
			SDL_RenderCopy(Renderer, TextTextures[((int)Text[i]) - 48], NULL, &Rect);
			Rect.x += SpaceBeetwenLetters;
		}
		
	}
	Rect.x = start_pos;
	//Typer renderer
	SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
	uint32_t Ticks = SDL_GetTicks();
	if (Ticks - Timer < NotBlinkingTime) {
		SDL_RenderFillRectF(Renderer, &Typer);
	}
	else if (Ticks % 1000 < 500) {
		SDL_RenderFillRectF(Renderer, &Typer);
	}
}

void GKeyboard::ResetText()
{
	Text = "";
	TyperUpdate();
}

void GKeyboard::TyperUpdate()
{
	Typer.x = Rect.x + Rect.h * 0.2;
	Typer.w = 10;
	Typer.y = Rect.y;
	Typer.h = Rect.h - Rect.h * 0.2;

}
