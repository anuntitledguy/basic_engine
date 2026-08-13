#include "level/tileset.h"

#include "raylib.h"

TileSet::TileSet(std::string id, Texture2D& tileset, int width, int height, int nbrX, int nbrY):
m_tileset(tileset)
{
	std::string m_id=id;
	m_width=width;
	m_height=height;	
	m_nbrX=nbrX;
	m_nbrY=nbrY;
}

TileSet::~TileSet()
{
	
}
		
Texture2D& TileSet::GetTileSet() const 
{
	return m_tileset;
}

Rectangle TileSet::GetRectSource(int tileIndex) const
{
	Rectangle rec={(float)((tileIndex%m_nbrX)*m_width), (float)((tileIndex/m_nbrX)*m_height), (float)m_width, (float)m_height};
	return(rec);
}
