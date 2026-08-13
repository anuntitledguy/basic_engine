#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include <iostream>

#include "itexture.h"

class Sprite : public Itexture
{
	public:
		Sprite(const std::string& id, Texture2D& texture);
		virtual ~Sprite();
		
		virtual void Draw(const int x, const int y, Color tint=BLANK);
		virtual void Draw(Vector2 pos, Color tint=BLANK);
	
	private:
		std::string m_id;
		Texture2D* m_sprite;
};

#endif
