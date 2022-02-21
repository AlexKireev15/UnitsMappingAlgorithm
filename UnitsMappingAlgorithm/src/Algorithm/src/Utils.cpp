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

bool IsPointInsideRect(std::array<sf::Vector2f, 4u> rectPoints, const sf::Vector2f& point)
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

bool IsPointInsideCircle(const sf::Vector2f& p, const CirclePtr& pCircle)
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

bool ProjectPointOnLine(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& point, sf::Vector2f& result)
{
    sf::Vector2f a = p2 - p1;
    sf::Vector2f b = point - p1;
    result = a * DotProduct(a, b);
    int s = sign(DotProduct(a, result - a));
    if (s > 0)
        return false;
    return true;
}

bool IsIntersects(const sf::Vector2f& p1, const sf::Vector2f& p2, const CirclePtr& pCircle)
{
    if (IsPointInsideCircle(p1, pCircle) || IsPointInsideCircle(p2, pCircle))
        return true;

    sf::Vector2f projPoint;
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

bool TryIntersect(const std::array<sf::Vector2f, 4u>& rectPointsA, const std::array<sf::Vector2f, 4u>& rectPointsB)
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

bool IsIntersects(const std::array<sf::Vector2f, 4u>& rectPointsA, const std::array<sf::Vector2f, 4u>& rectPointsB)
{
    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
}

bool IsIntersects(const sf::FloatRect& rect, const RectPtr& pRect)
{
    auto rectPointsA = GetPoints(rect);
    auto rectPointsB = GetPoints(pRect);
    return TryIntersect(rectPointsA, rectPointsB) && TryIntersect(rectPointsB, rectPointsA);
}

std::array<sf::Vector2f, 4u> GetPoints(const RectPtr& pRect, const sf::Vector2f& offset)
{
    std::array<sf::Vector2f, 4u> points =
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

std::array<sf::Vector2f, 4u> GetPoints(const RectPtr& pRect)
{
    std::array<sf::Vector2f, 4u> points =
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

std::array<sf::Vector2f, 4u> GetPoints(const sf::FloatRect& rect)
{
    return {
        sf::Vector2f(rect.left, rect.top),
        sf::Vector2f(rect.left, rect.top + rect.height),
        sf::Vector2f(rect.left + rect.width, rect.top + rect.height),
        sf::Vector2f(rect.left + rect.width, rect.top),
    };;
}
