#include "..\Utils.h"

bool IsIntersects(const sf::FloatRect& rect, const BlockPtr& pBlock)
{
    CircleBlockPtr pCircleBlock = Cast<CircleBlock>(pBlock);
    if (pCircleBlock)
        return IsIntersects(rect, pCircleBlock->GetDrawable());

    RectBlockPtr pRectBlock = Cast<RectBlock>(pBlock);
    if (pRectBlock)
        return IsIntersects(rect, pRectBlock->GetDrawable());

    return false;
}

bool IsPointInsideRect(std::array<Vector, 4u> rectPoints, const Vector& point)
{
    int isPositive = 0;
    int isNegative = 0;
    for (size_t idx = 0; idx < 4u; ++idx)
    {
        size_t jdx = (idx + 1) % 4u;
        auto a = rectPoints[jdx] - rectPoints[idx];
        auto b = point - rectPoints[idx];
        auto product = CrossProductAbs(a, b);
        if (product > 0.f)
            isPositive = 1;
        else if (product < 0.f)
            isNegative = 1;
    }

    return isPositive ^ isNegative;
}

bool IsPointInsideTriangle(std::array<Vector, 3u> trianglePoints, const Vector& point)
{
    int isPositive = 0;
    int isNegative = 0;
    for (size_t idx = 0; idx < 3u; ++idx)
    {
        size_t jdx = (idx + 1) % 3u;
        auto a = trianglePoints[jdx] - trianglePoints[idx];
        auto b = point - trianglePoints[idx];
        auto product = CrossProductAbs(a, b);
        if (product > 0.f)
            isPositive = 1;
        else if (product < 0.f)
            isNegative = 1;
    }

    return isPositive ^ isNegative;
}

bool IsPointInsideCircle(const Vector& p, const CirclePtr& pCircle)
{
    return GetAbs(p - pCircle->getPosition()) <= pCircle->getRadius();
}

int sign(float a)
{
    if (a > 0.f)
        return 1;
    if (a < 0.f)
        return -1;
    return 0;
}

bool ProjectPointOnLine(const Vector& p1, const Vector& p2, const Vector& point, Vector& result)
{
    Vector a = p2 - p1;
    Vector b = point - p1;
    result = a * DotProduct(a, b);
    int s = sign(DotProduct(a, result - a));
    result = p1 + result;
    if (s > 0)
        return false;
    return true;
}

bool IsIntersects(const Vector& p1, const Vector& p2, const CirclePtr& pCircle)
{
    if (IsPointInsideCircle(p1, pCircle) || IsPointInsideCircle(p2, pCircle))
        return true;

    Vector projPoint;
    if (ProjectPointOnLine(p1, p2, pCircle->getPosition(), projPoint))
        return GetAbs(projPoint - pCircle->getPosition()) < pCircle->getRadius();

    return false;
}

bool IsIntersects(const sf::FloatRect& rect, const CirclePtr& pCircle)
{
    auto rectPoints = GetPoints(rect);
    return IsPointInsideRect(rectPoints, pCircle->getPosition()) ||
        IsIntersects(rectPoints[0], rectPoints[1], pCircle) ||
        IsIntersects(rectPoints[1], rectPoints[2], pCircle) ||
        IsIntersects(rectPoints[2], rectPoints[3], pCircle) ||
        IsIntersects(rectPoints[3], rectPoints[0], pCircle);
}

bool IsIntersects(const std::array<Vector, 4u>& rectPoints, const TrianglePtr& pTriangle)
{
    std::array<Vector, 3u> trianglePoints = GetPoints(pTriangle);
    for (Vector& trianglePoint : trianglePoints)
    {
        if (IsPointInsideRect(rectPoints, trianglePoint))
            return true;
    }

    for (auto& rectPoint : rectPoints)
    {
        if (IsPointInsideTriangle(trianglePoints, rectPoint))
            return true;
    }

    return false;
}

bool TryIntersect(const std::array<Vector, 4u>& rectPointsA, const std::array<Vector, 4u>& rectPointsB)
{
    for (auto a : rectPointsA)
    {
        if (IsPointInsideRect(rectPointsB, a))
            return true;
    }
    for (auto b : rectPointsB)
    {
        if (IsPointInsideRect(rectPointsA, b))
            return true;
    }
    return false;
}

bool IsIntersects(const std::array<Vector, 4u>& rectPointsA, const std::array<Vector, 4u>& rectPointsB)
{
    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
}

bool IsIntersectsSegmentWithRay(const Vector& s1, const Vector& s2, const Vector& p1, const Vector& p2)
{
    const float a1 = s1.y - s2.y,
                b1 = s2.x - s1.x,
                c1 = s1.x * s2.y - s2.x * s1.y,
                a2 = p1.y - p2.y,
                b2 = p2.x - p1.x,
                c2 = p1.x * p2.y - p2.x * p1.y;

    float det = a1 * b2 - a2 * b1;
    if (IsZero(det))
        return false;
    float x = (b1 * c2 - b2 * c1) / det,
          y = (a2 * c1 - a1 * c2) / det;
    Vector result = { x, y };

    auto ray1 = p2 - p1;
    auto ray2 = result - p1;
    
    return sign(DotProduct(s2 - s1, result - s1)) != sign(DotProduct(s2 - s1, result - s2)) && sign(DotProduct(p2 - result, ray1)) == sign(DotProduct(p2 - result, ray2));
}

bool IsIntersectsWithRay(const sf::FloatRect& rect, const Vector& rayPos, const Vector& rayDir, bool isIntersectIfInside /*= false*/)
{
    auto rectPoints = GetPoints(rect);
    if (!isIntersectIfInside && IsPointInsideRect(rectPoints, rayPos))
        return false;
    Vector guide(-rayDir.y, rayDir.x);
    Vector p1 = rayPos;
    Vector p2 = rayPos + rayDir;

    for (size_t idx = 0u; idx < 4u; ++idx)
    {
        auto s1 = rectPoints[idx];
        auto s2 = rectPoints[(idx + 1) % 4];
        if (IsIntersectsSegmentWithRay(s1, s2, p1, p2))
            return true;
    }
    return false;
}

bool IsIntersects(const sf::FloatRect& rect, const RectPtr& pRect)
{
    auto rectPointsA = GetPoints(rect);
    auto rectPointsB = GetPoints(pRect);
    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
}

std::array<Vector, 4u> GetPoints(const RectPtr& pRect, const Vector& offset)
{
    std::array<Vector, 4u> points =
    {
        pRect->getPoint(0),
        pRect->getPoint(1),
        pRect->getPoint(2),
        pRect->getPoint(3),
    };
    for (auto& point : points)
    {
        point = point + offset;
    }
    return points;
}

std::array<Vector, 3u> GetTriangleShadowPoints(const Vector& lineupPos, const Vector& lineupDir, BlockPtr pBlock)
{
    if (!pBlock)
        return std::array<Vector, 3u>();

    Vector guide(-lineupDir.y, lineupDir.x);
    Vector secondPoint = lineupPos + guide;

    Vector leftPoint, rightPoint;

    CircleBlockPtr pCircleBlock = Cast<CircleBlock>(pBlock);
    RectBlockPtr pRectBlock = Cast<RectBlock>(pBlock);
    if (pCircleBlock)
    {
        auto translation = Normalize(guide) * pCircleBlock->GetRadius();
        rightPoint = pCircleBlock->GetPosition() + translation;
        leftPoint = pCircleBlock->GetPosition() - translation;
    }
    else if (pRectBlock)
    {
        auto leftRightPoint = GetLeftAndRightPoint(pRectBlock->GetBBox(), lineupPos, lineupDir);

        leftPoint = leftRightPoint.first;
        rightPoint = leftRightPoint.second;
    }
    else
        return std::array<Vector, 3u>();

    auto blockPos = pBlock->GetPosition();
    auto thirdPoint = blockPos + Normalize(-lineupDir) * (sqrt(pBlock->GetBBox().width * pBlock->GetBBox().width + pBlock->GetBBox().height * pBlock->GetBBox().height)) * 1.5f;

    return { leftPoint, rightPoint, thirdPoint };
}

std::pair<Vector, Vector> GetLeftAndRightPoint(const sf::FloatRect & rect, const Vector & dimPos, const Vector & dimDir)
{
    Vector guide(-dimDir.y, dimDir.x);
    auto rectPoints = GetPoints(rect);
    std::array<std::pair<Vector, Vector>, 4u> projPoints;
    for (size_t idx = 0; idx < rectPoints.size(); ++idx)
    {
        Vector projPoint;
        ProjectPointOnLine(dimPos, dimPos + guide, rectPoints[idx], projPoint);
        projPoints[idx] = std::make_pair(rectPoints[idx], projPoint);
    }
    auto base = dimPos + guide;
    auto getExtremePoints = [&projPoints](const Vector& base, bool isLeft)
    {
        std::vector<std::pair<Vector, Vector>> result;
        int sideSign = isLeft ? 1 : -1;
        for (const auto& p1 : projPoints)
        {
            bool isExtreme = true;
            for (const auto& p2 : projPoints)
            {
                if (p1 == p2)
                    continue;

                int resultSign = sign(DotProduct(p2.second - p1.second, base));
                if (resultSign == 0)
                    continue;
                if (resultSign != sideSign)
                {
                    isExtreme = false;
                    break;
                }
            }
            if (isExtreme)
                result.push_back(p1);
        }

        return result;
    };

    auto getClosestPoint = [&dimPos](std::vector<std::pair<Vector, Vector>> pointsPairs)
    {
        float minDist = 10000.f;
        Vector result;
        for (auto [p, dummy] : pointsPairs)
        {
            float dist = GetAbs(p - dimPos);
            if (minDist > dist)
            {
                minDist = dist;
                result = p;
            }
        }
        return result;
    };

    auto leftPoint = getClosestPoint(getExtremePoints(base, true));
    auto rightPoint = getClosestPoint(getExtremePoints(base, false));

    return { leftPoint, rightPoint };
}

std::array<Vector, 4u> GetPoints(const RectPtr& pRect)
{
    std::array<Vector, 4u> points =
    {
        pRect->getPoint(0),
        pRect->getPoint(1),
        pRect->getPoint(2),
        pRect->getPoint(3),
    };
    sf::Transform t = pRect->getTransform();

    for (auto& point : points)
    {
        point = t * point;
    }
    return points;
}

std::array<Vector, 4u> GetPoints(const sf::FloatRect& rect)
{
    return {
        Vector(rect.left, rect.top),
        Vector(rect.left, rect.top + rect.height),
        Vector(rect.left + rect.width, rect.top + rect.height),
        Vector(rect.left + rect.width, rect.top),
    };;
}

std::array<Vector, 3u> GetPoints(const TrianglePtr& pTriangle)
{
    std::array<Vector, 3u> points =
    {
        pTriangle->getPoint(0),
        pTriangle->getPoint(1),
        pTriangle->getPoint(2),
    };
    sf::Transform t = pTriangle->getTransform();

    for (auto& point : points)
    {
        point = t * point;
    }
    return points;
}
