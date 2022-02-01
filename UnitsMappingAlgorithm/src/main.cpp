#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics.hpp>
#include <list>

#include <iostream>

#include "Algorithm/PlaceAlgorithm.h"
#include "Algorithm/Blocks.h"
#include "Algorithm/Units.h"

using namespace PlaceAlgorithm;

int main(int argc, char ** argv)
{
	/*sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
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

	return 0;*/

	sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
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
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
				mouse->setPosition(mousePosition);
				mouseDir->setPosition(mousePosition + mouseDirRadius * dir);
				group.SetPosition(mousePosition);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				/*auto mat = mouse->getTransform().getMatrix();
				for (int idx = 0; idx < 4; ++idx)
				{
					for (int jdx = 0; jdx < 4; ++jdx)
					{
						std::cout << mat[idx * 4 + jdx] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;*/

				/*std::cout << mouse->getPosition().x << " " << mouse->getPosition().y << std::endl;
				std::cout << mousePosition.x << " " << mousePosition.y << std::endl << std::endl;*/
			}
		}

		window.clear();

		placer.Update(group);
		
		for (auto& drawable : drawables)
			window.draw(*drawable);

		window.display();
	}

	return 0;
}