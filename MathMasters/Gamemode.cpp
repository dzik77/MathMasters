#include "Gamemode.h"

GGamemode::GGamemode() : Renderer(nullptr), Event(), Inputs(2, 0), InputsTexture(), Answer{0},
inputsizes{ InputSizes::Intermiadiate }, Keyboard(), Fonts(), Operators(3, false),
OperatorsTexture(), OperatorPos{ 0,0,0,0 }, RandomOperator{ 0 }, CorrectAnswer{ 0 }
{
	srand(time(NULL));
	Fonts.push_back(LoadFont("Fonts\\arial.ttf", 100));
	if (!Fonts[0]) SDL_Log(SDL_GetError());
}

GGamemode::GGamemode(SDL_Renderer* Renderer) : Renderer(Renderer), Event(), Inputs(2, 0), InputsTexture(2, GText(Renderer, &Fonts)), Answer{0},
inputsizes{ InputSizes::Intermiadiate }, Keyboard(), Fonts(), Operators(3, false),
OperatorsTexture(3, GText(Renderer, &Fonts)), OperatorPos{0,0,0,0}, RandomOperator{0}, CorrectAnswer{ 0 }
{
	if (OperatorsTexture.size() < 3 && Inputs.size() < 2 && Operators.size() < 3)
		std::exit(EXIT_FAILURE);
	srand(time(NULL));
	Fonts.push_back(LoadFont("Assets\\Fonts\\arial.ttf", 100));
	if (!Fonts[0]) SDL_Log(SDL_GetError());
	Keyboard.Init(Renderer, &Fonts, &Event);
}

GGamemode::~GGamemode()
{
	
}

void GGamemode::Init(SDL_Renderer* Renderer)
{
	this->Renderer = Renderer;
	Keyboard.Init(Renderer, &Fonts,&Event);
	OperatorsTexture = std::vector(3, GText(Renderer, &Fonts));
	InputsTexture = std::vector(2, GText(Renderer, &Fonts));
}

void GGamemode::MenuOperationsChoose()
{
	std::vector<bool> MenuHandler(3, false);
	int Option{};
	OperatorsTexture[0].LoadText("+", ARIAL, { 0,0,0,0 });
	OperatorsTexture[1].LoadText("-", ARIAL, { 0,0,0,0 });
	OperatorsTexture[2].LoadText("*", ARIAL, { 0,0,0,0 });

	int move = 300;
	for (GText& Text : OperatorsTexture) {
		Text.Rect.x = move;
		Text.Rect.y = 400;
		DefaultSize(*Text.GetText(), Text.Rect);
		move += 150;
	}

	GMenuInputHandler InputHandler(MenuHandler);

	while (!InputHandler.choosen) {

		//update
		MenuHandler = InputHandler.MenuEventMultiple();
		Option = InputHandler.GetOption();

		//render
		SDL_RenderClear(Renderer);
		for(int i = 0; i < OperatorsTexture.size(); i++)
		SDL_RenderCopy(Renderer, OperatorsTexture[i].GetTexture(), NULL, &OperatorsTexture[i].Rect);
		if (!MenuHandler[Option]) SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		else SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
		SDL_RenderPresent(Renderer);

	}

	Operators = MenuHandler;
}

void GGamemode::MenuDifficultyChoose()
{

	int Option{};

	std::vector <GText> Difficulty(6, GText(Renderer, &Fonts));
	Difficulty[0].LoadText("Very Easy", ARIAL, { 0,0,0,0 });
	Difficulty[1].LoadText("Easy", ARIAL, { 0,0,0,0 });
	Difficulty[2].LoadText("Medium", ARIAL, { 0,0,0,0 });
	Difficulty[3].LoadText("Hard", ARIAL, { 0,0,0,0 });
	Difficulty[4].LoadText("Very Hard", ARIAL, { 0,0,0,0 });
	Difficulty[5].LoadText("Demon", ARIAL, { 0,0,0,0 });
	for (GText& Text : Difficulty) {
		Text.Rect.x = 800;
		Text.Rect.y = 400;
		DefaultSize(*Text.GetText(), Text.Rect);
	}

	GMenuInputHandler InputHandler(Difficulty.size());

	while (!InputHandler.choosen) {
		
		//update
		Option = InputHandler.MenuEventSingle();

		//render
		SDL_RenderClear(Renderer);
		SDL_RenderCopy(Renderer, Difficulty[Option].GetTexture(), NULL, &Difficulty[Option].Rect);
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		SDL_RenderPresent(Renderer);

	}

	switch (Option) {
	case 0:
		inputsizes = InputSizes::VeryEasy;
		break;
	case 1:
		inputsizes = InputSizes::Easy;
		break;
	case 2:
		inputsizes = InputSizes::Intermiadiate;
		break;
	case 3:
		inputsizes = InputSizes::Hard;
		break;
	case 4:
		inputsizes = InputSizes::VeryHard;
		break;
	case 5:
		inputsizes = InputSizes::Demon;
		break;
	}

}

void GGamemode::RandomInputs()
{
	for (int& Input : Inputs) {
		Input = rand() % (int)inputsizes;
	}
}

void GGamemode::RandomOperators()
{
	std::vector<int> ChoosenOperators;
	for (int i = 0; i < Operators.size(); i++)
		if (Operators[i]) ChoosenOperators.push_back(i);
	RandomOperator = ChoosenOperators[rand() % ChoosenOperators.size()];
}

void GGamemode::CalculateAnswer()
{
	switch (RandomOperator) {
	case OperatorPlus:
		CorrectAnswer = Inputs[0] + Inputs[1];
		break;
	case OperatorMinus:
		CorrectAnswer = Inputs[0] - Inputs[1];
		break;
	case OperatorMultiplication:
		CorrectAnswer = Inputs[0] * Inputs[1];
		break;
	}
}

void GGamemode::LoadInputs()
{
	for (int i = 0; i < InputsTexture.size(); i++) {
		InputsTexture[i].LoadText(std::to_string(Inputs[i]), ARIAL, { 0,0,0,0 });
		if (!InputsTexture[i].GetTexture())
			SDL_Log("Not loaded");
		SDL_Log(SDL_GetError());
		DefaultSize(std::to_string(Inputs[i]), InputsTexture[i].Rect);
	}
	DefaultSize("1", OperatorPos);
	OperatorPos.y = InputsTexture[0].Rect.y;
	OperatorPos.x = InputsTexture[0].Rect.x + InputsTexture[0].Rect.w + 50;
}

/*
void GGamemode::Init(SDL_Renderer* Renderer, int Font, int Size, SDL_Color Color)
{
	Keyboard.InitRenderer(Renderer);
	this->Font = Font;
	this->Size = Size;
	this->Color = Color;
	this->Renderer = Renderer;
	srand(time(NULL));
	GText Operation(this->Renderer);
	Operations[0] = Operation.LoadText("+", this->Font, this->Size, this->Color);
	Operations[1] = Operation.LoadText("-", this->Font, this->Size, this->Color);
	Operations[2] = Operation.LoadText("*", this->Font, this->Size, this->Color);
	for (int i = 0; i < InputsSize; i++) Inputs.push_back(0);
	
}
*/

