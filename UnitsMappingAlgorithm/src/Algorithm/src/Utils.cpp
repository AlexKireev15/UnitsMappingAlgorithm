//#include "..\Utils.h"
//
//bool IsIntersects(const sf::FloatRect& rect, const BlockPtr& pBlock)
//{
//    CircleBlockPtr pCircleBlock = Cast<CircleBlock>(pBlock);
//    if (pCircleBlock)
//        return IsIntersects(rect, pCircleBlock->GetDrawable());
//
//    RectBlockPtr pRectBlock = Cast<RectBlock>(pBlock);
//    if (pRectBlock)
//        return IsIntersects(rect, pRectBlock->GetDrawable());
//
//    /*TriangleBlockPtr pTriangleBlock = Cast<TriangleBlock>(pBlock);
//    if (pTriangleBlock)
//        return IsIntersects(rect, pTriangleBlock->GetDrawable());*/
//
//    return false;
//}
//
//bool IsPointInsideRect(std::array<Vector2f, 4u> rectPoints, const Vector2f& point)
//{
//    int isPositive = 0;
//    int isNegative = 0;
//    for (size_t idx = 0; idx < 4u; ++idx)
//    {
//        size_t jdx = (idx + 1) % 4u;
//        auto a = rectPoints[jdx] - rectPoints[idx];
//        auto b = point - rectPoints[idx];
//        auto product = CrossProductAbs(a, b);
//        if (product > 0.f)
//            isPositive = 1;
//        else if (product < 0.f)
//            isNegative = 1;
//    }
//
//    return isPositive ^ isNegative;
//}
//
//bool IsPointInsideTriangle(std::array<Vector2f, 3u> trianglePoints, const Vector2f& point)
//{
//    int isPositive = 0;
//    int isNegative = 0;
//    for (size_t idx = 0; idx < 3u; ++idx)
//    {
//        size_t jdx = (idx + 1) % 3u;
//        auto a = trianglePoints[jdx] - trianglePoints[idx];
//        auto b = point - trianglePoints[idx];
//        auto product = CrossProductAbs(a, b);
//        if (product > 0.f)
//            isPositive = 1;
//        else if (product < 0.f)
//            isNegative = 1;
//    }
//
//    return isPositive ^ isNegative;
//}
//
//bool IsPointInsideCircle(const Vector2f& p, const CirclePtr& pCircle)
//{
//    return GetAbs(p - pCircle->getPosition()) <= pCircle->getRadius();
//}
//
//int sign(float a)
//{
//    if (a > 0.f)
//        return 1;
//    if (a < 0.f)
//        return -1;
//    return 0;
//}
//
//bool ProjectPointOnLine(const Vector2f& p1, const Vector2f& p2, const Vector2f& point, Vector2f& result)
//{
//    Vector2f a = p2 - p1;
//    Vector2f b = point - p1;
//    result = a * DotProduct(a, b);
//    int s = sign(DotProduct(a, result - a));
//    result = p1 + result;
//    if (s > 0)
//        return false;
//    return true;
//}
//
//bool IsIntersects(const Vector2f& p1, const Vector2f& p2, const CirclePtr& pCircle)
//{
//    if (IsPointInsideCircle(p1, pCircle) || IsPointInsideCircle(p2, pCircle))
//        return true;
//
//    Vector2f projPoint;
//    if (ProjectPointOnLine(p1, p2, pCircle->getPosition(), projPoint))
//        return GetAbs(projPoint - pCircle->getPosition()) < pCircle->getRadius();
//
//    return false;
//}
//
//bool IsIntersects(const sf::FloatRect& rect, const CirclePtr& pCircle)
//{
//    auto rectPoints = GetPoints(rect);
//    return IsPointInsideRect(rectPoints, pCircle->getPosition()) ||
//        IsIntersects(rectPoints[0], rectPoints[1], pCircle) ||
//        IsIntersects(rectPoints[1], rectPoints[2], pCircle) ||
//        IsIntersects(rectPoints[2], rectPoints[3], pCircle) ||
//        IsIntersects(rectPoints[3], rectPoints[0], pCircle);
//}
//
//bool IsIntersects(const std::array<Vector2f, 4u>& rectPoints, const TrianglePtr& pTriangle)
//{
//    std::array<Vector2f, 3u> trianglePoints = GetPoints(pTriangle);
//    for (Vector2f& trianglePoint : trianglePoints)
//    {
//        if (IsPointInsideRect(rectPoints, trianglePoint))
//            return true;
//    }
//
//    for (auto& rectPoint : rectPoints)
//    {
//        if (IsPointInsideTriangle(trianglePoints, rectPoint))
//            return true;
//    }
//
//    return false;
//}
//
//bool TryIntersect(const std::array<Vector2f, 4u>& rectPointsA, const std::array<Vector2f, 4u>& rectPointsB)
//{
//    for (auto a : rectPointsA)
//    {
//        if (IsPointInsideRect(rectPointsB, a))
//            return true;
//    }
//    for (auto b : rectPointsB)
//    {
//        if (IsPointInsideRect(rectPointsA, b))
//            return true;
//    }
//    return false;
//}
//
//bool IsIntersects(const std::array<Vector2f, 4u>& rectPointsA, const std::array<Vector2f, 4u>& rectPointsB)
//{
//    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
//}
//
//bool IsIntersectsSegmentWithRay(const Vector2f& s1, const Vector2f& s2, const Vector2f& p1, const Vector2f& p2)
//{
//    const float a1 = s1.y - s2.y,
//                b1 = s2.x - s1.x,
//                c1 = s1.x * s2.y - s2.x * s1.y,
//                a2 = p1.y - p2.y,
//                b2 = p2.x - p1.x,
//                c2 = p1.x * p2.y - p2.x * p1.y;
//
//    float det = a1 * b2 - a2 * b1;
//    if (IsZero(det))
//        return false;
//    float x = (b1 * c2 - b2 * c1) / det,
//          y = (a2 * c1 - a1 * c2) / det;
//    Vector2f result = { x, y };
//
//    auto ray1 = p2 - p1;
//    auto ray2 = result - p1;
//    
//    return sign(DotProduct(s2 - s1, result - s1)) != sign(DotProduct(s2 - s1, result - s2)) && sign(DotProduct(p2 - result, ray1)) == sign(DotProduct(p2 - result, ray2));
//}
//
//bool IsIntersectsWithRay(const sf::FloatRect& rect, const Vector2f& rayPos, const Vector2f& rayDir, bool isIntersectIfInside /*= false*/)
//{
//    auto rectPoints = GetPoints(rect);
//    if (!isIntersectIfInside && IsPointInsideRect(rectPoints, rayPos))
//        return false;
//    Vector2f guide(-rayDir.y, rayDir.x);
//    Vector2f p1 = rayPos;
//    Vector2f p2 = rayPos + rayDir;
//
//    for (size_t idx = 0u; idx < 4u; ++idx)
//    {
//        auto s1 = rectPoints[idx];
//        auto s2 = rectPoints[(idx + 1) % 4];
//        if (IsIntersectsSegmentWithRay(s1, s2, p1, p2))
//            return true;
//    }
//    return false;
//}
//
//bool IsIntersects(const sf::FloatRect& rect, const RectPtr& pRect)
//{
//    auto rectPointsA = GetPoints(rect);
//    auto rectPointsB = GetPoints(pRect);
//    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
//}
//
//std::array<Vector2f, 4u> GetPoints(const RectPtr& pRect, const Vector2f& offset)
//{
//    std::array<Vector2f, 4u> points =
//    {
//        pRect->getPoint(0),
//        pRect->getPoint(1),
//        pRect->getPoint(2),
//        pRect->getPoint(3),
//    };
//    for (auto& point : points)
//    {
//        point = point + offset;
//    }
//    return points;
//}
//
//std::array<Vector2f, 3u> GetTriangleShadowPoints(const Vector2f& lineupPos, const Vector2f& lineupDir, BlockPtr pBlock)
//{
//    if (!pBlock)
//        return std::array<Vector2f, 3u>();
//
//    Vector2f guide(-lineupDir.y, lineupDir.x);
//    Vector2f secondPoint = lineupPos + guide;
//
//    Vector2f leftPoint, rightPoint;
//
//    CircleBlockPtr pCircleBlock = Cast<CircleBlock>(pBlock);
//    RectBlockPtr pRectBlock = Cast<RectBlock>(pBlock);
//    if (pCircleBlock)
//    {
//        auto translation = Normalize(guide) * pCircleBlock->GetRadius();
//        rightPoint = pCircleBlock->GetPosition() + translation;
//        leftPoint = pCircleBlock->GetPosition() - translation;
//    }
//    else if (pRectBlock)
//    {
//        auto leftRightPoint = GetLeftAndRightPoint(pRectBlock->GetBBox(), lineupPos, lineupDir);
//
//        leftPoint = leftRightPoint.first;
//        rightPoint = leftRightPoint.second;
//    }
//    else
//        return std::array<Vector2f, 3u>();
//
//    auto blockPos = pBlock->GetPosition();
//    auto thirdPoint = blockPos + Normalize(lineupPos - blockPos) * (sqrt(pBlock->GetBBox().width * pBlock->GetBBox().width + pBlock->GetBBox().height * pBlock->GetBBox().height));
//
//    return { leftPoint, rightPoint, thirdPoint };
//}
//
//std::pair<Vector2f, Vector2f> GetLeftAndRightPoint(const sf::FloatRect & rect, const Vector2f & dimPos, const Vector2f & dimDir)
//{
//    Vector2f guide(-dimDir.y, dimDir.x);
//    auto rectPoints = GetPoints(rect);
//    std::array<std::pair<Vector2f, Vector2f>, 4u> projPoints;
//    for (size_t idx = 0; idx < rectPoints.size(); ++idx)
//    {
//        Vector2f projPoint;
//        ProjectPointOnLine(dimPos, dimPos + guide, rectPoints[idx], projPoint);
//        projPoints[idx] = std::make_pair(rectPoints[idx], projPoint);
//    }
//    auto base = dimPos + guide;
//    auto getExtremePoints = [&projPoints](const Vector2f& base, bool isLeft)
//    {
//        std::vector<std::pair<Vector2f, Vector2f>> result;
//        int sideSign = isLeft ? 1 : -1;
//        for (const auto& p1 : projPoints)
//        {
//            bool isExtreme = true;
//            for (const auto& p2 : projPoints)
//            {
//                if (p1 == p2)
//                    continue;
//
//                int resultSign = sign(DotProduct(p2.second - p1.second, base));
//                if (resultSign == 0)
//                    continue;
//                if (resultSign != sideSign)
//                {
//                    isExtreme = false;
//                    break;
//                }
//            }
//            if (isExtreme)
//                result.push_back(p1);
//        }
//
//        return result;
//    };
//
//    auto getClosestPoint = [&dimPos](std::vector<std::pair<Vector2f, Vector2f>> pointsPairs)
//    {
//        float minDist = 10000.f;
//        Vector2f result;
//        for (auto [p, dummy] : pointsPairs)
//        {
//            float dist = GetAbs(p - dimPos);
//            if (minDist > dist)
//            {
//                minDist = dist;
//                result = p;
//            }
//        }
//        return result;
//    };
//
//    auto leftPoint = getClosestPoint(getExtremePoints(base, true));
//    auto rightPoint = getClosestPoint(getExtremePoints(base, false));
//
//    return { leftPoint, rightPoint };
//}
//
//std::array<Vector2f, 4u> GetPoints(const RectPtr& pRect)
//{
//    std::array<Vector2f, 4u> points =
//    {
//        pRect->getPoint(0),
//        pRect->getPoint(1),
//        pRect->getPoint(2),
//        pRect->getPoint(3),
//    };
//    sf::Transform t = pRect->getTransform();
//
//    for (auto& point : points)
//    {
//        point = t * point;
//    }
//    return points;
//}
//
//std::array<Vector2f, 4u> GetPoints(const sf::FloatRect& rect)
//{
//    return {
//        Vector2f(rect.left, rect.top),
//        Vector2f(rect.left, rect.top + rect.height),
//        Vector2f(rect.left + rect.width, rect.top + rect.height),
//        Vector2f(rect.left + rect.width, rect.top),
//    };;
//}
//
//std::array<Vector2f, 3u> GetPoints(const TrianglePtr& pTriangle)
//{
//    std::array<Vector2f, 3u> points =
//    {
//        pTriangle->getPoint(0),
//        pTriangle->getPoint(1),
//        pTriangle->getPoint(2),
//    };
//    sf::Transform t = pTriangle->getTransform();
//
//    for (auto& point : points)
//    {
//        point = t * point;
//    }
//    return points;
//}
