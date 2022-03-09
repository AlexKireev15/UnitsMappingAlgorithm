#include "../Block.h"
#include "../Utils.h"

bool CircleBlock::IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector)
{
	sf::FloatRect circleRect = m_pCircle->getGlobalBounds();
	sf::FloatRect unitRect = pRect->getGlobalBounds();
	sf::FloatRect intersectionRect;

	if (!circleRect.intersects(unitRect, intersectionRect))
		return false;

	auto circleCenter = m_pCircle->getPosition();
	auto rectCenter = pRect->getPosition();
	auto size = pRect->getSize();
	float radius = m_pCircle->getRadius();
	float rectRadius = sqrt(size.x / 2.f * size.x / 2.f + size.y / 2.f * size.y / 2.f);

	if (GetAbs(circleCenter - rectCenter) >= radius + rectRadius)
		return false;

	correctionVector = (rectRadius - (GetAbs(circleCenter - rectCenter) - radius)) * Normalize(rectCenter - circleCenter);

	return true;
}

bool CircleBlock::IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size)
{
	return false;
}

bool RectBlock::IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector)
{
	return false;
}

bool RectBlock::IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size)
{
	return false;
}

bool TriangleBlock::IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector)
{
	return false;
}

bool TriangleBlock::IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size)
{
	return false;
}
