#include "../Units.h"
#include "../Utils.h"

using namespace sf;

Vector2f PlaceAlgorithm::Unit::GetPosition() const { return m_pRect->getPosition(); }

bool PlaceAlgorithm::Unit::SetPosition(const Vector2f & position)
{
	if (m_placer.CanMoveHere(*this, position))
	{
		m_pRect->setPosition(position);
		return true;
	}
	return false;
}

void PlaceAlgorithm::Unit::Move(const Vector2f & offset) { m_pRect->move(offset); }

void PlaceAlgorithm::Unit::Rotate(float angle, const Vector2f & center)
{
	RotateNoSelfAxis(angle, center);
	m_pRect->rotate(angle);
}

void PlaceAlgorithm::Unit::RotateNoSelfAxis(float angle, const Vector2f & center)
{
	Transform t;
	t.rotate(angle, center);
	m_pRect->setPosition(t.transformPoint(m_pRect->getPosition()));
}

void PlaceAlgorithm::Unit::UpdateLineupPosition(const Vector2f & groupPosition)
{
	m_lineupPosition = GetPosition() - groupPosition;
}

float PlaceAlgorithm::Unit::GetRotation() const { return m_pRect->getRotation(); }

RectPtr PlaceAlgorithm::Unit::GetDrawable() const { return m_pRect; }

Vector2f PlaceAlgorithm::Unit::GetBBox() const { return m_pRect->getSize() + m_padding; }

Vector2f PlaceAlgorithm::Unit::GetLineupPosition() const { return m_lineupPosition; }

bool PlaceAlgorithm::Unit::IsIntersectedWithRect(const Vector2f & position, const Vector2f & size, float rotationAngle, Vector2f & correctionVector)
{
	Vector2f cornerPoints[4] = 
	{
		position - size / 2.f,
		position + size / 2.f,
		Vector2f(position.x - size.x / 2.f, position.y + size.y / 2.f),
		Vector2f(position.x + size.x / 2.f, position.y - size.y / 2.f),
	};

	for (size_t idx = 0; idx < 4; ++idx)
	{
		Transform t;
		t.rotate(rotationAngle);

		Vector2f cornerPoint = t.transformPoint(cornerPoints[idx]);

		int flag = 0;
		for (size_t jdx = 0; jdx < 4; ++jdx)
		{
			Vector2f firstCorner = m_pRect->getTransform().transformPoint(m_pRect->getPoint(jdx));
			Vector2f secondCorner = m_pRect->getTransform().transformPoint(m_pRect->getPoint((jdx + 1) % 4));
			auto sideVector = secondCorner - firstCorner;
			auto toPointVector = cornerPoint - firstCorner;
			if (CrossProductAbs(sideVector, toPointVector) >= 0)
				flag++;
			else
				flag--;
		}

		if (flag > 3)
		{
			return true;
		}
	}

	return false;
}