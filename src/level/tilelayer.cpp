#include "level/tilelayer.h"

#include "level/tileset.h"

TileLayer::TileLayer(std::string id, std::vector<int> tiles, int nbrX, int nbrY)
{
	m_id= id;
	m_tiles=tiles;
	m_nbrX=nbrX;
	m_nbrY=nbrY;
}

TileLayer::~TileLayer()
{
	
}
		
void TileLayer::Draw()
{
	Texture2D& texture=m_tileset->GetTileSet();
	for(size_t index = 0; index < m_tiles.size(); ++index)
	{
		Rectangle rec= m_tileset->GetRectSource(m_tiles[index]);
			
		Vector2 pos={(float)((index%this->m_nbrX)*m_tileset->GetWidth()),(float)((index/this->m_nbrX)*m_tileset->GetHeight())};
			
		DrawTextureRec(texture, rec, pos, WHITE);
	}
}
		
void TileLayer::AddTileSet(std::string id, Texture2D& tileset, int tilewidth, int tileheight, int nbrX, int nbrY)
{
	m_tileset=std::make_unique<TileSet>(id, tileset, tilewidth, tileheight, nbrX, nbrY);
}


int TileLayer::GetTileID(const Vector2 pos) const
{
	return (m_tiles[(int(pos.y)/m_tileset->GetHeight())*m_nbrX+(int(pos.x)/m_tileset->GetWidth())]);
}


Rectangle TileLayer::GetTileRect(const Vector2 pos) const
{
	return ((Rectangle){int(pos.x/m_tileset->GetWidth())*m_tileset->GetWidth(), int(pos.y/m_tileset->GetHeight())*m_tileset->GetHeight(), m_tileset->GetWidth(),m_tileset->GetHeight()});
}
