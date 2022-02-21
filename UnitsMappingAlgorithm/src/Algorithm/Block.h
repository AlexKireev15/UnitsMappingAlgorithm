#pragma once
#include "../Common.h"

class Block
{
public:
	Block(const ElementType& type) : m_type(type) { }

	ElementType GetType() const { return m_type; }

	virtual bool IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector) = 0;
	virtual bool IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size) = 0;
	virtual sf::Vector2f GetPosition() const = 0;

protected:
	ElementType m_type;
};

class CircleBlock : public Block
{
public:
	CircleBlock(const ElementType& type, CirclePtr pCircle) : Block(type), m_pCircle(pCircle) { }
	sf::Vector2f GetPosition() const override
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
	CirclePtr GetDrawable() const
	{
		return m_pCircle;
	}
	bool IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector) override;
	bool IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size) override;

private:
	CirclePtr m_pCircle;
};

class RectBlock : public Block
{
public:
	RectBlock(const ElementType& type, RectPtr pRect) : Block(type), m_pRect(pRect) { }
	sf::Vector2f GetPosition() const override
	{
		if (m_pRect)
			return m_pRect->getPosition();
		return { 0.f, 0.f };
	}
	sf::Vector2f GetSize() const
	{
		if (m_pRect)
			return m_pRect->getSize();
		return { 0.f, 0.f };
	}
	RectPtr GetDrawable() const
	{
		return m_pRect;
	}
	bool IsIntersectedWithRect(const RectPtr& pRect, sf::Vector2f& correctionVector) override;
	bool IsIntersectRect(const sf::Vector2f& position, const sf::Vector2f& size) override;

private:
	RectPtr m_pRect;
};

using BlockPtr = std::shared_ptr<Block>;
using CircleBlockPtr = std::shared_ptr<CircleBlock>;
using RectBlockPtr = std::shared_ptr<RectBlock>;

inline CircleBlockPtr CreateCircleBlock(const ElementType& type, CirclePtr pCircle)
{
	return std::make_shared<CircleBlock>(type, pCircle);
}
inline RectBlockPtr CreateRectBlock(const ElementType& type, RectPtr pRect)
{
	return std::make_shared<RectBlock>(type, pRect);
}

template<typename T>
inline std::shared_ptr<T> Cast(BlockPtr pBlock)
{
	return (std::dynamic_pointer_cast<T>(pBlock));
}