#include "Tile.h"

unsigned int Tile::lastTileID = 0;

Tile::Tile() :
    tileID(++lastTileID){
    texLayers.resize(0);
    relativeMode = false;
    collision = false;
    entity = false;
    active = true;
}

Tile::Tile(const Tile& tileObj):
    tileID(++lastTileID),
    texLayers(tileObj.texLayers),
    collision(tileObj.collision)
{}

Tile::~Tile() {
    //for(auto &tex : texLayers)
        //delete tex;
    std::vector<Texture*>().swap(texLayers);
}

void Tile::addTexLayer(Texture *newTexture) {
    texLayers.emplace_back(new Texture(*newTexture));
}

void Tile::update() {
    size = { texLayers.back()->dstRectTex.w, texLayers.back()->dstRectTex.h };
};

void Tile::render() {
    if(active)
    for(auto &texLayer : texLayers)
        if(texLayer != nullptr) {
            if (relativeMode)
                texLayer->drawTexture(relativePos.x, relativePos.y);
            else
                texLayer->drawTexture(absolutePos.x, absolutePos.y);
        }
}
