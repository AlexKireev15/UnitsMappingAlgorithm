#pragma once
#include "../Common.h"
#include "Block.h"
#include <list>

class Placer
{
public:
	Placer(float worldSizeX, float worldSizeY, std::list<BlockPtr> blocks, std::list<UnitDrawablePtr> unitDrawables);
	void PlaceUnits(const std::string& lineUpName, size_t count, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f boundary, sf::Vector2f padding);
	void ConsoleMap() const;
	void AddBlock(BlockPtr pBlock);
	void SetUnitDrawables(std::list<UnitDrawablePtr> unitDrawables);

private:
	std::list<sf::Vector2f> GetLineLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	std::list<sf::Vector2f> GetWedgeLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	std::list<sf::Vector2f> GetSquareLineup(size_t count, sf::Vector2f boundary, sf::Vector2f padding) const;
	ElementType GetAreaStatus(const std::array<sf::Vector2f, 4u>& rect) const;
	ElementType GetAreaStatusFast(const std::array<sf::Vector2f, 4u>& rect) const;
	sf::Vector2f FindClosestFreeArea(const std::array<sf::Vector2f, 4u>& rect, const sf::Vector2f& position, const sf::Vector2f& lineupPosition, const sf::Vector2f& direction) const;
	int GetConnectivity(const sf::Vector2f& pos) const;
	void FixRotationByBlocks(UnitDrawablePtr& pUnitDrawable, const sf::Vector2f& position, const sf::Vector2f& direction) const;

	void FillMap(float worldSizeX, float worldSizeY);
	void FillDynamicMap(const sf::Vector2f& position);
	void SetUnitMapPosition(const std::array<sf::Vector2f, 4u>& rect);
	void ClearUnitMapPosition();
	void FixGunPosition(UnitDrawablePtr pUnitDrawable);
	void MakeHighShadows(const sf::Vector2f& lineupPos, const sf::Vector2f& lineupDir);
	void CheckHoles();

	std::list<BlockPtr> m_blocks;
	std::list<UnitDrawablePtr> m_unitDrawables;
	std::vector<std::vector<ElementType>> m_map;
	std::vector<std::vector<ElementType>> m_dynamicMap;
	std::vector<std::vector<int>> m_connectivityMap;
	sf::Vector2f m_worldSize;
	sf::Vector2f m_cellSize;
	std::vector<std::pair<size_t, size_t>> m_clearMapIdxs;
	int m_currentConnectivity;
};