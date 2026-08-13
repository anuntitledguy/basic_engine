#ifndef LAYERDATA_H
#define LAYERDATA_H

#include "layer.h"

#include <vector>
#include <string>

struct LayerData
{
    // Layer
    std::string id;
    LAYER type;
    std::vector<int> tiles;

    int width;
    int height;

    // Tile
    int tileWidth;
    int tileHeight;

    // Tileset
    int tilesetColumns;
    int tilesetRows;

    std::string tilesetTexture;
};

#endif
