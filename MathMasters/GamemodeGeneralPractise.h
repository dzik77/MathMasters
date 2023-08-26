#include "Gamemode.h"
#include "MenuInputHandler.h"
#pragma once

class GGamemodeGeneralPractise : GGamemode
{
public:

	GGamemodeGeneralPractise();
	GGamemodeGeneralPractise(SDL_Renderer* Renderer);
	~GGamemodeGeneralPractise();
	void InitRenderer(SDL_Renderer* Renderer);

	void MainGame() override;


private:
	
	void UpdateMain() override;
	void RenderMain() override;
	void LoadTextures() override;
	void NewInputs();
	void RenderInputs();

	int Tasks;
	GTexture Screen;

};

