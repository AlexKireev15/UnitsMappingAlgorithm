#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>

using DrawablePtr = std::shared_ptr<sf::Drawable>;
using CirclePtr = std::shared_ptr<sf::CircleShape>;
using RectPtr = std::shared_ptr<sf::RectangleShape>;

struct UnitDrawable : public sf::Drawable
{
	RectPtr body;
	RectPtr gun;
	void SetPosition(const sf::Vector2f& position)
	{
		body->setPosition(position);
		gun->setPosition(position);
	}
	void SetRotation(const float& angle)
	{
		body->setRotation(angle);
	}
	void SetGunRotation(const float& angle)
	{
		gun->setRotation(angle);
	}
	void RotateGun(const float& angle)
	{
		gun->rotate(angle);

	}
	void SetGunDirection(const sf::Vector2f& dir)
	{
		m_gunDirection = dir;
	}
	sf::Vector2f GetGunDirection() const
	{
		return m_gunDirection;
	}
	float GetRotation() const
	{
		return body->getRotation();
	}
	float GetGunRotation() const
	{
		return gun->getRotation();
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(body)
			target.draw(*body, states);
		if(gun)
			target.draw(*gun, states);
	}

	sf::Vector2f m_gunDirection = sf::Vector2f(0.f, 1.f);
};

using UnitDrawablePtr = std::shared_ptr<UnitDrawable>;

inline CirclePtr CreateCircle(float radius, const sf::Color& color = sf::Color::White, const sf::Vector2f& position = { 0.f, 0.f })
{
	CirclePtr circle = std::make_shared<sf::CircleShape>(radius);
	circle->setOrigin({ radius, radius });
	//circle->setOrigin(radius, radius);
	circle->setPosition(position);
	circle->setFillColor(color);

	return circle;
}

inline RectPtr CreateRect(const sf::Vector2f& size, const sf::Vector2f& origin, const sf::Color& color = sf::Color::White, const sf::Vector2f& position = { 0.f, 0.f })
{
	RectPtr rect = std::make_shared<sf::RectangleShape>(size);
	rect->setOrigin(origin);
	rect->setPosition(position);
	rect->setFillColor(color);

	return rect;
}

inline RectPtr CreateRect(const sf::Vector2f& size, const sf::Color& color = sf::Color::White, const sf::Vector2f& position = { 0.f, 0.f })
{
	RectPtr rect = std::make_shared<sf::RectangleShape>(size);
	rect->setOrigin(size / 2.f);
	rect->setPosition(position);
	rect->setFillColor(color);

	return rect;
}

inline UnitDrawablePtr CreateUnitDrawable(const RectPtr& pBody, const RectPtr& pGun)
{
	UnitDrawablePtr pUnit = std::make_shared<UnitDrawable>();
	pUnit->body = pBody;
	pUnit->gun = pGun;
	return pUnit;
}

enum ElementType
{
	BLOCK_HIGH,
	BLOCK_LOW,
	UNIT,
	FREE,
};

//class Block;
//class Unit;
//class CircleBlock;
//using BlockPtr = std::shared_ptr<Block>;
//using UnitPtr = std::shared_ptr<Unit>;
//using CircleBlockPtr = std::shared_ptr<CircleBlock>;