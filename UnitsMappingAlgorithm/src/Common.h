#pragma once
#define _USE_MATH_DEFINES
#include <SDL.h>
#include <SDL_render.h>
#include <cmath>
#include <memory>
#include <array>
#include <vector>

template<class T>
struct Vector2
{
	T x;
	T y;
	
	Vector2() : x(0), y(0) { }
	Vector2(T _x, T _y) : x(_x), y(_y) { }
	Vector2<T> operator/(int val) const
	{
		return Vector2<T>(x / val, y / val);
	}
	Vector2<T> operator*(int val) const
	{
		return Vector2<T>(x * val, y * val);
	}
	Vector2<T> operator+(const Vector2<T> & rhs) const
	{
		return Vector2<T>(x + rhs.x, y + rhs.y);
	}
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using BBox = SDL_FRect;

namespace Colors
{
	struct Color
	{
		Color() : 
			r(0), g(0), b(0), a(0)
		{}
		Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
			r(red), g(green), b(blue), a(alpha) 
		{}
		Uint8 r, g, b, a;
	};

	const Color White(255u, 255u, 255u, 255u);
	const Color Default(0u, 0u, 0u, 255u);
	const Color Red(255u, 0u, 0u, 255u);
	const Color Green(0u, 255u, 0u, 255u);
	const Color Blue(0u, 0u, 255, 255u);
	const Color Yellow(255u, 255u, 0u, 255u);
}

enum ElementType
{
	BLOCK_HIGH,
	BLOCK_LOW,
	UNIT,
	FREE,
};

//#include <cmath>
//#include <memory>
//#include <array>
//#include <vector>
//
//using DrawablePtr = std::shared_ptr<sf::Drawable>;
//using CirclePtr = std::shared_ptr<sf::CircleShape>;
//using RectPtr = std::shared_ptr<sf::RectangleShape>;
//using TrianglePtr = std::shared_ptr<sf::ConvexShape>;
//using Vector2f = sf::Vector2f;
//using Vector2i = sf::Vector2i;
//
//struct UnitDrawable : public sf::Drawable
//{
//	RectPtr body;
//	RectPtr gun;
//	void SetPosition(const Vector2f& position)
//	{
//		body->setPosition(position);
//		gun->setPosition(position);
//	}
//	void SetRotation(const float& angle)
//	{
//		body->setRotation(angle);
//	}
//	void SetGunRotation(const float& angle)
//	{
//		gun->setRotation(angle);
//	}
//	void RotateGun(const float& angle)
//	{
//		gun->rotate(angle);
//
//	}
//	void SetGunDirection(const Vector2f& dir)
//	{
//		m_gunDirection = dir;
//	}
//	Vector2f GetGunDirection() const
//	{
//		return m_gunDirection;
//	}
//	float GetRotation() const
//	{
//		return body->getRotation();
//	}
//	float GetGunRotation() const
//	{
//		return gun->getRotation();
//	}
//
//private:
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
//	{
//		if(body)
//			target.draw(*body, states);
//		if(gun)
//			target.draw(*gun, states);
//	}
//
//	Vector2f m_gunDirection = Vector2f(0.f, 1.f);
//};
//
//using UnitDrawablePtr = std::shared_ptr<UnitDrawable>;
//
//inline CirclePtr CreateCircle(float radius, const sf::Color& color = sf::Color::White, const Vector2f& position = { 0.f, 0.f })
//{
//	CirclePtr circle = std::make_shared<sf::CircleShape>(radius);
//	circle->setOrigin({ radius, radius });
//	circle->setPosition(position);
//	circle->setFillColor(color);
//
//	return circle;
//}
//
//inline TrianglePtr CreateTriangle(const std::array<Vector2f, 3u>& points, const sf::Color& color = sf::Color::White, const Vector2f& position = { 0.f, 0.f })
//{
//	TrianglePtr triangle = std::make_shared<sf::ConvexShape>(3);
//	triangle->setOrigin((points.at(0) + points.at(1) + points.at(2)) / 3.f);
//	triangle->setPosition((points.at(0) + points.at(1) + points.at(2)) / 3.f);
//	triangle->setPoint(0, points.at(0));
//	triangle->setPoint(1, points.at(1));
//	triangle->setPoint(2, points.at(2));
//	triangle->setFillColor(color);
//
//	return triangle;
//}
//
//inline RectPtr CreateRect(const Vector2f& size, const Vector2f& origin, const sf::Color& color = sf::Color::White, const Vector2f& position = { 0.f, 0.f })
//{
//	RectPtr rect = std::make_shared<sf::RectangleShape>(size);
//	rect->setOrigin(origin);
//	rect->setPosition(position);
//	rect->setFillColor(color);
//
//	return rect;
//}
//
//inline RectPtr CreateRect(const Vector2f& size, const sf::Color& color = sf::Color::White, const Vector2f& position = { 0.f, 0.f })
//{
//	RectPtr rect = std::make_shared<sf::RectangleShape>(size);
//	rect->setOrigin(size / 2.f);
//	rect->setPosition(position);
//	rect->setFillColor(color);
//
//	return rect;
//}
//
//inline UnitDrawablePtr CreateUnitDrawable(const RectPtr& pBody, const RectPtr& pGun)
//{
//	UnitDrawablePtr pUnit = std::make_shared<UnitDrawable>();
//	pUnit->body = pBody;
//	pUnit->gun = pGun;
//	return pUnit;
//}
//
//enum ElementType
//{
//	BLOCK_HIGH,
//	BLOCK_LOW,
//	UNIT,
//	FREE,
//};
//
////class Block;
////class Unit;
////class CircleBlock;
////using BlockPtr = std::shared_ptr<Block>;
////using UnitPtr = std::shared_ptr<Unit>;
////using CircleBlockPtr = std::shared_ptr<CircleBlock>;