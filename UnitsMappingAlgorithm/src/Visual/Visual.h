//#pragma once
//#include "../Common.h"
//#include <memory>
//
//#include <iostream>
//using TexturePtr = std::shared_ptr<SDL_Texture>;
//class VisualObject;
//class Rect;
//class RectTexture;
//using VisualObjectPtr = std::shared_ptr<VisualObject>;
//using RectPtr = std::shared_ptr<Rect>;
//using RectTexturePtr = std::shared_ptr<RectTexture>;
//TexturePtr CreateTexture(SDL_Renderer* pRenderer, Uint32 format, int access, int w, int h);
//
//int SetRenderDrawColor(SDL_Renderer* pRenderer, Colors::Color color);
//template<class T>
//SDL_Point ToSDL_Point(Vector2<T> vector);
//
//class RectTexture
//{
//public:
//	RectTexture(SDL_Renderer* pRenderer, const Vector2f& size, const Colors::Color& color);
//	float GetHeight() const;
//	float GetWidth() const;
//	Vector2f GetSize() const;
//	SDL_Texture* GetTextureRawPtr() const;
//	~RectTexture()
//	{
//		std::cout << "Destroyed" << std::endl;
//		if(m_pTexture)
//			SDL_DestroyTexture(m_pTexture.get());
//	}
//
//private:
//	TexturePtr m_pTexture;
//	SDL_FRect m_fRect;
//};
//
//class VisualObject
//{
//public:
//	virtual void Draw() = 0;
//};
//
//class Rect : public VisualObject
//{
//public:
//	Rect(SDL_Renderer* pRenderer, const Vector2f& position, const Vector2f& size, const Colors::Color& color);
//	void Draw() override;
//	RectPtr Clone() const;
//
//	float GetRotation() const
//	{
//		return m_rotationAngle;
//	}
//	Vector2f GetSize() const
//	{
//		return m_rectTexture->GetSize();
//	}
//	Vector2f GetPosition() const
//	{
//		return m_position;
//	}
//	BBox GetBBox() const
//	{
//		return BBox();
//	}
//
//	void SetPosition(const Vector2f& position)
//	{
//		m_position = position;
//	}
//	void SetRotation(const float& degrees)
//	{
//		m_rotationAngle = degrees;
//	}
//	void Rotate(const float& degrees)
//	{
//		m_rotationAngle += degrees;
//	}
//
//private:
//	Vector2f m_position;
//	SDL_Point m_rotationPoint;
//	double m_rotationAngle = 0.l;
//	RectTexturePtr m_rectTexture;
//	SDL_Renderer* m_pRenderer;
//};
//
//RectPtr CreateRect(SDL_Renderer* pRenderer, const Vector2f & position, const Vector2f & size, const Colors::Color& color);
//
//template<class T>
//inline SDL_Point ToSDL_Point(Vector2<T> vector)
//{
//	SDL_Point p;
//	p.x = vector.x;
//	p.y = vector.y;
//	return p;
//}
//
//struct UnitDrawable : public VisualObject
//{
//	RectPtr body;
//	RectPtr gun;
//
//	void SetPosition(const Vector2f& position)
//	{
//		body->SetPosition(position);
//
//		auto bodySize = body->GetSize();
//		gun->SetPosition(position + Vector2f(bodySize.x / 2.f - bodySize.x / 16.f, bodySize.y / 2.f - bodySize.x / 16.f));
//	}
//	void SetRotation(const float& angle)
//	{
//		body->SetRotation(angle);
//	}
//	void SetGunRotation(const float& angle)
//	{
//		gun->SetRotation(angle);
//	}
//	void RotateGun(const float& angle)
//	{
//		gun->Rotate(angle);
//
//	}
//	void SetGunDirection(const Vector2f& dir)
//	{
//		m_gunDirection = dir;
//	}
//	Vector2f GetGunDirection() const
//	{
//		return m_gunDirection;
//	}
//	float GetRotation() const
//	{
//		return body->GetRotation();
//	}
//	float GetGunRotation() const
//	{
//		return gun->GetRotation();
//	}
//
//	static bool IsUnitDrawable(const VisualObjectPtr& o)
//	{
//		return dynamic_cast<UnitDrawable*>(o.get());
//	}
//
//private:
//	void Draw() override
//	{
//		if (body)
//			body->Draw();
//		if (gun)
//			gun->Draw();
//	}
//
//	Vector2f m_gunDirection = Vector2f(0.f, 1.f);
//};
//
//using UnitDrawablePtr = std::shared_ptr<UnitDrawable>;
//
//inline UnitDrawablePtr CreateUnitDrawable(const RectPtr& pBody, const RectPtr& pGun)
//{
//	UnitDrawablePtr pUnit = std::make_shared<UnitDrawable>();
//	pUnit->body = pBody;
//	pUnit->gun = pGun;
//	return pUnit;
//}