#pragma once
#include "../Common.h"
#include "../Block.h"

#include <array>

#define M_PI 3.14159265358979323846f
#define EPS 1.e-10

inline bool IsZero(float v)
{
	return abs(v) <= EPS;
}

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

inline float DotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

inline float GetAngleBetween(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float dot = a.x * b.x + a.y * b.y;
	float det = a.x * b.y - a.y * b.x;
	if (IsZero(dot))
		return (det > 0 ? 1.f : -1.f ) * 90.f;
	if (IsZero(det))
		return 0.f;
	return std::atan2(det, dot) * 180.f / (float)M_PI;
}

bool IsIntersects(const sf::FloatRect& rect, const BlockPtr& pBlock);
bool IsIntersects(const sf::FloatRect& rect, const CirclePtr& pCircle);
bool IsIntersects(const sf::FloatRect& rect, const RectPtr& pRect);
bool IsIntersects(const std::array<sf::Vector2f, 4u>& rectPointsA, const std::array<sf::Vector2f, 4u>& rectPointsB);

std::array<sf::Vector2f, 4u> GetPoints(const RectPtr& pRect);
std::array<sf::Vector2f, 4u> GetPoints(const sf::FloatRect& rect);
std::array<sf::Vector2f, 4u> GetPoints(const RectPtr& pRect, const sf::Vector2f& offset);