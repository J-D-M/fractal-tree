#pragma once

#include <SDL2/SDL.h>

#include "error.hpp"

namespace sdl2
{
class Renderer;

class Window : Error
{
      public:
	// SDL window constatnts
	static const int    npos{SDL_WINDOWPOS_UNDEFINED};
	static const Uint32 shown{SDL_WINDOW_SHOWN};

	Window(const char *title, int x, int y, int w, int h, Uint32 flags);
	~Window();

	friend Renderer;

      private:
	SDL_Window *win;
};

} // namespace sdl2
