#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <optional>

class Tree
{

      public:
	Tree(const SDL_Point origin,
	     const int       length,
	     const double    angle,
	     const int       depth);

	auto left_branch() const -> std::optional<std::shared_ptr<Tree>>;
	auto right_branch() const -> std::optional<std::shared_ptr<Tree>>;
	auto get_origin() const -> SDL_Point;

      private:
	const int       _length;
	const double    _angle;
	const SDL_Point _origin;

	std::shared_ptr<Tree> l_branch;
	std::shared_ptr<Tree> r_branch;
};
