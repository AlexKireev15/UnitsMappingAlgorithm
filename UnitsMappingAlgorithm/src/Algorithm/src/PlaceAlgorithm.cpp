#define _USE_MATH_DEFINES
#include <cmath>

#include "..\PlaceAlgorithm.h"


using namespace PlaceAlgorithm;
using namespace sf;

std::vector<Vector2f> Placer::LineUp(size_t count, Vector2f boundary, Vector2f padding) const
{
	std::vector<Vector2f> result;
	result.reserve(count);

	float spacing = padding.x;
	float totalSpace = boundary.x * count + (count > 0 ? (spacing * (count - 1)) : 0);
	for (size_t idx = 0; idx < count; ++idx)
	{
		result.push_back({ (boundary.x + spacing) * idx - totalSpace / 2.f, -boundary.y / 2 });
	}

	return result;
}

sf::Transform PlaceAlgorithm::Placer::CorrectTransformsByBlocks(sf::Transform & transform, sf::Vector2f boundary) const
{
	for (auto block : m_elements)
	{
		if (block.m_type == ElementType::Block_High || block.m_type == ElementType::Block_Low)
		{
			sf::Vector2f center = transform.transformPoint(boundary / 2.f);
			//sf::Transform t = sf::Transform::Identity;

			sf::Vector2f correctionVector;
			if (block.IsIntersectedWithRect(center, boundary, correctionVector))
				transform.translate(correctionVector);
		}
	}
	return transform;
}

float GetAbs(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float GetAngleBetween(sf::Vector2f a, sf::Vector2f b)
{
	float dot = a.x * b.x + a.y * b.y;

	float sign = (a.x * b.y - b.x * a.y) > 0 ? 1.f : -1.f;
	return acos(sign * dot / (GetAbs(a) * GetAbs(b))) * 180.f / (float)M_PI;
}



std::vector<sf::Transform> Placer::Place(const std::string & lineUpName, size_t count, Vector2f position, Vector2f direction, Vector2f boundary, Vector2f padding)
{
	/*
		TODO: Make several lineups 
	*/

	Vector2f initialDirection = { 0.f, 1.f };
	
	float angle = GetAngleBetween(initialDirection, direction);
	
	sf::Transform globalTransform = sf::Transform::Identity;
	globalTransform
		.rotate(angle, position)
		.translate(position.x, position.y);

	std::vector<sf::Transform> transforms;
	transforms.reserve(count);

	auto initialLineup = LineUp(count, boundary, padding);
	for (auto translation : initialLineup)
	{
		sf::Transform t(globalTransform);
		t.translate(translation);
		t = CorrectTransformsByBlocks(t, boundary);
		transforms.push_back(t);
	}

	return transforms;
}
