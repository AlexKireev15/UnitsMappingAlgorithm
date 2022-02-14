#include "..\PlaceAlgorithm.h"
#include <cmath>

#include "../Units.h"
#include "../Utils.h"

using namespace PlaceAlgorithm;

bool IsInside(const FloatRect& a, const FloatRect& b)
{
	return a.contains(b.left, b.top) &&
		a.contains(b.left + b.width, b.top) &&
		a.contains(b.left, b.top + b.height) &&
		a.contains(b.left + b.width, b.top + b.height);
}

Vector2f GetCenter(const FloatRect& rect)
{
	return Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}

bool GetIntersection(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2, Vector2f& intersection)
{
	float A1 = a2.y - a1.y;
	float B1 = a1.x - a2.x;
	float C1 = a2.x * a1.y - a1.x * a2.y;

	float A2 = b2.y - b1.y;
	float B2 = b1.x - b2.x;
	float C2 = b2.x * b1.y - b1.x * b2.y;

	float det = A1 * B2 - A2 * B1;
	if (abs(det) <= 0.e-10f)
		return false;

	intersection.x = -(C1 * B2 - C2 * B1) / (A1* B2 - A2 * B1);
	intersection.y = -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

	Vector2f v1 = (intersection - b1);
	Vector2f v2 = (intersection - b2);

	float dot = v1.x * v2.x + v1.y * v2.y;

	return dot < 0.f;
}

Vector2f GetIntersection(Vector2f a, Vector2f b, FloatRect rect)
{
	Vector2f intersection;
	Vector2f corners[4] =
	{
		Vector2f(rect.left, rect.top),
		Vector2f(rect.left, rect.top + rect.height),
		Vector2f(rect.left + rect.width, rect.top),
		Vector2f(rect.left + rect.width, rect.top + rect.height),
	};

	for (size_t idx = 0; idx < 4; ++idx)
	{
		if (GetIntersection(a, b, corners[idx], corners[(idx + 1) % 4], intersection))
		{
			return intersection;
		}
	}

	return intersection;
}

std::list<Vector2f> PlaceAlgorithm::Placer::GetLineLineup(size_t count, Vector2f boundary, Vector2f padding) const
{
	std::list<Vector2f> result;
	//result.reserve(count);

	float spacing = padding.x;
	float totalSpace = boundary.x * count + (count > 0 ? (spacing * (count - 1)) : 0);
	for (size_t idx = 0; idx < count; ++idx)
	{
		result.push_back({ boundary.x / 2.f + (boundary.x + spacing) * idx - totalSpace / 2.f, 0.f });
	}

	return result;
}

UnitGroup PlaceAlgorithm::Placer::Place(const std::string & lineupName, size_t count, Vector2f position, Vector2f direction, Vector2f boundary, Vector2f padding)
{
	std::list<Vector2f> lineupTranslations = GetLineLineup(count, boundary, padding);

	Vector2f Oy = { 0.f, 1.f };
	float angle = GetAngleBetween(direction, Oy);

	std::list<UnitPtr> units;
	for (auto lineupTranslation : lineupTranslations)
	{
		auto unit = CreateUnit(CreateRect(boundary, Color::White, position + lineupTranslation), padding, lineupTranslation, *this);
		units.push_back(unit);
		m_blocks.push_back(unit);
	}
	UnitGroup group(position, units);
	group.Rotate(angle);

	return group;
}

bool PlaceAlgorithm::Placer::IsFree(const Vector2f & position, const UnitPtr& pUnit) const
{
	for (auto blockPtr : m_blocks)
	{
		if (blockPtr.get() == pUnit.get() || !blockPtr)
			continue;

		if (blockPtr->IsIntersectedWith(position, pUnit->GetRadius()))
			return false;
	}
	return true;
}

void PlaceAlgorithm::Placer::Replace(UnitGroup & unitGroup)
{
	auto unitsList = unitGroup.GetUnits();
	auto groupPosition = unitGroup.GetPosition();
	auto IsReplaceNeeded = [this](UnitPtr pUnit)
	{
		for (auto pBlock : m_blocks)
		{
			if (pBlock.get() == pUnit.get())
				continue;
			if (pBlock->IsIntersectedWith(pUnit->GetPosition(), pUnit->GetRadius()))
				return true;
		}
		return false;
	};
	auto GetPossiblePositions = [this](UnitPtr pUnit, const sf::Vector2f& startPosition, float radius)
	{
		std::vector<sf::Vector2f> result;
		for (float rotationAngle = 0.f; rotationAngle <= 360.f; rotationAngle += 5.f)
		{
			Transform t;
			t.translate({ 0.f, rotationAngle >= 180.f ? -radius : radius });
			t.rotate(rotationAngle, startPosition);
			sf::Vector2f resultPosition = t.transformPoint(startPosition);
			if (IsFree(resultPosition, pUnit))
				result.push_back(resultPosition);
		}

		return result;
	};

	for (auto unitPtr : unitsList)
	{
		if (!IsReplaceNeeded(unitPtr))
		{
			continue;
		}

		auto startPosition = groupPosition + unitPtr->GetLineupPosition();
		std::vector<sf::Vector2f> possiblePositions;
		float offset = unitPtr->GetRadius() * 0.5f;
		while (possiblePositions.empty())
		{
			possiblePositions = GetPossiblePositions(unitPtr, startPosition, offset);
			offset += unitPtr->GetRadius();
		}

		sf::Vector2f minimalDistPosition = possiblePositions.front();
		float minimalDist = GetAbs(startPosition - possiblePositions.front());
		for (auto pos : possiblePositions)
		{
			float dist = GetAbs(startPosition - pos);
			if (dist < minimalDist)
			{
				minimalDist = dist;
				minimalDistPosition = pos;
			}
		}

		unitPtr->SetPosition(minimalDistPosition);
		//unitPtr->SetPosition(unitPtr->GetPosition() + sf::Vector2f(20.f, 20.f));
		/*if (IsFree(startPosition))
		{
			continue;
		}*/
	}
}

bool PlaceAlgorithm::Placer::CanMoveHere(Unit & unit, Vector2f position) const
{
	bool isIntersected = false;
	Vector2f correctionVectorsSum;
	for (auto& pBlock : m_blocks)
	{
		Vector2f correctionVector;
		if (pBlock->IsIntersectedWithRect(position, unit.GetBBox(), unit.GetRotation(), correctionVector))
		{
			isIntersected = true;
			correctionVectorsSum += correctionVector;
		}
	}

	if (isIntersected)
	{
		for (auto& pBlock : m_blocks)
		{
			Vector2f correctionVector;
			if (pBlock->IsIntersectedWithRect(position + correctionVectorsSum, unit.GetBBox(), unit.GetRotation(), correctionVector))
			{
				return false;
			}
		}
	}

	return true;
}

void PlaceAlgorithm::Placer::Update(UnitGroup& group) const
{
	for (auto& pUnit : group.GetUnits())
	{
		Vector2f correctionVectorsSum;
		for (auto& pBlock : m_blocks)
		{
			Vector2f correctionVector;
			if (pBlock->IsIntersectedWithRect(pUnit->GetPosition(), pUnit->GetBBox(), pUnit->GetRotation(), correctionVector))
			{
				correctionVectorsSum += correctionVector;
			}
		}
		pUnit->Move(correctionVectorsSum);
	}
}
