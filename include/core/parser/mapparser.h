#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <vector>
#include <string>

struct LayerData;

class MapParser
{
	public:
	MapParser(){}
	virtual ~MapParser()=default;
	
	std::vector<LayerData> ExtractData(std::string address); 
	
};
#endif
