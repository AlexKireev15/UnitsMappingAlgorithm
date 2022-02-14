#pragma once
#include "../Common.h"
#include "Blocks.h"
#include "PlaceAlgorithm.h"

namespace PlaceAlgorithm
{
	using namespace sf;

	class Unit : public Block
	{
	public:
		Unit(RectPtr pRect, const Vector2f& padding, const Vector2f& lineupPosition, const Placer& placer) :
			Block(ElementType::UNIT), m_pRect(pRect), m_padding(padding), m_lineupPosition(lineupPosition), m_placer(placer) { }

		bool SetPosition(const Vector2f& position);
		void Move(const Vector2f& offset);
		void Rotate(float angle, const Vector2f& center);
		void RotateNoSelfAxis(float angle, const Vector2f& center);
		void UpdateLineupPosition(const Vector2f& groupPosition);

		Vector2f GetPosition() const;
		float GetRadius() const;
		float GetRotation() const;
		RectPtr GetDrawable() const;
		Vector2f GetBBox() const;
		Vector2f GetLineupPosition() const;

		bool IsIntersectedWithRect(const sf::Vector2f& position, const sf::Vector2f& size, float rotationAngle, sf::Vector2f& correctionVector) override;
		bool IsIntersectedWith(const sf::Vector2f& position, float radius) override;

	private:
		RectPtr m_pRect;
		Vector2f m_padding;
		Vector2f m_lineupPosition;
		const Placer& m_placer;
	};

	class UnitGroup
	{
	public:
		UnitGroup(const Vector2f& position, std::list<UnitPtr> units) : m_position(position), m_units(units) { }
		void SetPosition(const Vector2f& position)
		{
			for (UnitPtr pUnit : m_units)
			{
				if (!pUnit)
					continue;
				if(pUnit->SetPosition(position + pUnit->GetLineupPosition()))
					pUnit->RotateNoSelfAxis(m_rotation, position);
			}
			m_position = position;
		}
		Vector2f GetPosition() const
		{
			return m_position;
		}

		void Rotate(float angle)
		{
			for (UnitPtr pUnit : m_units)
			{
				if (!pUnit)
					continue;
				pUnit->Rotate(angle, m_position);
			}
			m_rotation += angle;
		}
		std::list<DrawablePtr> GetDrawables() const
		{
			std::list<DrawablePtr> drawables;
			for (auto pUnit : m_units)
			{
				if (!pUnit)
					continue;
				auto pDrawable = pUnit->GetDrawable();
				if (pDrawable)
					drawables.push_back(pDrawable);
			}
			return drawables;
		}
		std::list<UnitPtr>& GetUnits()
		{
			return m_units;
		}

	private:
		std::list<UnitPtr> m_units;
		Vector2f m_position;
		float m_rotation;
	};

	inline UnitPtr CreateUnit(RectPtr pRect, const Vector2f& padding, const Vector2f& lineupPosition, const Placer& placer) { return std::make_shared<Unit>(pRect, padding, lineupPosition, placer); }

};