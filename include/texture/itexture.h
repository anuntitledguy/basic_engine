#ifndef ITEXTURE_H
#define ITEXTURE_H

#include "raylib.h"

class Itexture
{
	public:
		virtual ~Itexture()=default;
		
		virtual void Draw(const int x, const int y, Color tint=BLANK)=0;
		virtual void Draw(Vector2 pos, Color tint=BLANK)=0;
		
};
#endif
