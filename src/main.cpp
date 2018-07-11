#include <SDL2/SDL.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

const double pi{std::acos(-1)};

#include "tree.hpp"
#include "wrappers.hpp"

const int width{1024};
const int height{768};

auto
draw_tree(sdl2::Renderer &rend, std::shared_ptr<Tree> tree) -> void
{
	const auto tree_origin{tree->get_origin()};

	const auto draw_branch = [&](auto b) {
		rend.draw_line(tree_origin, b.value()->get_origin());
	};

	if (auto l_branch{tree->left_branch()}) {
		if (auto r_branch{tree->right_branch()}) {
			draw_branch(l_branch);
			draw_branch(r_branch);

			draw_tree(rend, l_branch.value());
			draw_tree(rend, r_branch.value());
		}
	}
}

auto
main(int argc, char **argv) -> int
{
	using namespace sdl2;

	Subsystem sys(SDL_INIT_VIDEO);

	Window main_win("Fractal Tree",
	                Window::npos,
	                Window::npos,
	                width,
	                height,
	                Window::shown);

	Renderer  rend(main_win);
	Event     event;
	SDL_Point base_coord{width / 2,
	                     static_cast<int>(height - height * 0.05)};

	auto tree{
	    std::make_shared<Tree>(base_coord, height * 0.20, pi / 2, 16)};

	rend.set_draw_color(color::black);
	rend.clear();
	rend.set_draw_color(color::white);
	draw_tree(rend, tree);

	for (bool quit{false}; !quit;) {
		while (event.poll()) {
			if (event.type() == SDL_QUIT)
				quit = true;
		}

		rend.present();
		SDL_Delay(static_cast<int>(1000 / 30));
	}
}
