#include "Map.h"
#include "../../Manager/Tiles.h"
#include <fstream>
#include <sstream>

Map::Map(const std::string& levelMapPath, char delimChar) {
    config = Config::getInstance();
    loadNewMapFromPath(levelMapPath,delimChar);
}

Map::Map(const Map &mapObj):
    config(mapObj.config){
    for (int y = 0; y < mapObj.map.size(); ++y) {
        map.emplace_back(std::vector<Tile*>());
        for (int x = 0; x < mapObj.map[y].size(); ++x) {
            map[y].emplace_back(new Tile(*mapObj.map[y][x]));
        }
    }

}

Map::~Map() {
    if(!map.empty()){
        for(const auto& row : map)
            for(Tile* column : row)
                delete column;
    }
    std::vector<std::vector<Tile*>>().swap(map);
}

void Map::loadNewMapFromPath(const std::string& levelMapPath, char delimChar) {
    if(!map.empty()){
        for(auto &y : map)
            for(auto & x : y)
                delete x;
    }
    map.resize(config->getValue("sizeYInTiles"), std::vector<Tile*>(config->getValue("sizeXInTiles"), nullptr));
    for(auto &y : map)
        for(auto &x : y)
            x = new Tile();
    std::ifstream fileIn(levelMapPath.c_str());
    if(fileIn.is_open()) {
        int y = 0, x = 0;
        std::string line;
        while(getline(fileIn,line, '\n')){
            if(y >= config->getValue("sizeYInTiles")) break;
            //map.emplace_back(std::vector<int>());
            std::istringstream tokenStream(line);
            std::string charNumber;
            while(getline(tokenStream, charNumber, delimChar)) {
                if(x >= config->getValue("sizeXInTiles")) break;
                //map[y].push_back(std::stoi(charNumber));
                int tokenMap = std::stoi(charNumber);
                Tiles::switchTile(*(map[y][x]), tokenMap);
                x++;
            }
            x = 0;
            y++;
        }
    }
    fileIn.close();
}

void Map::update(unsigned int startIdX, unsigned int startIdY, unsigned int stopIdX, unsigned int stopIdY) {
    for(unsigned int y = startIdY; y < stopIdY && y < map.size(); y++)
        for(unsigned int x = startIdX; x < stopIdX && x < map[y].size(); x++)
            map[y][x]->update();
}
