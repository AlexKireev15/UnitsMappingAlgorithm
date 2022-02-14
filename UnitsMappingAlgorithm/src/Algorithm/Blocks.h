#pragma once
#include "../Common.h"

namespace PlaceAlgorithm
{
	using namespace sf;

	class Block
	{
	public:
		Block(const ElementType& type) : m_type(type) { }

		ElementType GetType() const { return m_type; }

		virtual bool IsIntersectedWithRect(const sf::Vector2f& position, const sf::Vector2f& size, float rotationAngle, sf::Vector2f& correctionVector) = 0;
		virtual bool IsIntersectedWith(const sf::Vector2f& position, float radius) = 0;

	protected:
		ElementType m_type;
	};

	class CircleBlock : public Block
	{
	public:
		CircleBlock(const ElementType& type, CirclePtr pCircle) : Block(type), m_pCircle(pCircle) { }
		sf::Vector2f GetPosition() const
		{
			if (m_pCircle)
				return m_pCircle->getPosition();
			return { 0.f, 0.f };
		}
		float GetRadius() const
		{
			if (m_pCircle)
				return m_pCircle->getRadius();
			return 0.f;
		}
		bool IsIntersectedWithRect(const sf::Vector2f& position, const sf::Vector2f& size, float rotationAngle, sf::Vector2f& correctionVector) override;
		bool IsIntersectedWith(const sf::Vector2f& position, float radius) override;

	private:
		CirclePtr m_pCircle;
	};

	inline CircleBlockPtr CreateCircleBlock(const ElementType& type, CirclePtr pCircle) { return std::make_shared<CircleBlock>(type, pCircle); }

};