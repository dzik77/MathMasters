#pragma once


enum class MMerr {
	SDL_Init = 1,
	TTF_Init,
	IMG_Init,
	Window_Init,
	Renderer_Init,
	Font_Init,
	Texture_Init
};

inline void ErrorHandler(const MMerr& error) {
	switch (error) {
	case MMerr::Renderer_Init:
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
		std::terminate();
	case MMerr::Font_Init:
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
		std::terminate();
	case MMerr::Texture_Init:
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
		std::terminate();
	}
}

