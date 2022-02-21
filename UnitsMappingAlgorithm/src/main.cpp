#include "Common.h"

#include <list>
#include <array>
#include <iostream>

#include "Algorithm/Placer.h"
#include "Algorithm/Block.h"

std::list<UnitDrawablePtr> CreateUnitDrawables(size_t count)
{
	sf::Vector2f unitSize = {20.f, 20.f};

	std::list<UnitDrawablePtr> unitsDrawables;
	for (size_t idx = 0; idx < count; ++idx)
	{
		auto bodyRect = CreateRect(unitSize, sf::Color::White);
		auto gunRect = CreateRect({ unitSize.x / 4.f, unitSize.y }, { unitSize.x / 8.f, unitSize.y - unitSize.x / 8.f }, sf::Color::Red);
		auto unitDrawable = CreateUnitDrawable(bodyRect, gunRect);
		unitsDrawables.push_back(unitDrawable);
	}

	return unitsDrawables;
}

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
	window.setVerticalSyncEnabled(true);

	std::list<DrawablePtr> drawables;

	float mouseRadius = 25.f;
	float mouseDirRadius = mouseRadius / 2.f;
	float blockRadius = 100.f;
	sf::Vector2f blockSize = { blockRadius, blockRadius };
	sf::Vector2f dir = { 0.f, -1.f };

	//CirclePtr mouse = CreateCircle(mouseRadius, sf::Color::Red);
	//CirclePtr mouseDir = CreateCircle(mouseDirRadius, sf::Color::Green);
	RectPtr blockRectLeft = CreateRect(blockSize, sf::Color::Yellow, { (float)window.getSize().x / 2.f - blockSize.x, (float)window.getSize().y / 2.f });
	CirclePtr blockCircleRight = CreateCircle(blockRadius, sf::Color::Blue, { (float)window.getSize().x / 2.f + blockRadius, (float)window.getSize().y / 2.f });
	
	std::list<UnitDrawablePtr> unitsDrawables = CreateUnitDrawables(9u);

	drawables.push_back(blockRectLeft);
	drawables.push_back(blockCircleRight);
	//drawables.push_back(mouse);
	//drawables.push_back(mouseDir);
	drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());

	RectBlockPtr pLeftBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectLeft);
	CircleBlockPtr pRightBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleRight);

	Placer placer(window.getSize().x, window.getSize().y, std::list<BlockPtr>{pLeftBlock, pRightBlock}, unitsDrawables);

	std::array<std::string, 3> lineupNames = 
	{
		"line",
		"wedge",
		"square"
	};
	size_t currentLineupIdx = 0;
	std::string currentLineup = lineupNames[currentLineupIdx];

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
					//mouseDir->setPosition(mousePosition + mouseDirRadius * dir);

					placer.PlaceUnits(currentLineup, 9, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
				//mouse->setPosition(mousePosition);
				//mouseDir->setPosition(mousePosition + mouseDirRadius * dir);

				placer.PlaceUnits(currentLineup, 9, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.control)
				{
					currentLineupIdx = (currentLineupIdx + 1) % lineupNames.size();
					currentLineup = lineupNames[currentLineupIdx];

					placer.PlaceUnits(currentLineup, 9, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
				}
			}
		}

		window.clear();
		
		for (auto& drawable : drawables)
			window.draw(*drawable);

		window.display();
	}

	return 0;
}