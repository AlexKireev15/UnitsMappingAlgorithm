#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

using DrawablePtr = std::shared_ptr<sf::Drawable>;
using CirclePtr = std::shared_ptr<sf::CircleShape>;
using RectPtr = std::shared_ptr<sf::RectangleShape>;

inline CirclePtr CreateCircle(float radius, const sf::Color& color = sf::Color::White, const sf::Vector2f& position = { 0.f, 0.f })
{
	CirclePtr circle = std::make_shared<sf::CircleShape>(radius);
	circle->setOrigin(radius, radius);
	circle->setPosition(position);
	circle->setFillColor(color);

	return circle;
}

inline RectPtr CreateRect(const sf::Vector2f& size, const sf::Color& color = sf::Color::White, const sf::Vector2f& position = { 0.f, 0.f })
{
	RectPtr rect = std::make_shared<sf::RectangleShape>(size);
	rect->setOrigin(size / 2.f);
	rect->setPosition(position);
	rect->setFillColor(color);

	return rect;
}

namespace PlaceAlgorithm
{
	enum ElementType
	{
		BLOCK_HIGH,
		BLOCK_LOW,
		UNIT,
		Other,
	};

	class Block;
	class Unit;
	class CircleBlock;
	using BlockPtr = std::shared_ptr<Block>;
	using UnitPtr = std::shared_ptr<Unit>;
	using CircleBlockPtr = std::shared_ptr<CircleBlock>;
};