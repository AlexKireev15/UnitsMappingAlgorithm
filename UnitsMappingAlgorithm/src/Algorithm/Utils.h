#pragma once
#include "../Common.h"

#define M_PI 3.14159265358979323846f

inline float GetAbs(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline sf::Vector2f Normalize(const sf::Vector2f& v)
{
	sf::Vector2f result = v / GetAbs(v);
	return result;
}

inline float CrossProductAbs(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.y - a.y * b.x;
}

inline float GetAngleBetween(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float dot = a.x * b.x + a.y * b.y;
	float det = a.x * b.y - a.y * b.x;
	return abs(atan2(det, dot)) * 180.f / (float)M_PI;
}

inline bool IsIntersects(const sf::Vector2f& circleAPos, float circleARadius, const sf::Vector2f& circleBPos, float circleBRadius)
{
	sf::Vector2f distVector = circleAPos - circleBPos;
	float dist = GetAbs(distVector);
	
	return dist < circleARadius + circleBRadius;
}