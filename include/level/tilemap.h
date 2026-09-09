#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

class TileLayer;
enum class LAYER;

class TileMap
{
	public:
		TileMap(std::string id);
		virtual ~TileMap();
		
		void Draw();
		//void Update();
		
		void LoadLayer(std::string id, Texture2D& tileset, LAYER layer, std::vector<int> tiles, int layerNbrX, int layerNbrY, int tileWidth, int tileHeight, int tilesetNbrX, int tilesetNbrY, int firstGid);
		void LoadMap(std::string id, std::string address);
		void Unload();
		
		TileLayer& GetTileLayer(const LAYER layer);
		
		int GetSizeX() const;
		int GetSizeY() const;
		
	private:
		std::string m_id;
		std::map<LAYER,std::unique_ptr<TileLayer>> m_layer;
		int m_sizeX, m_sizeY;
		int m_nbrX, m_nbrY;
	
};
#endif
