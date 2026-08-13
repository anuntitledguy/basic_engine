#include "level/tilemap.h"

#include "level/layer.h"
#include "level/tilelayer.h"

#include "core/parser/mapparser.h"
#include "level/layerdata.h"

TileMap::TileMap(std::string id)
{
	m_id=id;
}

TileMap::~TileMap()
{
	
}

void TileMap::Draw()
{
    auto it = m_layer.find(LAYER::COLLISION);

    if(it != m_layer.end())
    {
        m_layer[LAYER::COLLISION]->Draw();
    }
    
    else
    {
        std::cout <<" layer DECOR doesn't exist\n";
    }
    
}
		
void TileMap::LoadLayer(std::string id, LAYER layer, std::vector<int> tiles, int layerNbrX, int layerNbrY, Texture2D& tileset, int tilesetWidth, int tilesetHeight, int tilesetNbrX, int tilesetNbrY)
{
    m_sizeX=layerNbrX*tilesetWidth;
    m_sizeY=layerNbrY*tilesetHeight;
	m_nbrX=layerNbrX;
	m_nbrY=layerNbrY;

    m_layer[layer] = std::make_unique<TileLayer>(id, tiles, layerNbrX, layerNbrY);
    auto it = m_layer.find(layer);

    if(it != m_layer.end())
    {
        m_layer[layer]->AddTileSet(id, tileset, tilesetWidth, tilesetHeight, tilesetNbrX, tilesetNbrY);
	std::cout << id <<" layer loaded\n";
    }
    
    else
    {
        std::cout << id <<" layer not loaded\n";
    }
}


void TileMap::LoadMap(std::string id, std::string address, Texture2D& tileset)
{
    MapParser parser;

    std::vector<LayerData> layers =
        parser.ExtractData(address);

    for (const auto& layer : layers)
    {
        m_sizeX = layer.width * layer.tileWidth;
        m_sizeY = layer.height * layer.tileHeight;

        m_nbrX = layer.width;
        m_nbrY = layer.height;

        auto tileLayer = std::make_unique<TileLayer>(
            id,
            layer.tiles,
            layer.width,
            layer.height
        );

        tileLayer->AddTileSet(
            id,
            tileset,
            layer.tileWidth,
            layer.tileHeight,
            layer.tilesetColumns,
            layer.tilesetRows
        );

        m_layer[layer.type] = std::move(tileLayer);

        std::cout << id << " layer loaded\n";
    }
}

void TileMap::Unload()
{
    for(auto& layer : m_layer)
    {
        m_layer.erase(layer.first);
    }

    std::cout << "sceneManager destroy\n";
}

TileLayer& TileMap::GetTileLayer(const LAYER layer) 
{
    auto it = m_layer.find(layer);

    if(it != m_layer.end())
    {
        return (*m_layer[layer]);
    }
    
    else
    {
        std::cout <<" layer doesn't exist\n";
    }
}

int TileMap::GetSizeX() const
{
    return m_sizeX;
}

int TileMap::GetSizeY() const
{
    return m_sizeY;
}
