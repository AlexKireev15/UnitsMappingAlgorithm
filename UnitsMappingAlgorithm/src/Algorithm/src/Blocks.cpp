#include "../Blocks.h"
#include "../Utils.h"
#include "../Units.h"

using namespace PlaceAlgorithm;

bool PlaceAlgorithm::CircleBlock::IsIntersectedWithRect(const Vector2f & position, const Vector2f & size, float rotationAngle, Vector2f & correctionVector)
{
	FloatRect circleRect = m_pCircle->getGlobalBounds();
	FloatRect unitRect(position - size / 2.f, size);
	Transform t; t.rotate(rotationAngle);
	t.transformRect(unitRect);
	FloatRect intersectionRect;

	if (!circleRect.intersects(unitRect, intersectionRect))
		return false;

	auto circleCenter = m_pCircle->getPosition();
	auto rectCenter = position;
	float radius = m_pCircle->getRadius();
	float rectRadius = sqrt(size.x / 2.f * size.x / 2.f + size.y / 2.f * size.y / 2.f);

	if (GetAbs(circleCenter - rectCenter) >= radius + rectRadius)
		return false;

	correctionVector = (rectRadius - (GetAbs(circleCenter - rectCenter) - radius)) * Normalize(rectCenter - circleCenter);

	return true;


	/*float distX = abs(circleCenter.x - rectCenter.x);
	float distY = abs(circleCenter.y - rectCenter.y);

	if (distX > (size.x / 2.f + radius) || distY > (size.y / 2.f + radius))
		return false;

	if (distX <= (size.x / 2.f))
	{
		correctionVector.y = rectCenter.y > circleCenter.y ? (distY - (size.y / 2.f + radius)) : ((size.y / 2.f + radius) - distY);
		return true;
	}
	if (distY <= (size.y / 2.f))
	{
		correctionVector.x = rectCenter.x > circleCenter.x ? (distX - (size.x / 2.f + radius)) : ((size.x / 2.f + radius) - distX);
		return true;
	}

	float hypot = (distX - size.x / 2) * (distX - size.x / 2) + (distY - size.y / 2) * (distY - size.y / 2);
	if (hypot <= radius * radius)
	{
		auto norm = [](const sf::Vector2f& v)
		{
			float m = sqrt(v.x * v.x + v.y * v.y);
			return v / m;
		};

		auto direction = norm((circleCenter - rectCenter));
		correctionVector = (radius - sqrt(hypot)) * direction;
		return true;
	}
	return false;*/
}

bool PlaceAlgorithm::CircleBlock::IsIntersectedWith(const sf::Vector2f& position, float radius)
{
	auto distVect = m_pCircle->getPosition() - position;
	float dist = GetAbs(distVect);

	return dist < m_pCircle->getRadius() + radius;
}
