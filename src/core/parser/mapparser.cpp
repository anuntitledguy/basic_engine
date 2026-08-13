#include "core/parser/mapparser.h"

#include "level/layerdata.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include <iostream>


using json = nlohmann::json;

std::vector<LayerData> MapParser::ExtractData(std::string address)
{
    json data;

    std::ifstream fichier(address);

    if (!fichier.is_open())
    {
        std::cout << "File: " << address << " not found\n";
        return {};
    }

    fichier >> data;

    std::vector<LayerData> setData;

    for (size_t i = 0; i < data["layers"].size(); ++i)
    {
        LayerData layer;

        layer.width = data["layers"][i]["width"];
        layer.height = data["layers"][i]["height"];

        layer.tiles =
            data["layers"][i]["data"].get<std::vector<int>>();

        layer.tileWidth = data["tilewidth"];
        layer.tileHeight = data["tileheight"];

        if (data["layers"][i]["name"] == "COLLISION")
        {
            layer.type = LAYER::COLLISION;

            layer.tilesetColumns = 2;
            layer.tilesetRows = 1;

            layer.tilesetTexture = "NA";
        }
        else if (data["layers"][i]["name"] == "DECOR")
        {
            layer.type = LAYER::DECOR;

            for (size_t j = 0; j < data["tilesets"].size(); ++j)
            {
                if (data["tilesets"][j]["class"] == "DECOR")
                {
                    layer.tilesetColumns =
                        data["tilesets"][j]["columns"];

                    layer.tilesetRows =
                        int(data["tilesets"][j]["tilecount"]) /
                        int(data["tilesets"][j]["columns"]);

                    layer.tilesetTexture =
                        data["tilesets"][j]["image"];
                }
            }
        }

        setData.emplace_back(std::move(layer));
    }

    return setData;
}


