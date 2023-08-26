#include "MenuInputHandler.h"

GMenuInputHandler::GMenuInputHandler(int Options): Event(), Options{Options}, Option{0}, choosen{false}
{
}

GMenuInputHandler::GMenuInputHandler(std::vector<bool> Options): Event(), Options{Options}, Option{0}, choosen{false}
{
}

GMenuInputHandler::~GMenuInputHandler()
{
}

int GMenuInputHandler::MenuEventSingle()
{
	if (!std::holds_alternative<int>(Options)) throw std::bad_variant_access();
	if (choosen) return Option;
	SDL_PollEvent(&Event);
	if (Event.type == SDL_KEYDOWN) {
		switch (Event.key.keysym.sym) {
		case SDLK_RETURN:
			choosen = true;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			if (Option < std::get<int>(Options) - 1) { 
				Option++;
			}
			break;
		case SDLK_LEFT:
		case SDLK_a:
			if (Option > 0)
				Option--;
			break;
		case SDLK_ESCAPE:
			std::exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
	if (Event.type == SDL_QUIT) std::exit(EXIT_SUCCESS);

	return Option;
}

std::vector<bool> GMenuInputHandler::MenuEventMultiple()
{
	if (!std::holds_alternative<std::vector<bool>>(Options)) throw std::bad_variant_access();
	if (choosen) return std::get<std::vector<bool>>(Options);;
	SDL_PollEvent(&Event);
	if (Event.type == SDL_KEYDOWN) {
		switch (Event.key.keysym.sym) {
		case SDLK_RETURN:
			for(bool option: std::get<std::vector<bool>>(Options))
				if (option) {
					choosen = true;
					break;
				}
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			if (Option < std::get<std::vector<bool>>(Options).size() - 1)
				Option++;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			if (Option > 0)
				Option--;
			break;
		case SDLK_UP:
		case SDLK_w:
			std::get<std::vector<bool>>(Options)[Option] = true;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			std::get<std::vector<bool>>(Options)[Option] = false;
			break;
		case SDLK_ESCAPE:
			std::exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
	if (Event.type == SDL_QUIT) std::exit(EXIT_SUCCESS);

	return std::get<std::vector<bool>>(Options);
	
}
