#include <SDL.h>
#include <variant>
#include <vector>
#pragma once
class GMenuInputHandler
{

public:

	GMenuInputHandler(const GMenuInputHandler*) = delete;
	GMenuInputHandler(int Options);
	GMenuInputHandler(std::vector<bool> Options);
	inline int GetOption() { return Option; }
	~GMenuInputHandler();
	int MenuEventSingle();
	std::vector<bool> MenuEventMultiple();
	bool choosen;

private:
	
	
	SDL_Event Event;
	std::variant <std::vector<bool>, int> Options;
	int Option;

};

