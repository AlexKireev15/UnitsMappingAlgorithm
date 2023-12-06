#pragma once
#include "../Common.h"
#include "Block.h"
#include <list>

class Placer
{
public:
	Placer(float worldSizeX, float worldSizeY, std::list<BlockPtr> blocks, std::list<UnitDrawablePtr> unitDrawables);
	void PlaceUnits(const std::string& lineUpName, size_t count, Vector position, Vector direction, Vector boundary, Vector padding, bool dummy);
	void AddBlock(BlockPtr pBlock);
	void SetUnitDrawables(std::list<UnitDrawablePtr> unitDrawables);

private:
	std::list<Vector> GetLineLineup(size_t count, Vector boundary, Vector padding) const;
	std::list<Vector> GetWedgeLineup(size_t count, Vector boundary, Vector padding) const;
	std::list<Vector> GetSquareLineup(size_t count, Vector boundary, Vector padding, const float& angle) const;
	ElementType GetAreaStatus(const std::array<Vector, 4u>& rect) const;
	ElementType GetAreaStatusFast(const std::array<Vector, 4u>& rect) const;
	Vector FindClosestFreeArea(const std::array<Vector, 4u>& rect, const Vector& position, const Vector& lineupPosition, const Vector& direction) const;
	int GetConnectivity(const Vector& pos) const;
	void FixRotationByBlocks(UnitDrawablePtr& pUnitDrawable, const Vector& position, const Vector& direction) const;

	void FillMap(float worldSizeX, float worldSizeY);
	void FillDynamicMap(const Vector& position);
	void SetUnitMapPosition(const std::array<Vector, 4u>& rect);
	void ClearUnitMapPosition();
	void FixGunPosition(UnitDrawablePtr pUnitDrawable);
	void MakeHighShadows(Vector lineupPos, const Vector& lineupDir);
	void CheckHoles();

	std::list<BlockPtr> m_blocks;
	std::list<UnitDrawablePtr> m_unitDrawables;
	std::vector<std::vector<ElementType>> m_map;
	std::vector<std::vector<ElementType>> m_dynamicMap;
	std::vector<std::vector<int>> m_connectivityMap;
	Vector m_worldSize;
	Vector m_cellSize;
	std::vector<std::pair<size_t, size_t>> m_clearMapIdxs;
	int m_currentConnectivity;
};