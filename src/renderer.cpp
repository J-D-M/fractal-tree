#include "renderer.hpp"

namespace sdl2
{

Renderer::Renderer(const Window &win, int index, Uint32 flags)
    : ren{SDL_CreateRenderer(win.win, index, flags)}
{
	if (!ren)
		error("Failed to create renderer");
}

Renderer::~Renderer() { SDL_DestroyRenderer(ren); }

// Set renderer draw color
auto
Renderer::set_draw_color(Color c, Uint8 alpha) -> void
{
	auto [red, green, blue] = c;
	SDL_SetRenderDrawColor(ren, red, green, blue, alpha);
}

// Fill renderer will current color
auto
Renderer::clear() -> void
{
	SDL_RenderClear(ren);
}

// Present renderer
auto
Renderer::present() -> void
{
	SDL_RenderPresent(ren);
}

auto
Renderer::draw_line(SDL_Point p1, SDL_Point p2) -> void
{
	const auto [x1, y1]{p1};
	const auto [x2, y2]{p2};
	SDL_RenderDrawLine(ren, x1, y1, x2, y2);
}

} // namespace sdl2
