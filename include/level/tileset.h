#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include "raylib.h"

class TileSet
{
	public:
		TileSet(std::string id, Texture2D& tileset, int weight, int height, int nbrX, int nbrY);
		virtual ~TileSet();
		
		Texture2D& GetTileSet() const;
		Rectangle GetRectSource(int tileIndex) const ;	
		
		//Getter
		int GetWidth() const {return m_width;};
		int GetHeight() const {return m_height;};
		
		int GetNbrX() const {return m_nbrX;};
		int GetNbrY() const {return m_nbrY;};
		
		private:
			std::string m_id;
			Texture2D& m_tileset;	
			
			int m_width, m_height;
			int m_nbrX, m_nbrY;	
			
};
#endif
