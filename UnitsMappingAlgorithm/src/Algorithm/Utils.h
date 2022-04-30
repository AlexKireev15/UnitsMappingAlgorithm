//#pragma once
//#include "../Common.h"
//#include "../Block.h"
//
//#include <array>
//
////#define M_PI 3.14159265358979323846f
//#define EPS 1.e-10
//
//inline bool IsZero(float v)
//{
//	return abs(v) <= EPS;
//}
//
//inline float GetAbs(Vector2f v)
//{
//	return sqrt(v.x * v.x + v.y * v.y);
//}
//
//inline Vector2f Normalize(Vector2f v)
//{
//	v /= GetAbs(v);
//	return v;
//}
//
//inline float CrossProductAbs(const Vector2f& a, const Vector2f& b)
//{
//	return a.x * b.y - a.y * b.x;
//}
//
//inline float DotProduct(const Vector2f& a, const Vector2f& b)
//{
//	return a.x * b.x + a.y * b.y;
//}
//
//inline float GetAngleBetween(const Vector2f& a, const Vector2f& b)
//{
//	float dot = a.x * b.x + a.y * b.y;
//	float det = a.x * b.y - a.y * b.x;
//	if (IsZero(dot))
//		return (det > 0 ? 1.f : -1.f ) * 90.f;
//	if (IsZero(det))
//		return 0.f;
//	return std::atan2(det, dot) * 180.f / (float)M_PI;
//}
//
//bool IsIntersects(const sf::FloatRect& rect, const BlockPtr& pBlock);
//bool IsIntersects(const sf::FloatRect& rect, const CirclePtr& pCircle);
//bool IsIntersects(const sf::FloatRect& rect, const RectPtr& pRect);
//bool IsIntersects(const std::array<Vector2f, 4u>& rect, const TrianglePtr& pTriangle);
//bool IsIntersects(const std::array<Vector2f, 4u>& rectPointsA, const std::array<Vector2f, 4u>& rectPointsB);
//bool IsIntersectsWithRay(const sf::FloatRect& rect, const Vector2f& lineupPos, const Vector2f& lineupDir, bool isIntersectIfInside = false);
//
//std::array<Vector2f, 4u> GetPoints(const RectPtr& pRect);
//std::array<Vector2f, 4u> GetPoints(const sf::FloatRect& rect);
//std::array<Vector2f, 4u> GetPoints(const RectPtr& pRect, const Vector2f& offset);
//std::array<Vector2f, 3u> GetPoints(const TrianglePtr& pTriangle);
//
//std::array<Vector2f, 3u> GetTriangleShadowPoints(const Vector2f& lineupPos, const Vector2f& lineupDir, BlockPtr pBlock);
//std::pair<Vector2f, Vector2f> GetLeftAndRightPoint(const sf::FloatRect& rect, const Vector2f& dimPos, const Vector2f& dimDir);
