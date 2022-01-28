#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace PlaceAlgorithm {
	class Placer;

	enum ElementType
	{
		Block_High,
		Block_Low,
		Other,
	};

	struct Block
	{
		Block(ElementType type) : m_type(type) { }
		virtual bool IsIntersectedWithRect(sf::Vector2f topLeftPoint, sf::Vector2f size, sf::Vector2f& correctionVector) = 0;
		ElementType m_type;
	};

	struct CircleBlock : public Block
	{
		CircleBlock(const ElementType& type, const sf::Vector2f& position, const float& radius, const sf::Color& color) :
			Block(type)
		{
			m_pShape = std::make_shared<sf::CircleShape>(radius);
			m_pShape->setFillColor(color);
			m_pShape->setPosition(position);
		}

		bool IsIntersectedWithRect(sf::Vector2f center, sf::Vector2f size, sf::Vector2f& correctionVector) override
		{
			auto pos = m_pShape->getPosition();
			auto radius = m_pShape->getRadius();
			auto circleCenter = sf::Vector2f{pos.x + radius, pos.y + radius};
			auto rectCenter = center;

			float radRect = sqrt(size.x * size.x + size.y * size.y);

			auto dist = (circleCenter - rectCenter);
			float d = sqrt(dist.x * dist.x + dist.y * dist.y);
			if (d < radius + radRect)
			{
				auto norm = [](const sf::Vector2f& v)
				{
					float m = sqrt(v.x * v.x + v.y * v.y);
					return v / m;
				};

				correctionVector = (radius + radRect - d) * norm(dist);
				return true;
			}

			return false;
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

		std::shared_ptr<sf::CircleShape> m_pShape;
	};

	class Placer
	{
	public:
		Placer(std::vector<CircleBlock> elements) : m_elements(elements) {}

		std::vector<sf::Vector2f> LineUp(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
		sf::Transform CorrectTransformsByBlocks(sf::Transform& transform, sf::Vector2f boundary) const;

		std::vector<sf::Transform> Place(const std::string& lineUpName, size_t count, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f boundary, sf::Vector2f padding);
	
	private:

		std::vector<CircleBlock> m_elements;
	};
};