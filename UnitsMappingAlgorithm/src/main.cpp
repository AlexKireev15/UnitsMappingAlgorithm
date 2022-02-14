#include <SFML/Graphics.hpp>
#include <list>

#include <iostream>

#include "Algorithm/PlaceAlgorithm.h"
#include "Algorithm/Blocks.h"
#include "Algorithm/Units.h"

#include "Algorithm/Utils.h"

using namespace PlaceAlgorithm;

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(1024u, 768u), "Units mapping");
	window.setVerticalSyncEnabled(true);

	std::list<DrawablePtr> drawables;

	float mouseRadius = 25.f;
	float mouseDirRadius = mouseRadius / 2.f;
	float blockRadius = 100.f;
	sf::Vector2f dir = { 0.f, -1.f };
	CirclePtr mouse = CreateCircle(mouseRadius, sf::Color::Red);
	CirclePtr mouseDir = CreateCircle(mouseDirRadius, sf::Color::Green);
	CirclePtr blockCircleLeft = CreateCircle(blockRadius, sf::Color::Green, { (float)window.getSize().x / 2.f - blockRadius, (float)window.getSize().y / 2.f });
	CirclePtr blockCircleRight = CreateCircle(blockRadius, sf::Color::Blue, { (float)window.getSize().x / 2.f + blockRadius, (float)window.getSize().y / 2.f });
	BlockPtr blockLeftPtr = CreateCircleBlock(ElementType::BLOCK_HIGH, blockCircleLeft);
	BlockPtr blockRightPtr = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleRight);


	PlaceAlgorithm::Placer placer(std::list<BlockPtr>{ blockLeftPtr, blockRightPtr });
	UnitGroup group = placer.Place("", 10, { 0.f,0.f }, dir, { 25.f, 25.f }, { 5.f, 5.f });
	auto groupDrawables = group.GetDrawables();

	drawables.push_back(blockCircleLeft);
	drawables.push_back(blockCircleRight);
	drawables.push_back(mouse);
	drawables.push_back(mouseDir);
	drawables.insert(drawables.end(), groupDrawables.begin(), groupDrawables.end());

	sf::Vector2f mousePosition;
	
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
					float rotAngle = sign * 5.f;
					float rotAngleRad =  rotAngle * (float)M_PI / 180.f;
					dir = { dir.x * cos(rotAngleRad) - dir.y * sin(rotAngleRad), dir.x * sin(rotAngleRad) + dir.y * cos(rotAngleRad) };
					mouseDir->setPosition(mousePosition + mouseDirRadius * dir);
					group.Rotate(rotAngle);
					placer.Replace(group);
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
				mouse->setPosition(mousePosition);
				mouseDir->setPosition(mousePosition + mouseDirRadius * dir);
				group.SetPosition(mousePosition);
				placer.Replace(group);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
			}
		}

		window.clear();
				
		for (auto& drawable : drawables)
			window.draw(*drawable);

		window.display();
	}

	return 0;
}