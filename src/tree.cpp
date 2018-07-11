#include <cmath>

#include "tree.hpp"

const double pi{std::acos(-1)};

static auto
get_new_origin(const SDL_Point origin, const int length, const double angle)
    -> SDL_Point
{
	return {static_cast<int>(origin.x - (std::cos(angle) * length)),
	        static_cast<int>(origin.y - (std::sin(angle) * length))};
}

// Recursivly build tree and branches
Tree::Tree(const SDL_Point origin,
           const int       length,
           const double    angle,
           const int       depth)
    : _length{length}, _angle{angle}, _origin{origin}
{
	const auto make_new_branch = [=](double angle_delta) {
		return std::make_shared<Tree>(
		    get_new_origin(_origin, _length, _angle),
		    _length * 0.75,
		    _angle + angle_delta,
		    depth - 1);
	};

	if (depth > 0) {
		l_branch = make_new_branch(-pi / 12);
		r_branch = make_new_branch(pi / 6);
	}
}

static const auto safe_return =
    [](const auto p) -> std::optional<std::shared_ptr<Tree>> {
	if (p)
		return p;
	else
		return {};
};

auto
Tree::left_branch() const -> std::optional<std::shared_ptr<Tree>>
{
	return safe_return(l_branch);
}

auto
Tree::right_branch() const -> std::optional<std::shared_ptr<Tree>>
{
	return safe_return(r_branch);
}

auto
Tree::get_origin() const -> SDL_Point
{
	return _origin;
}
