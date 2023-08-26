#include "Text.h"
#include "Texture.h"
#include "Keyboard.h"
#include "MenuInputHandler.h"
#include <vector>
#include <ctime>
#pragma once

#define OperatorPlus 0
#define OperatorMinus 1
#define OperatorMultiplication 2

class GGamemode
{
public:

	GGamemode();
	GGamemode(SDL_Renderer* Renderer);
	virtual ~GGamemode();
	void Init(SDL_Renderer* Renderer);

	virtual void MainGame() = 0;
	//virtual void MenuInputSChoose();
	//TODO ManyInputChoice
	virtual void MenuOperationsChoose();
	//TODO operation '/' will be available in next versions
	virtual void MenuDifficultyChoose();
	
protected:

	enum class InputSizes {
		VeryEasy = 10,
		Easy = 100,
		Intermiadiate = 1000,
		Hard = 10'000,
		VeryHard = 100'000,
		Demon = 1'000'000
	};
	
	//game loop functions
	virtual void UpdateMain() = 0;
	virtual void RenderMain() = 0;
	virtual void LoadTextures() = 0;

	void RandomInputs();
	void RandomOperators();
	void CalculateAnswer();
	void LoadInputs();

	//Primary Variables
	SDL_Renderer* Renderer;
	SDL_Event Event;
	
	//Interface
	int Answer;
	int CorrectAnswer;
	GKeyboard Keyboard;
	std::vector <int> Inputs;
	std::vector <GText> InputsTexture;
	InputSizes inputsizes;
	std::vector <bool> Operators;
	std::vector <GText> OperatorsTexture;
	SDL_Rect OperatorPos;
	int RandomOperator;

	//Fonts
	std::vector<TTF_Font*> Fonts;


};

