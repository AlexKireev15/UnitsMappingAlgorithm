#pragma once
#include "../Common.h"

inline float GetAbs(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline sf::Vector2f Normalize(sf::Vector2f v)
{
	v /= GetAbs(v);
	return v;
}

inline float CrossProductAbs(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.y - a.y * b.x;
}