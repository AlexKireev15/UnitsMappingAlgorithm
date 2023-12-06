#pragma once
#include "../Common.h"

class Block
{
public:
	Block(const ElementType& type) : m_type(type) { }

	ElementType GetType() const { return m_type; }

	virtual bool IsIntersectedWithRect(const RectPtr& pRect, Vector& correctionVector) = 0;
	virtual bool IsIntersectRect(const Vector& position, const Vector& size) = 0;
	virtual Vector GetPosition() const = 0;
	virtual sf::FloatRect GetBBox() const = 0;

protected:
	ElementType m_type;
};

class CircleBlock : public Block
{
public:
	CircleBlock(const ElementType& type, CirclePtr pCircle) : Block(type), m_pCircle(pCircle) { }
	Vector GetPosition() const override
	{
		if (m_pCircle)
			return m_pCircle->getPosition();
		return { 0.f, 0.f };
	}
	sf::FloatRect GetBBox() const override
	{
		return m_pCircle->getGlobalBounds();
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
	bool IsIntersectedWithRect(const RectPtr& pRect, Vector& correctionVector) override;
	bool IsIntersectRect(const Vector& position, const Vector& size) override;

private:
	CirclePtr m_pCircle;
};

class RectBlock : public Block
{
public:
	RectBlock(const ElementType& type, RectPtr pRect) : Block(type), m_pRect(pRect) { }
	Vector GetPosition() const override
	{
		if (m_pRect)
			return m_pRect->getPosition();
		return { 0.f, 0.f };
	}
	sf::FloatRect GetBBox() const override
	{
		return m_pRect->getGlobalBounds();
	}
	Vector GetSize() const
	{
		if (m_pRect)
			return m_pRect->getSize();
		return { 0.f, 0.f };
	}
	RectPtr GetDrawable() const
	{
		return m_pRect;
	}
	bool IsIntersectedWithRect(const RectPtr& pRect, Vector& correctionVector) override;
	bool IsIntersectRect(const Vector& position, const Vector& size) override;

private:
	RectPtr m_pRect;
};

class TriangleBlock : public Block
{
public:
	TriangleBlock(const ElementType& type, TrianglePtr pTriangle) : Block(type), m_pTriangle(pTriangle) { }
	Vector GetPosition() const override
	{
		if (m_pTriangle)
			return m_pTriangle->getPosition();
		return { 0.f, 0.f };
	}
	TrianglePtr GetDrawable() const
	{
		return m_pTriangle;
	}
	virtual sf::FloatRect GetBBox() const
	{
		return m_pTriangle->getGlobalBounds();
	}
	bool IsIntersectedWithRect(const RectPtr& pRect, Vector& correctionVector) override;
	bool IsIntersectRect(const Vector& position, const Vector& size) override;

private:
	TrianglePtr m_pTriangle;
};

using BlockPtr = std::shared_ptr<Block>;
using CircleBlockPtr = std::shared_ptr<CircleBlock>;
using RectBlockPtr = std::shared_ptr<RectBlock>;
using TriangleBlockPtr = std::shared_ptr<TriangleBlock>;

inline CircleBlockPtr CreateCircleBlock(const ElementType& type, CirclePtr pCircle)
{
	return std::make_shared<CircleBlock>(type, pCircle);
}
inline RectBlockPtr CreateRectBlock(const ElementType& type, RectPtr pRect)
{
	return std::make_shared<RectBlock>(type, pRect);
}
inline TriangleBlockPtr CreateTriangleBlock(const ElementType& type, TrianglePtr pTriangle)
{
	return std::make_shared<TriangleBlock>(type, pTriangle);
}

template<typename T>
inline std::shared_ptr<T> Cast(BlockPtr pBlock)
{
	return (std::dynamic_pointer_cast<T>(pBlock));
}