#include <iostream>
#include "Textures.h"
#include "../Utility/Config.h"

Textures* Textures::selfInstance = nullptr;

Textures::Textures() {
    std::string path = "assets/textures/";
    int srcWidth = 32;
    int srcHeight = 32;
    int dstWidth = Config::getInstance()->getValue("sizeTile");
    int dstHeight = Config::getInstance()->getValue("sizeTile");
    //default
    default_default = new Texture(path + "default.png", srcWidth, srcHeight, dstWidth, dstHeight);
    //entity
    entity_player = new Texture(path + "entity/player_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    entity_spider_0 = new Texture(path + "entity/spider_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    entity_mag_0 = new Texture(path + "entity/mag_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    entity_cactuser_0 = new Texture(path + "entity/cactuser_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    entity_bat_0 = new Texture(path + "entity/bat_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    //map
    map_grass_0 = new Texture(path + "map/grass_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_grass_1 = new Texture(path + "map/grass_1.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_grass_2 = new Texture(path + "map/grass_2.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_grass_3 = new Texture(path + "map/grass_3.png", srcWidth, srcHeight, dstWidth, dstHeight);

    map_dirt = new Texture("assets/textures/map/dirt.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_water_0 = new Texture("assets/textures/map/water_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_water_1 = new Texture("assets/textures/map/water_1.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_water_2 = new Texture("assets/textures/map/water_2.png", srcWidth, srcHeight, dstWidth, dstHeight);

    map_tree_0 = new Texture("assets/textures/map/tree_0.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_bush = new Texture("assets/textures/map/bush.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_bush_red = new Texture("assets/textures/map/bush_red.png", srcWidth, srcHeight, dstWidth, dstHeight);

    map_flower_0 = new Texture("assets/textures/map/flower_0.png", srcWidth, srcHeight, dstWidth, dstHeight);

    map_gold = new Texture("assets/textures/map/gold.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_stone = new Texture("assets/textures/map/stone.png", srcWidth, srcHeight, dstWidth, dstHeight);
    map_windmill = new Texture("assets/textures/map/windmill.png", srcWidth, srcHeight, dstWidth, dstHeight);

}

Textures::~Textures() {
    //default
    delete default_default;
    //entity
    delete entity_player;
    delete entity_spider_0;
    delete entity_cactuser_0;
    delete entity_bat_0;
    //map
    delete map_grass_0;
    delete map_grass_1;
    delete map_grass_2;
    delete map_grass_3;

    delete map_dirt;
    delete map_water_0;
    delete map_water_1;
    delete map_water_2;

    delete map_tree_0;
    delete map_bush;
    delete map_bush_red;

    delete map_gold;
    delete map_stone;
    delete map_windmill;
}

void Textures::initTextures() {
    if(selfInstance == nullptr) selfInstance = new Textures();
}

Textures *Textures::getTextures() {
    if(selfInstance == nullptr){
        std::cerr<<"ERROR: Textures has not been initiated..."<<std::endl;
        exit(2);
    }
    return selfInstance;
}

void Textures::destroyTextures() {
    delete selfInstance;
    selfInstance = nullptr;
}
