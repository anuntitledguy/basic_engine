#ifndef TILELAYER_H
#define TILELAYER_H

#include "raylib.h"

#include <iostream>
#include <vector>
#include <memory>

class TileSet;

class TileLayer
{
	public:
		TileLayer(std::string id, std::vector<int> tiles, int nbrX, int nbrY);
		virtual ~TileLayer();
		
		void Draw();
		
		void AddTileSet(std::string id, Texture2D& tileset, int tilewidth, int tileheight, int nbrX, int nbrY);
		
		int GetTileID(const Vector2 pos) const;
		Rectangle GetTileRect(const Vector2 pos) const;
	
	private:
		std::string m_id;
		
		std::vector<int> m_tiles;
		std::unique_ptr<TileSet> m_tileset;
		
		int m_nbrY, m_nbrX;

};
#endif
