#pragma once
#include "../Common.h"
#include "Block.h"

class Placer
{
public:
	Placer(float worldSizeX, float worldSizeY, std::list<BlockPtr> blocks, std::list<UnitDrawablePtr> unitDrawables);
	void PlaceUnits(const std::string& lineUpName, size_t count, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f boundary, sf::Vector2f padding);

private:
	std::list<sf::Vector2f> GetLineLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	std::list<sf::Vector2f> GetWedgeLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	std::list<sf::Vector2f> GetSquareLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	ElementType GetAreaStatus(const std::array<sf::Vector2f, 4u>& rect) const;
	ElementType GetAreaStatusFast(const std::array<sf::Vector2f, 4u>& rect) const;
	sf::Vector2f FindClosestFreeArea(const std::array<sf::Vector2f, 4u>& rect, const sf::Vector2f& position) const;

	void FillMap(float worldSizeX, float worldSizeY);
	void SetUnitMapPosition(const std::array<sf::Vector2f, 4u>& rect);
	void ClearUnitMapPosition();
	void FixGunPosition(UnitDrawablePtr pUnitDrawable);

	std::list<BlockPtr> m_blocks;
	std::list<UnitDrawablePtr> m_unitDrawables;
	std::vector<std::vector<ElementType>> m_map;
	sf::Vector2f m_worldSize;
	sf::Vector2f m_cellSize;
};