//#pragma once
//#include "../Common.h"
//#include "Block.h"
//#include <list>
//
//class Placer
//{
//public:
//	Placer(float worldSizeX, float worldSizeY, std::list<BlockPtr> blocks, std::list<UnitDrawablePtr> unitDrawables);
//	void PlaceUnits(const std::string& lineUpName, size_t count, Vector2f position, Vector2f direction, Vector2f boundary, Vector2f padding, bool dummy);
//	void ConsoleMap() const;
//	void AddBlock(BlockPtr pBlock);
//	void SetUnitDrawables(std::list<UnitDrawablePtr> unitDrawables);
//
//private:
//	std::list<Vector2f> GetLineLineup(size_t count, Vector2f boundary, Vector2f padding) const;
//	std::list<Vector2f> GetWedgeLineup(size_t count, Vector2f boundary, Vector2f padding) const;
//	std::list<Vector2f> GetSquareLineup(size_t count, Vector2f boundary, Vector2f padding, const float& angle) const;
//	ElementType GetAreaStatus(const std::array<Vector2f, 4u>& rect) const;
//	ElementType GetAreaStatusFast(const std::array<Vector2f, 4u>& rect) const;
//	Vector2f FindClosestFreeArea(const std::array<Vector2f, 4u>& rect, const Vector2f& position, const Vector2f& lineupPosition, const Vector2f& direction) const;
//	int GetConnectivity(const Vector2f& pos) const;
//	void FixRotationByBlocks(UnitDrawablePtr& pUnitDrawable, const Vector2f& position, const Vector2f& direction) const;
//
//	void FillMap(float worldSizeX, float worldSizeY);
//	void FillDynamicMap(const Vector2f& position);
//	void SetUnitMapPosition(const std::array<Vector2f, 4u>& rect);
//	void ClearUnitMapPosition();
//	void FixGunPosition(UnitDrawablePtr pUnitDrawable);
//	void MakeHighShadows(const Vector2f& lineupPos, const Vector2f& lineupDir);
//	void CheckHoles();
//
//	std::list<BlockPtr> m_blocks;
//	std::list<UnitDrawablePtr> m_unitDrawables;
//	std::vector<std::vector<ElementType>> m_map;
//	std::vector<std::vector<ElementType>> m_dynamicMap;
//	std::vector<std::vector<int>> m_connectivityMap;
//	Vector2f m_worldSize;
//	Vector2f m_cellSize;
//	std::vector<std::pair<size_t, size_t>> m_clearMapIdxs;
//	int m_currentConnectivity;
//};