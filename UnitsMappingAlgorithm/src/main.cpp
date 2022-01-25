#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics.hpp>
#include <list>

#include <iostream>

#include "Algorithm/PlaceAlgorithm.h"

enum ElementType
{
	Block_High,
	Block_Low,
	Other,
};

struct Element
{
	Element(const ElementType& type, const sf::Vector2f& position, const std::shared_ptr<sf::Shape>& pShape) :
		m_type(type), m_position(position), m_pShape(pShape) 
	{
		m_pShape->setPosition(position);
	}
	Element(const ElementType& type, const sf::Vector2f& position, const float& radius, const sf::Color& color) :
		m_type(type), m_position(position)
	{ 
		m_pShape = std::make_shared<sf::CircleShape>(radius);
		m_pShape->setFillColor(color);
		m_pShape->setPosition(position);
	}

	ElementType m_type;
	sf::Vector2f m_position;
	std::shared_ptr<sf::Shape> m_pShape;
};

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
	window.setVerticalSyncEnabled(true);

	float mouseRadius = 25.f;
	float mouseDirRadius = mouseRadius / 2.f;
	float angle = (float) M_PI_2;
	sf::Vector2f dir = { cos(angle), sin(angle) };
	sf::CircleShape mouse(mouseRadius);
	sf::CircleShape mouseDir(mouseDirRadius);

	mouse.setFillColor(sf::Color::Red);
	mouseDir.setFillColor(sf::Color::Green);

	float blockRadius = 100.f;
	sf::Vector2f pos1 = { window.getSize().x / 2.f - 2*blockRadius - mouseRadius / 2.f, window.getSize().y / 2.f - blockRadius };
	sf::Vector2f pos2 = { window.getSize().x / 2.f + mouseRadius / 2.f, window.getSize().y / 2.f - blockRadius };
	
	std::list<Element> elements;
	elements.push_back(Element(ElementType::Block_High, pos1, blockRadius, sf::Color::Green));
	elements.push_back(Element(ElementType::Block_Low, pos2, blockRadius, sf::Color::Blue));

	PlaceAlgorithm::Placer placer;
	


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				float sign = event.mouseWheelScroll.delta >= 0.f ? 1.f : -1.f;
				{
					angle += sign * 5.f * (float) M_PI / 180.f;
					dir = { cos(angle), sin(angle) };
				}
			}
		}

		auto pos = sf::Mouse::getPosition(window);
		mouse.setPosition(pos.x - mouseRadius, pos.y - mouseRadius);
		mouseDir.setPosition(pos.x - mouseDirRadius - mouseDirRadius * dir.x, pos.y - mouseDirRadius - mouseDirRadius * dir.y);

		auto placed = placer.Place("", 10, { mouse.getPosition().x + mouse.getRadius() , mouse.getPosition().y + mouse.getRadius() }, M_PI_2 + angle, { 25, 25 }, { 5, 5 });

		window.clear();
		for (auto element : elements)
		{
			window.draw(*element.m_pShape);
		}

		window.draw(mouse);
		window.draw(mouseDir);
		for (auto p : placed)
		{
			window.draw(p);
		}

		window.display();
	}

	return 0;
}