#include "../Placer.h"
#include "../Utils.h"
#include <iostream>

using namespace sf;

Placer::Placer(float worldSizeX, float worldSizeY, std::list<BlockPtr> blocks, std::list<UnitDrawablePtr> unitDrawables) :
	m_blocks(blocks), m_unitDrawables(unitDrawables), m_worldSize(worldSizeX, worldSizeY)
{
	FillMap(worldSizeX, worldSizeY);
}

void Placer::FillMap(float worldSizeX, float worldSizeY)
{
	if (m_unitDrawables.empty())
		return;

	m_cellSize = m_unitDrawables.front()->body->getSize()/4.f;
	size_t squareCountX = worldSizeX / m_cellSize.x;
	size_t squareCountY = worldSizeY / m_cellSize.y;
	m_map.resize(squareCountY, std::vector<ElementType>(squareCountX, ElementType::FREE));

	for (size_t yIdx = 0; yIdx < m_map.size(); ++yIdx)
	{
		for (size_t xIdx = 0; xIdx < m_map[yIdx].size(); ++xIdx)
		{
			FloatRect cellCoords({ m_cellSize.x * xIdx, m_cellSize.y * yIdx }, m_cellSize);
			for (auto pBlock : m_blocks)
				if (IsIntersects(cellCoords, pBlock))
					m_map[yIdx][xIdx] = pBlock->GetType();
		}
	}
}

void Placer::SetUnitMapPosition(const std::array<sf::Vector2f, 4u>& rect)
{
	if (m_unitDrawables.empty())
		return;

	sf::Vector2i minIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y),
		maxIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y);
	for (size_t idx = 1; idx < rect.size(); ++idx)
	{
		size_t x = rect[idx].x / m_cellSize.x;
		size_t y = rect[idx].y / m_cellSize.y;
		if (minIdx.x > x)
			minIdx.x = x;
		if (minIdx.y > y)
			minIdx.y = y;
		if (maxIdx.x < x)
			maxIdx.x = x;
		if (maxIdx.y < y)
			maxIdx.y = y;
	}

	for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
	{
		if (ydx < 0)
			continue;
		if (ydx >= m_map.size())
			break;
		for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
		{
			if (xdx < 0)
				continue;
			if (xdx >= m_map[ydx].size())
				break;

			std::array<sf::Vector2f, 4u> field =
			{
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * ydx),
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * ydx)

			};

			if (IsIntersects(rect, field))
				m_map[ydx][xdx] = ElementType::UNIT;
		}
	}
}

void Placer::ClearUnitMapPosition()
{
	if (m_unitDrawables.empty())
		return;

	for (auto& pUnit : m_unitDrawables)
	{
		auto bboxPoints = GetPoints(pUnit->body->getGlobalBounds());
		sf::Vector2i minIdx(bboxPoints[0].x / m_cellSize.x, bboxPoints[0].y / m_cellSize.y),
			maxIdx(bboxPoints[0].x / m_cellSize.x, bboxPoints[0].y / m_cellSize.y);
		for (size_t idx = 1; idx < bboxPoints.size(); ++idx)
		{
			size_t x = bboxPoints[idx].x / m_cellSize.x;
			size_t y = bboxPoints[idx].y / m_cellSize.y;
			if (minIdx.x > x)
				minIdx.x = x;
			if (minIdx.y > y)
				minIdx.y = y;
			if (maxIdx.x < x)
				maxIdx.x = x;
			if (maxIdx.y < y)
				maxIdx.y = y;
		}

		for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
		{
			if (ydx < 0)
				continue;
			if (ydx >= m_map.size())
				break;
			for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
			{
				if (xdx < 0)
					continue;
				if (xdx >= m_map[ydx].size())
					break;

				if (m_map[ydx][xdx] == ElementType::UNIT)
					m_map[ydx][xdx] = ElementType::FREE;
			}
		}
	}
}

void Placer::FixGunPosition(UnitDrawablePtr pUnitDrawable)
{
	sf::Vector2f dirSum;
	sf::Vector2f gunDir = pUnitDrawable->GetGunDirection();

	sf::Vector2f defaultGunDir = { 0.f, 1.f };
	sf::Transform defaultGunDirT;
	defaultGunDirT.rotate(pUnitDrawable->GetRotation());
	defaultGunDir = defaultGunDirT.transformPoint(defaultGunDir);

	bool found = false;
	for (auto pBlock : m_blocks)
	{
		if (pBlock->GetType() == ElementType::BLOCK_HIGH)
		{
			sf::Vector2f position = pBlock->GetPosition();
			sf::Vector2f dir = position - pUnitDrawable->gun->getPosition();
			float distance = GetAbs(dir);
			if (distance < 100.f && abs(GetAngleBetween(defaultGunDir, Normalize(dir))) >= 135)
			{
				dirSum += Normalize(dir);
				found = true;
			}
		}
	}

	if (!found)
	{
		dirSum = defaultGunDir;
	}
	sf::Vector2f ndir = Normalize(dirSum);
	float angle = GetAngleBetween(gunDir, ndir);
	pUnitDrawable->RotateGun(angle);
	pUnitDrawable->SetGunDirection(ndir);
}

void Placer::MakeHighShadows(const sf::Vector2f& lineupPos, const sf::Vector2f& lineupDir)
{
	if (m_unitDrawables.empty() || m_blocks.empty())
		return;

	for (auto& pBlock : m_blocks)
	{
		if (!pBlock || pBlock->GetType() != ElementType::BLOCK_HIGH)
			continue;

		std::array<sf::Vector2f, 3u> shadowPoints = GetTriangleShadowPoints(lineupPos, lineupDir, pBlock);
		TriangleBlockPtr pShadowBlock = CreateTriangleBlock(ElementType::BLOCK_HIGH, CreateTriangle(shadowPoints));

		auto bounds = GetPoints(pShadowBlock->GetDrawable()->getGlobalBounds());

		sf::Vector2i minIdx(bounds[0].x / m_cellSize.x, bounds[0].y / m_cellSize.y),
			maxIdx(bounds[0].x / m_cellSize.x, bounds[0].y / m_cellSize.y);
		for (size_t idx = 1; idx < bounds.size(); ++idx)
		{
			size_t x = bounds[idx].x / m_cellSize.x;
			size_t y = bounds[idx].y / m_cellSize.y;
			if (minIdx.x > x)
				minIdx.x = x;
			if (minIdx.y > y)
				minIdx.y = y;
			if (maxIdx.x < x)
				maxIdx.x = x;
			if (maxIdx.y < y)
				maxIdx.y = y;
		}

		for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
		{
			if (ydx < 0)
				continue;
			if (ydx >= m_map.size())
				break;
			for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
			{
				if (xdx < 0)
					continue;
				if (xdx >= m_map[ydx].size())
					break;

				std::array<sf::Vector2f, 4u> field =
				{
					sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * ydx),
					sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * (ydx + 1u)),
					sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * (ydx + 1u)),
					sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * ydx)

				};

				if (IsIntersects(field, pShadowBlock->GetDrawable()))
				{
					m_map[ydx][xdx] = ElementType::BLOCK_HIGH;
					m_clearMapIdxs.push_back(std::make_pair(ydx, xdx));
				}
			}
		}
	}
	
}

std::list<Vector2f> Placer::GetLineLineup(size_t count, Vector2f boundary, Vector2f padding) const
{
	std::list<Vector2f> result;

	float spacing = padding.x;
	float totalSpace = boundary.x * count + (count > 0 ? (spacing * (count - 1)) : 0);
	for (size_t idx = 0; idx < count; ++idx)
	{
		result.push_back({ boundary.x / 2.f + (boundary.x + spacing) * idx - totalSpace / 2.f, 0.f });
	}

	return result;
}

std::list<sf::Vector2f> Placer::GetWedgeLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const
{
	std::list<Vector2f> result;

	float spacing = padding.x;
	float totalSpace = boundary.x * count + (count > 0 ? (spacing * (count - 1)) : 0);
	size_t centerIdx = count / 2u;
	float currentY = 0.f;
	for (size_t idx = 0; idx < count; ++idx)
	{
		result.push_back({ boundary.x / 2.f + (boundary.x + spacing) * idx - totalSpace / 2.f, currentY });
		currentY -= (idx >= centerIdx ? -1.f : 1.f) * boundary.y / 2.f;
	}

	return result;
}

std::list<sf::Vector2f> Placer::GetSquareLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const
{
	std::list<Vector2f> result;

	size_t sizeX = (size_t)(sqrt(count) + 1);
	size_t sizeY = count / sizeX + 1;
	float spacing = padding.x;
	float totalSpace = boundary.x * sizeX + (sizeX > 0 ? (spacing * (sizeX - 1)) : 0);

	size_t totalPlaced = 0;
	for (size_t idx = 0; idx < sizeY && totalPlaced < count; ++idx)
	{
		float currentY = (idx - sizeY / 2.f + 0.5f) * (boundary.y + padding.y);
		for (size_t jdx = 0; jdx < sizeX && totalPlaced < count; ++jdx, ++totalPlaced)
		{
			result.push_back({ boundary.x / 2.f + (boundary.x + spacing) * jdx - totalSpace / 2.f,  currentY });
		}
	}

	return result;
}

ElementType Placer::GetAreaStatus(const std::array<sf::Vector2f, 4u>& rect) const
{
	if (m_unitDrawables.empty())
		return ElementType::FREE;

	sf::Vector2i minIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y),
		maxIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y);
	for (size_t idx = 1; idx < rect.size(); ++idx)
	{
		size_t x = rect[idx].x / m_cellSize.x;
		size_t y = rect[idx].y / m_cellSize.y;
		if (minIdx.x > x)
			minIdx.x = x;
		if (minIdx.y > y)
			minIdx.y = y;
		if (maxIdx.x < x)
			maxIdx.x = x;
		if (maxIdx.y < y)
			maxIdx.y = y;
	}

	for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
	{
		if (ydx < 0)
			continue;
		if (ydx >= m_map.size())
			break;
		for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
		{
			if (xdx < 0)
				continue;
			if (xdx >= m_map[ydx].size())
				break;
			if (m_map[ydx][xdx] == ElementType::FREE /*|| m_map[ydx][xdx] == ElementType::UNIT*/)
				continue;

			std::array<sf::Vector2f, 4u> field =
			{
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * ydx),
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * ydx)
				
			};

			if (IsIntersects(rect, field))
				return m_map[ydx][xdx];
		}
	}

	return ElementType::FREE;
}

ElementType Placer::GetAreaStatusFast(const std::array<sf::Vector2f, 4u>& rect) const
{
	if (m_unitDrawables.empty())
		return ElementType::FREE;

	sf::Vector2i minIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y),
		maxIdx(rect[0].x / m_cellSize.x, rect[0].y / m_cellSize.y);
	for (size_t idx = 1; idx < rect.size(); ++idx)
	{
		size_t x = rect[idx].x / m_cellSize.x;
		size_t y = rect[idx].y / m_cellSize.y;
		if (minIdx.x > x)
			minIdx.x = x;
		if (minIdx.y > y)
			minIdx.y = y;
		if (maxIdx.x < x)
			maxIdx.x = x;
		if (maxIdx.y < y)
			maxIdx.y = y;
	}

	for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
	{
		if (ydx < 0)
			continue;
		if (ydx >= m_map.size())
			break;
		for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
		{
			if (xdx < 0)
				continue;
			if (xdx >= m_map[ydx].size())
				break;
			if (m_map[ydx][xdx] == ElementType::FREE)
				continue;

			std::array<sf::Vector2f, 4u> field =
			{
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * ydx),
				sf::Vector2f(m_cellSize.x * xdx, m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * (ydx + 1u)),
				sf::Vector2f(m_cellSize.x * (xdx + 1u), m_cellSize.y * ydx)

			};

			
			return m_map[ydx][xdx];
		}
	}

	return ElementType::FREE;
}

sf::Vector2f Placer::FindClosestFreeArea(const std::array<sf::Vector2f, 4u>& rect, const sf::Vector2f& position) const
{
	size_t shiftAbs = 1;
	
	auto points = rect;
	while (GetAreaStatus(points) != ElementType::FREE)
	{
		for (float angle = 0.f; angle < 360.f && GetAreaStatusFast(points) != ElementType::FREE; angle += 15.f)
		{
			points = rect;
			sf::Transform t;
			t.rotate(angle, { 0.f, 0.f });
			sf::Vector2f shiftDir = t * sf::Vector2f(0.f, 1.f);

			for (auto& point : points)
			{
				point.x += shiftDir.x * shiftAbs * m_cellSize.x;
				point.y += shiftDir.y * shiftAbs * m_cellSize.y;
			}
		}
		shiftAbs++;
	}

	auto offset = rect[0] - points[0];
	return position - offset;
}

void Placer::PlaceUnits(const std::string& lineUpName, size_t count, Vector2f position, Vector2f direction, Vector2f boundary, Vector2f padding)
{
	std::list<Vector2f> lineupTranslations;
	if(lineUpName == "line")
		lineupTranslations = GetLineLineup(count, boundary, padding);
	if(lineUpName == "wedge")
		lineupTranslations = GetWedgeLineup(count, boundary, padding);
	if(lineUpName == "square")
		lineupTranslations = GetSquareLineup(count, boundary, padding);

	Vector2f Oy = { 0.f, -1.f };
	float angle = GetAngleBetween(direction, Oy);

	ClearUnitMapPosition();

	auto unitDrawableIt = m_unitDrawables.begin();
	for (auto lineupTranslation : lineupTranslations)
	{
		if (unitDrawableIt == m_unitDrawables.end())
			break;
		auto pUnitDrawable = *unitDrawableIt;

		auto unitPosition = position + lineupTranslation;
		Transform t;
		t.rotate(angle, position);
		unitPosition = t.transformPoint(unitPosition);
		pUnitDrawable->SetPosition(unitPosition);
		pUnitDrawable->SetRotation(angle);
		auto points = GetPoints(pUnitDrawable->body);

		/*for (auto p : m_clearMapIdxs)
		{
			m_map[p.first][p.second] = ElementType::FREE;
		}
		m_clearMapIdxs.clear();*/
		MakeHighShadows(position, direction);

		if (GetAreaStatus(points) != ElementType::FREE)
		{
			unitPosition = FindClosestFreeArea(points, unitPosition);
			pUnitDrawable->SetPosition(unitPosition);
		}
		points = GetPoints(pUnitDrawable->body);
		sf::Transform scaleT;
		scaleT.scale({ 0.75f, 0.75f }, pUnitDrawable->body->getPosition());
		for (auto& p : points)
		{
			p = scaleT.transformPoint(p);
		}
		SetUnitMapPosition(points);

		//FixGunPosition(pUnitDrawable);

		++unitDrawableIt;
	}
}

void Placer::ConsoleMap() const
{
	for (auto y : m_map)
	{
		for (auto x : y)
		{
			std::cout << (x == ElementType::FREE ? " " : "1") << " ";
		}
		std::cout << std::endl;
	}
}

void Placer::AddBlock(BlockPtr pBlock)
{
	//m_blocks.push_back(pBlock);
	//for (size_t yIdx = 0; yIdx < m_map.size(); ++yIdx)
	//{
	//	for (size_t xIdx = 0; xIdx < m_map[yIdx].size(); ++xIdx)
	//	{
	//		FloatRect cellCoords({ m_cellSize.x * xIdx, m_cellSize.y * yIdx }, m_cellSize);
	//		if (IsIntersects(cellCoords, pBlock))
	//			m_map[yIdx][xIdx] = pBlock->GetType();
	//	}
	//}

	auto bboxPoints = GetPoints(pBlock->GetBBox());
	sf::Vector2i minIdx(bboxPoints[0].x / m_cellSize.x, bboxPoints[0].y / m_cellSize.y),
		maxIdx(bboxPoints[0].x / m_cellSize.x, bboxPoints[0].y / m_cellSize.y);
	for (size_t idx = 1; idx < bboxPoints.size(); ++idx)
	{
		size_t x = bboxPoints[idx].x / m_cellSize.x;
		size_t y = bboxPoints[idx].y / m_cellSize.y;
		if (minIdx.x > x)
			minIdx.x = x;
		if (minIdx.y > y)
			minIdx.y = y;
		if (maxIdx.x < x)
			maxIdx.x = x;
		if (maxIdx.y < y)
			maxIdx.y = y;
	}

	for (size_t ydx = minIdx.y; ydx <= maxIdx.y; ++ydx)
	{
		if (ydx < 0)
			continue;
		if (ydx >= m_map.size())
			break;
		for (size_t xdx = minIdx.x; xdx <= maxIdx.x; ++xdx)
		{
			if (xdx < 0)
				continue;
			if (xdx >= m_map[ydx].size())
				break;
			if (m_map[ydx][xdx] == ElementType::BLOCK_HIGH || m_map[ydx][xdx] == ElementType::BLOCK_LOW /*|| m_map[ydx][xdx] == ElementType::UNIT*/)
				continue;

			FloatRect cellCoords({ m_cellSize.x * xdx, m_cellSize.y * ydx }, m_cellSize);
			if (IsIntersects(cellCoords, pBlock))
				m_map[ydx][xdx] = pBlock->GetType();
		}
	}

}

void Placer::SetUnitDrawables(std::list<UnitDrawablePtr> unitDrawables)
{
	m_unitDrawables.clear();
	m_unitDrawables = unitDrawables;
}
