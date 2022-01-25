#define _USE_MATH_DEFINES
#include <cmath>

#include "..\PlaceAlgorithm.h"


using namespace PlaceAlgorithm;

std::vector<Vector2f> Placer::LineUp(size_t count, Vector2f boundary, Vector2f padding) const
{
	std::vector<Vector2f> result;
	result.reserve(count);

	float spacing = padding.x;
	float totalSpace = boundary.x * count + (count > 0 ? (spacing * (count - 1)) : 0);
	for (size_t idx = 0; idx < count; ++idx)
	{
		result.push_back({ (boundary.x + spacing) * idx - totalSpace / 2.f, - boundary.y / 2.f });
	}

	return result;
}

std::vector<sf::RectangleShape> Placer::Place(const std::string & lineUpName, size_t count, Vector2f position, float angle, Vector2f boundary, Vector2f padding)
{
	/*
		TODO: Make several lineups 
	*/
	auto lineup = LineUp(count, boundary, padding);

	for (size_t idx = 0; idx < count; ++idx)
	{
		float x = lineup[idx].x;
		float y = lineup[idx].y;
		lineup[idx].x = x * cos(angle) - y * sin(angle);
		lineup[idx].y = x * sin(angle) + y * cos(angle);
	}

	for (size_t idx = 0; idx < count; ++idx)
	{
		lineup[idx].x = lineup[idx].x + position.x;
		lineup[idx].y = lineup[idx].y + position.y;
	}
	
	

	std::vector<sf::RectangleShape> shapes;
	for (size_t idx = 0; idx < count; ++idx)
	{
		auto rect = sf::RectangleShape({ boundary.x, boundary.y });
		rect.setFillColor(sf::Color::White);
		rect.setPosition({ lineup[idx].x, lineup[idx].y });
		rect.setRotation(angle * 180 / M_PI);
		shapes.push_back(rect);
	}

	return shapes;
}
