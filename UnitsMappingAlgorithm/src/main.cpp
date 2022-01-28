#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics.hpp>
#include <list>

#include <iostream>

#include "Algorithm/PlaceAlgorithm.h"

using namespace PlaceAlgorithm;

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
	window.setVerticalSyncEnabled(true);

	float mouseRadius = 25.f;
	float mouseDirRadius = mouseRadius / 2.f;
	sf::Vector2f dir = { 0.f, 1.f };
	sf::CircleShape mouse(mouseRadius);
	sf::CircleShape mouseDir(mouseDirRadius);

	mouse.setFillColor(sf::Color::Red);
	mouseDir.setFillColor(sf::Color::Green);

	float blockRadius = 100.f;
	sf::Vector2f pos1 = { window.getSize().x / 2.f - 2*blockRadius - mouseRadius / 2.f, window.getSize().y / 2.f - blockRadius };
	sf::Vector2f pos2 = { window.getSize().x / 2.f + mouseRadius / 2.f, window.getSize().y / 2.f - blockRadius };
	
	std::vector<CircleBlock> elements;
	elements.push_back(CircleBlock(ElementType::Block_High, pos1, blockRadius, sf::Color::Green));
	elements.push_back(CircleBlock(ElementType::Block_Low, pos2, blockRadius, sf::Color::Blue));

	sf::Vector2f bounds = { 25.f, 25.f };
	PlaceAlgorithm::Placer placer(elements);
	
	std::vector<sf::RectangleShape> shapes;
	for (int i = 0; i < 10; ++i)
	{
		sf::RectangleShape rect(bounds);
		rect.setFillColor(sf::Color::White);
		shapes.push_back(rect);
	}

	std::vector<sf::Transform> transforms(shapes.size(), sf::Transform::Identity);

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
					float rotAngle = sign * 5.f * (float)M_PI / 180.f;
					dir = { dir.x * cos(rotAngle) - dir.y * sin(rotAngle), dir.x * sin(rotAngle) + dir.y * cos(rotAngle) };
				}
			}
		}

		auto pos = sf::Mouse::getPosition(window);
		mouse.setPosition(pos.x - mouseRadius, pos.y - mouseRadius);
		mouseDir.setPosition(pos.x - mouseDirRadius - mouseDirRadius * dir.x, pos.y - mouseDirRadius - mouseDirRadius * dir.y);

		transforms = placer.Place("", shapes.size(), sf::Vector2f((float)pos.x, (float)pos.y), dir, bounds, { 5.f, 5.f });

		window.clear();
		for (auto element : elements)
		{
			window.draw(*element.m_pShape);
		}

		window.draw(mouse);
		window.draw(mouseDir);
		for (size_t idx = 0; idx < shapes.size(); ++idx)
		{
			window.draw(shapes[idx], transforms[idx]);
		}

		window.display();
	}

	return 0;
}