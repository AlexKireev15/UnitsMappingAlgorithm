#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace PlaceAlgorithm {
	class Placer;

	struct Vector2f
	{
		float x;
		float y;
	};

	class Object
	{
		friend class Placer;
	public:
		Object(float x, float y, float boundaryX, float boundaryY) :
			m_pos({ x, y }), m_boundary({ boundaryX, boundaryY }) { }
	private:
		Vector2f m_pos;
		Vector2f m_boundary;
	};

	class Placer
	{
	public:
		Placer() { }
		Placer(std::vector<Object> objects) :
			m_objects(objects) { }

		std::vector<Vector2f> LineUp(size_t count, Vector2f boundary, Vector2f padding) const;

		std::vector<sf::RectangleShape> Place(const std::string& lineUpName, size_t count, Vector2f position, float angle, Vector2f boundary, Vector2f padding);
	private:
		std::vector<Object> m_objects;
	};
};