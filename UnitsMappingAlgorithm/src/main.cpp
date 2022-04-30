//#include "Common.h"
//
//#include <list>
//#include <array>
//#include <iostream>
//
//#include "Algorithm/Placer.h"
//#include "Algorithm/Block.h"
//
//std::list<UnitDrawablePtr> CreateUnitDrawables(size_t count)
//{
//	Vector2f unitSize = {20.f, 20.f};
//
//	std::list<UnitDrawablePtr> unitsDrawables;
//	for (size_t idx = 0; idx < count; ++idx)
//	{
//		auto bodyRect = CreateRect(unitSize, sf::Color::White);
//		auto gunRect = CreateRect({ unitSize.x / 4.f, unitSize.y }, { unitSize.x / 8.f, unitSize.y - unitSize.x / 8.f }, sf::Color::Red);
//		auto unitDrawable = CreateUnitDrawable(bodyRect, gunRect);
//		unitsDrawables.push_back(unitDrawable);
//	}
//
//	return unitsDrawables;
//}
//
//size_t CountFps(float lastTime, sf::Clock& clock)
//{
//	float currentTime = clock.restart().asSeconds();
//	float fps = 1.f / (currentTime - lastTime);
//	lastTime = currentTime;
//	return fps;
//}
//
//
//sf::Font font;
//
//std::shared_ptr<sf::Text> CreateText(const std::string& str)
//{
//	std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
//
//	if (!font.loadFromFile("arial.ttf"))
//	{
//	}
//	// select the font
//	text->setFont(font); // font is a sf::Font
//
//	// set the string to display
//	text->setString(str);
//
//	// set the character size
//	text->setCharacterSize(24); // in pixels, not points!
//
//	// set the color
//	text->setFillColor(sf::Color::Red);
//
//	// set the text style
//	text->setStyle(sf::Text::Bold);
//
//	return text;
//}
//
//int main(int argc, char ** argv)
//{
//	sf::RenderWindow window(sf::VideoMode(900u, 600u), "Units mapping");
//	window.setVerticalSyncEnabled(true);
//	size_t unitCount = 15u;
//	auto fpsCounter = CreateText("0");
//
//	std::list<DrawablePtr> drawables;
//
//	float mouseRadius = 25.f;
//	float mouseDirRadius = mouseRadius / 2.f;
//	float blockRadius = 100.f;
//	float dynamicBlockRadius = 25.f;
//	Vector2f blockSize = { blockRadius, blockRadius };
//	Vector2f dir = { 0.f, -1.f };
//
//	//CirclePtr mouse = CreateCircle(mouseRadius, sf::Color::Red);
//	//CirclePtr mouseDir = CreateCircle(mouseDirRadius, sf::Color::Green);
//	RectPtr blockRectLeft = CreateRect(blockSize, sf::Color::Yellow, { (float)window.getSize().x / 2.f - blockSize.x, (float)window.getSize().y / 2.f });
//	RectPtr blockRectRight = CreateRect(blockSize, sf::Color::Green, { (float)window.getSize().x / 2.f + blockSize.x, (float)window.getSize().y / 2.f });
//	
//	std::list<UnitDrawablePtr> unitsDrawables = CreateUnitDrawables(unitCount);
//
//	drawables.push_back(blockRectLeft);
//	drawables.push_back(blockRectRight);
//	//drawables.push_back(mouse);
//	//drawables.push_back(mouseDir);
//	//drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
//
//	drawables.push_back(fpsCounter);
//
//	RectBlockPtr pLeftBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectLeft);
//	RectBlockPtr pRightBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectRight);
//
//	Placer placer(window.getSize().x, window.getSize().y, std::list<BlockPtr>{pLeftBlock, pRightBlock}, unitsDrawables);
//
//	std::array<std::string, 3> lineupNames = 
//	{
//		"line",
//		"wedge",
//		"square"
//	};
//	size_t currentLineupIdx = 0;
//	std::string currentLineup = lineupNames[currentLineupIdx];
//
//	Vector2f mousePosition;
//
//	sf::Clock clock;
//	float lastTime = 0;
//	
//	while (window.isOpen())
//	{
//
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//
//			if (event.type == sf::Event::MouseWheelScrolled)
//			{
//				float sign = event.mouseWheelScroll.delta >= 0.f ? 1.f : -1.f;
//				{
//					float rotAngle = sign * 5.f;
//					float rotAngleRad =  rotAngle * (float)M_PI / 180.f;
//					dir = { dir.x * cos(rotAngleRad) - dir.y * sin(rotAngleRad), dir.x * sin(rotAngleRad) + dir.y * cos(rotAngleRad) };
//					//mouseDir->setPosition(mousePosition + mouseDirRadius * dir);
//
//					//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
//				}
//			}
//
//			if (event.type == sf::Event::MouseMoved)
//			{
//				mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
//				//mouse->setPosition(mousePosition);
//				//mouseDir->setPosition(mousePosition + mouseDirRadius * dir);
//
//				//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
//			}
//
//			if (event.type == sf::Event::MouseButtonPressed)
//			{
//				if (event.mouseButton.button == sf::Mouse::Button::Left)
//				{
//					placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 20.f, 20.f }, false);
//					drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
//				}
//
//				if (event.mouseButton.button == sf::Mouse::Button::Right)
//				{
//					placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 20.f, 20.f }, true);
//					drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
//				}
//				//if (event.mouseButton.button == sf::Mouse::Button::Right)
//				//{
//				//	if(unitCount != 1)
//				//		unitCount--;
//				//}
//
//				///*for (auto unit : unitsDrawables)
//				//{
//				//	drawables.remove_if([&unit](auto it) { return unit == it; });
//				//}*/
//
//				//unitsDrawables.clear();
//
//				//unitsDrawables = CreateUnitDrawables(unitCount);
//				//placer.SetUnitDrawables(unitsDrawables);
//				//drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
//				//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
//
//			}
//
//			if (event.type == sf::Event::KeyPressed)
//			{
//				if (event.key.control)
//				{
//					currentLineupIdx = (currentLineupIdx + 1) % lineupNames.size();
//					currentLineup = lineupNames[currentLineupIdx];
//
//					//placer.PlaceUnits(currentLineup, unitCount, mousePosition, dir, unitsDrawables.front()->body->getSize(), { 5.f, 5.f });
//				}
//
//				if (event.key.alt)
//				{
//					/*for (auto unit : unitsDrawables)
//					{
//						drawables.remove_if([&unit](auto it) { return unit == it; });
//					}*/
//
//					CirclePtr blockCircleDynamic = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
//					drawables.push_back(blockCircleDynamic);
//					bool finishPlaceWater = false;
//					bool isMousePressed = false;
//					while (window.isOpen() && !finishPlaceWater)
//					{
//						sf::Event event;
//						while (window.pollEvent(event))
//						{
//							if (event.type == sf::Event::Closed)
//							{
//								window.close();
//							}
//							if (event.type == sf::Event::MouseButtonPressed)
//							{
//								isMousePressed = true;
//								auto newBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleDynamic);
//								placer.AddBlock(newBlock);
//								auto newCircle = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
//								drawables.push_back(newCircle);
//							}
//							if (event.type == sf::Event::MouseButtonReleased)
//							{
//								isMousePressed = false;
//							}
//							if (event.type == sf::Event::MouseMoved)
//							{
//								mousePosition = { (float)event.mouseMove.x, (float)event.mouseMove.y };
//								blockCircleDynamic->setPosition(mousePosition);
//								if (isMousePressed)
//								{
//									auto newBlock = CreateCircleBlock(ElementType::BLOCK_LOW, blockCircleDynamic);
//									placer.AddBlock(newBlock);
//									auto newCircle = CreateCircle(dynamicBlockRadius, sf::Color::Blue, mousePosition);
//									drawables.push_back(newCircle);
//
//									fpsCounter->setString(std::to_string(CountFps(lastTime, clock)));
//									window.clear();
//
//									for (auto& drawable : drawables)
//										window.draw(*drawable);
//
//									window.display();
//								}
//							}
//							if (event.type == sf::Event::KeyPressed)
//							{
//								if (event.key.alt)
//								{
//									///drawables.insert(drawables.end(), unitsDrawables.begin(), unitsDrawables.end());
//
//									finishPlaceWater = true;
//								}
//							}
//
//							
//						}
//
//						fpsCounter->setString(std::to_string(CountFps(lastTime, clock)));
//						window.clear();
//
//						for (auto& drawable : drawables)
//							window.draw(*drawable);
//
//						window.display();
//					}
//
//					drawables.remove(blockCircleDynamic);
//
//					placer.ConsoleMap();
//				}
//			}
//		}
//
//		auto str = std::to_string(CountFps(lastTime, clock));
//		fpsCounter->setString(str);
//		window.clear();
//		
//		for (auto& drawable : drawables)
//			window.draw(*drawable);
//
//		window.display();
//	}
//
//	return 0;
//}

#include "Common.h"
#include "Visual/Visual.h"
#include <string>
#include <list>

#include <iostream>

class Visualizer
{
public:
	Visualizer(const std::string& windowName, int width, int height) : m_isSDLInitialized(false), m_pWindow(nullptr), m_pRenderer(nullptr)
	{
		m_isSDLInitialized = Init(windowName, width, height);
	}

	bool Init(const std::string& windowName, int width, int height)
	{
		if (m_isSDLInitialized)
			return true;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}
		m_pWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (!m_pWindow)
		{
			return false;
		}
		m_windowSize = { (float)width, (float)height };
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		return true;
	}

	void AddUnitDrawables(size_t count)
	{
		Vector2f unitSize = {25.f, 25.f};

		auto bodyRect = CreateRect(m_pRenderer, { 0.f, 0.f }, unitSize, Colors::White);
		auto gunRect = CreateRect(m_pRenderer, { unitSize.x / 2.f - unitSize.x / 16.f, unitSize.y / 2.f - unitSize.x / 16.f }, { unitSize.x / 8.f, unitSize.y - unitSize.x / 8.f }, Colors::Red);

		m_unitsDrawables;
		for (size_t idx = 0; idx < count; ++idx)
		{
			auto unitDrawable = CreateUnitDrawable(bodyRect->Clone(), gunRect->Clone());
			unitDrawable->SetPosition({ unitSize.x * idx + idx * 5.f, 0.f });
			m_unitsDrawables.push_back(unitDrawable);
		}

		m_renderList.insert(m_renderList.end(), m_unitsDrawables.begin(), m_unitsDrawables.end());
	}

	void RemoveUnitDrawables()
	{
		m_renderList.remove_if([](const VisualObjectPtr& o) {return UnitDrawable::IsUnitDrawable(o); });
	}

	void Run()
	{
		if (!m_isSDLInitialized)
			return;

		size_t unitCount = 15u;
		float mouseRadius = 25.f;
		float mouseDirRadius = mouseRadius / 2.f;
		float blockRadius = 100.f;
		float dynamicBlockRadius = 25.f;
		Vector2f blockSize = { blockRadius, blockRadius };
		Vector2f dir = { 0.f, -1.f };

		Vector2f mousePosition;

		RectPtr blockRectLeft = CreateRect(m_pRenderer, { m_windowSize.x / 2.f - blockSize.x, m_windowSize.y / 2.f }, blockSize, Colors::Green);
		RectPtr blockRectRight = CreateRect(m_pRenderer, { m_windowSize.x / 2.f + blockSize.x, m_windowSize.y / 2.f }, blockSize, Colors::Yellow);
		m_renderList.push_back(blockRectLeft);
		m_renderList.push_back(blockRectRight);

		AddUnitDrawables(unitCount);

		RectBlockPtr pLeftBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectLeft);
		RectBlockPtr pRightBlock = CreateRectBlock(ElementType::BLOCK_HIGH, blockRectRight);

		bool isQuit = false;
		while (!isQuit)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					isQuit = true;

				if (e.type == SDL_MOUSEMOTION)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					mousePosition.x = (float)x;
					mousePosition.y = (float)y;
					
					/*int idx = 0;
					for (auto& unit : m_unitsDrawables)
					{
						auto shift = unit->body->GetSize();
						shift.x += 5.f;
						shift.y = 0.f;
						unit->SetPosition(mousePosition + shift * idx);
						idx++;
					}*/
				}
			}
			SDL_RenderClear(m_pRenderer);

			for(auto& pObject : m_renderList)
				pObject->Draw();

			SDL_RenderPresent(m_pRenderer);
		}
	}

	~Visualizer()
	{
		if (!m_isSDLInitialized)
			return;
		if (m_pRenderer)
			SDL_DestroyRenderer(m_pRenderer);
		if(m_pWindow)
			SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

private:
	bool m_isSDLInitialized = false;
	SDL_Window* m_pWindow;
	Vector2f m_windowSize;
	SDL_Renderer* m_pRenderer;
	std::list<VisualObjectPtr> m_renderList;
	std::list<UnitDrawablePtr> m_unitsDrawables;
};

int main(int argc, char** argv)
{
	Visualizer v("Units placer visualizer", 900, 600);
	v.Run();
	return 0;
}