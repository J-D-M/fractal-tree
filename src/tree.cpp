#include <cmath>

#include "tree.hpp"

const double pi{std::atan(1) * 4};

static auto
get_new_origin(const SDL_Point origin, const int length, const double angle)
    -> SDL_Point
{
	auto [x, y]{origin};

	x += static_cast<int>(std::cos(angle) * length);
	y += static_cast<int>(std::sin(angle) * length);

	return {x, y};
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
		    _length * (2 / 3),
		    _angle + angle_delta,
		    depth - 1);
	};

	if (depth > 0) {
		l_branch = make_new_branch(pi / 6);
		r_branch = make_new_branch(-(pi / 4));
	}
}

static const auto safe_return = [](const auto p) -> std::optional<Tree> {
	if (p.get())
		return *p;
	else
		return {};
};

auto
Tree::left_branch() const -> std::optional<Tree>
{
	return safe_return(l_branch);
}

auto
Tree::right_branch() const -> std::optional<Tree>
{
	return safe_return(r_branch);
}

auto
Tree::get_origin() const -> SDL_Point
{
	return _origin;
}
