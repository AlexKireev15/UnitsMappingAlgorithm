//#include "../Visual.h"
//
//#include <iostream>
//TexturePtr CreateTexture(SDL_Renderer* pRenderer, Uint32 format, int access, int w, int h)
//{
//	return TexturePtr(SDL_CreateTexture(pRenderer, format, access, w, h));
//}
//int SetRenderDrawColor(SDL_Renderer* pRenderer, Colors::Color color)
//{
//	return SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
//}
//
//RectTexture::RectTexture(SDL_Renderer* pRenderer, const Vector2f & size, const Colors::Color & color)
//{
//	m_pTexture = CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y);
//	SDL_SetRenderTarget(pRenderer, m_pTexture.get());
//	SetRenderDrawColor(pRenderer, color);
//
//	m_fRect.x = 0.f;
//	m_fRect.y = 0.f;
//	m_fRect.w = size.x;
//	m_fRect.h = size.y;
//	SDL_RenderDrawRectF(pRenderer, &m_fRect);
//	SDL_RenderFillRectF(pRenderer, &m_fRect);
//
//	SetRenderDrawColor(pRenderer, Colors::Default);
//	SDL_SetRenderTarget(pRenderer, NULL);
//
//}
//
//float RectTexture::GetHeight() const
//{
//	return m_fRect.h;
//}
//
//float RectTexture::GetWidth() const
//{
//	return m_fRect.w;
//}
//
//Vector2f RectTexture::GetSize() const
//{
//	return {m_fRect.w, m_fRect.h};
//}
//
//SDL_Texture* RectTexture::GetTextureRawPtr() const
//{
//	return m_pTexture.get();
//}
//
//Rect::Rect(SDL_Renderer* pRenderer, const Vector2f & position, const Vector2f & size, const Colors::Color& color) :
//	m_pRenderer(pRenderer),
//	m_position(position), m_rotationPoint(ToSDL_Point(position + size / 2.f)),
//	m_rotationAngle(0.l)
//{
//	m_rectTexture = std::make_shared<RectTexture>(pRenderer, size, color);
//}
//
//void Rect::Draw()
//{
//	SDL_Rect dst;
//	dst.x = m_position.x;
//	dst.y = m_position.y;
//	dst.w = m_rectTexture->GetWidth();
//	dst.h = m_rectTexture->GetHeight();
//	SDL_RenderCopyEx(m_pRenderer, m_rectTexture->GetTextureRawPtr(), NULL, &dst, m_rotationAngle, &m_rotationPoint, SDL_FLIP_NONE);
//}
//
//RectPtr Rect::Clone() const
//{
//	return RectPtr(new Rect(*this));
//}
//
//RectPtr CreateRect(SDL_Renderer* pRenderer, const Vector2f & position, const Vector2f & size, const Colors::Color& color)
//{
//	RectPtr rect = std::make_shared<Rect>(pRenderer, position, size, color);
//	return rect;
//}
