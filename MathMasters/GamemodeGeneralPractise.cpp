 #include "GamemodeGeneralPractise.h"

GGamemodeGeneralPractise::GGamemodeGeneralPractise() : GGamemode(), Tasks{ 10 }, Screen()
{
}

GGamemodeGeneralPractise::GGamemodeGeneralPractise(SDL_Renderer* Renderer) : GGamemode(Renderer), Tasks{ 10 },
Screen(Renderer)
{
}

GGamemodeGeneralPractise::~GGamemodeGeneralPractise()
{
}

void GGamemodeGeneralPractise::InitRenderer(SDL_Renderer* Renderer)
{
	Init(Renderer);
	Screen.InitRenderer(Renderer);
}

void GGamemodeGeneralPractise::MainGame()
{

	try {
		LoadTextures();
		Screen.Rect.x = 0;
		Screen.Rect.y = 0;
		Screen.Rect.w = 1920;
		Screen.Rect.h = 1080;


		Keyboard.Rect.x = 200;
		Keyboard.Rect.y = 700;
		Keyboard.TyperUpdate();

		InputsTexture[0].Rect.x = 200;
		InputsTexture[0].Rect.y = 0;
		InputsTexture[1].Rect.x = 200;
		InputsTexture[1].Rect.y = 300;


		MenuDifficultyChoose();
		MenuOperationsChoose();
		NewInputs();

		while (Tasks) {

			UpdateMain();
			if (!Keyboard.typing) {
				if (!Keyboard.GetText()->empty())
					Answer = std::stoi(*Keyboard.GetText());
				if (Answer == CorrectAnswer) {
					NewInputs();
					Tasks--;
					Keyboard.ResetText();
				}
				else Keyboard.typing = true;
			}
			else Keyboard.typing = true;

			RenderMain();

		}
	}
	catch (const MMerr& error) {
		ErrorHandler(error);
	}

}

void GGamemodeGeneralPractise::UpdateMain()
{
	SDL_PollEvent(&Event);
	switch (Event.key.keysym.sym) {
	case SDLK_ESCAPE:
		std::exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
	if (Event.type == SDL_QUIT) std::exit(EXIT_SUCCESS);
	Keyboard.Update();
}

void GGamemodeGeneralPractise::RenderMain()
{
	SDL_RenderClear(Renderer);

	SDL_RenderCopy(Renderer, Screen.GetTexture(), NULL, &Screen.Rect);
	RenderInputs();
	Keyboard.Render();
	//SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);

	SDL_RenderPresent(Renderer);
}

void GGamemodeGeneralPractise::LoadTextures() 
{
	if (!Screen.IMG_LoadTexture("Assets\\Textures\\screen.jpg"))
		throw MMerr::Texture_Init;
}

void GGamemodeGeneralPractise::NewInputs()
{
	RandomInputs();
	RandomOperators();
	CalculateAnswer();
	LoadInputs();
}

void GGamemodeGeneralPractise::RenderInputs()
{
	for (GText& Texture : InputsTexture) {
		SDL_RenderCopy(Renderer, Texture.GetTexture(), NULL, &Texture.Rect);
	}
	SDL_RenderCopy(Renderer, OperatorsTexture[RandomOperator].GetTexture(), NULL, &OperatorPos);
}

