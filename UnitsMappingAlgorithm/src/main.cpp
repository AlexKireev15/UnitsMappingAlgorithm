#include "Common.h"

#include <list>
#include <array>
#include <iostream>

#include "Algorithm/Placer.h"
#include "Algorithm/Block.h"

std::list<UnitDrawablePtr> CreateUnitDrawables(size_t count)
{
	Vector unitSize = {20.f, 20.f};

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
	size_t unitCount = 15u;

	std::list<DrawablePtr> drawables;

	float mouseRadius = 25.f;
	float mouseDirRadius = mouseRadius / 2.f;
	float blockRadius = 100.f;
	float dynamicBlockRadius = 25.f;
	Vector blockSize = { blockRadius, blockRadius };
	Vector dir = { 0.f, -1.f };

	RectPtr blockRectLeft = CreateRect(blockSize, sf::Color::Yellow, { (float)window.getSize().x / 2.f - blockSize.x, (float)window.getSize().y / 2.f });
	CirclePtr blockCircleRight = CreateCircle(blockRadius, sf::Color::Blue, { (float)window.getSize().x / 2.f + blockRadius, (float)window.getSize().y / 2.f });
	
	std::list<UnitDrawablePtr> unitsDrawables = CreateUnitDrawables(unitCount);

	drawables.push_back(blockRectLeft);

	RectBlockPtr pLeftBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectLeft);
	CircleBlockPtr pRightBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleRight);

	Placer placer((float)window.getSize().x, (float)window.getSize().y, std::list<BlockPtr>{pLeftBlock}, unitsDrawables);

	std::array<std::string, 3> lineupNames = 
	{
		"line",
		"wedge",
		"square"
	};
	size_t currentLineupIdx = 0;
	std::string currentLineup = lineupNames[currentLineupIdx];

	Vector mousePosition;

	sf::Clock clock;
	float lastTime = 0;
	
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

					//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
				//mouse->setPosition(mousePosition);
				//mouseDir->setPosition(mousePosition + mouseDirRadius * dir);

				//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 20.f, 20.f }, false);
					drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
				}

				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 20.f, 20.f }, true);
					drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
				}
				//if (event.mouseButton.button == sf::Mouse::Button::Right)
				//{
				//	if(unitCount != 1)
				//		unitCount--;
				//}

				///*for (auto unit : unitsDrawables)
				//{
				//	drawables.remove_if([&unit](auto it) { return unit == it; });
				//}*/

				//unitsDrawables.clear();

				//unitsDrawables = CreateUnitDrawables(unitCount);
				//placer.SetUnitDrawables(unitsDrawables);
				//drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
				//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });

			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.control)
				{
					currentLineupIdx = (currentLineupIdx + 1) % lineupNames.size();
					currentLineup = lineupNames[currentLineupIdx];

					//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
				}

				if (event.key.alt)
				{
					/*for (auto unit : unitsDrawables)
					{
						drawables.remove_if([&unit](auto it) { return unit == it; });
					}*/

					CirclePtr blockCircleDynamic = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
					drawables.push_back(blockCircleDynamic);
					bool finishPlaceWater = false;
					bool isMousePressed = false;
					while (window.isOpen() && !finishPlaceWater)
					{
						sf::Event event;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
							{
								window.close();
							}
							if (event.type == sf::Event::MouseButtonPressed)
							{
								isMousePressed = true;
								auto newBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleDynamic);
								placer.AddBlock(newBlock);
								auto newCircle = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
								drawables.push_back(newCircle);
							}
							if (event.type == sf::Event::MouseButtonReleased)
							{
								isMousePressed = false;
							}
							if (event.type == sf::Event::MouseMoved)
							{
								mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
								blockCircleDynamic->setPosition(mousePosition);
								if (isMousePressed)
								{
									auto newBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleDynamic);
									placer.AddBlock(newBlock);
									auto newCircle = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
									drawables.push_back(newCircle);
									window.clear();

									for (auto& drawable : drawables)
										window.draw(*drawable);

									window.display();
								}
							}
							if (event.type == sf::Event::KeyPressed)
							{
								if (event.key.alt)
								{
									///drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());

									finishPlaceWater = true;
								}
							}

							
						}

						window.clear();

						for (auto& drawable : drawables)
							window.draw(*drawable);

						window.display();
					}

					drawables.remove(blockCircleDynamic);
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