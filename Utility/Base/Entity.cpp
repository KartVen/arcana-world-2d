#include "Entity.h"
#include "../../Manager/Tiles.h"

Entity::Entity(const std::string& name, int posX, int posY, Texture* texture) :
    Tile(),
    ENT_VELOCITY(Config::getInstance()->getValue("entityVelocity")) {
    config = Config::getInstance();
    absolutePos = {
            posX / config->getValue("sizeTile") * config->getValue("sizeTile"),
            posY / config->getValue("sizeTile") * config->getValue("sizeTile")
    };
    constructPos = absolutePos;
    this->name = name;
    lvl = lvlBackBuffer = 1;
    xp = 0;
    Uint8 r = config->getValue("colorRHeadText");
    Uint8 g = (Uint8) config->getValue("colorGHeadText");
    Uint8 b = (Uint8) config->getValue("colorBHeadText");
    Uint8 a = (Uint8) config->getValue("colorAHeadText");
    startHpMax = hpMaxBooster = hpMax = hp = hpBackBuffer = 0;
    startAttackPassive = attackPassive = 0;
    startDefense = defense = 0;
    startAttackCriticalPercent = attackCriticalPercent = 0;
    headText = new Text(name + " -- <---->", config->getValue("sizeHeadText"), absolutePos.x, absolutePos.y - 10, {r, g, b, a}, "anton.ttf");
    width = config->getValue("sizeTile");
    height = config->getValue("sizeTile");
    collision = true;
    entity = true;
    rotate = 0;
    animNexter = 0;
    active = true;
    if (texture != nullptr)
        texLayers.emplace_back(new Texture(*texture));
    else
        texLayers.emplace_back(new Texture(*Textures::getTextures()->default_default));
    if (!texLayers.empty())
        texLayers.back()->dstRectTex = {posX, posY, width, height};
    eyeRange = movementRange = config->getValue("entityRange");
    entShiftX = 0;
    entShiftY = 0;
    frameEvents = 0;
    ai = true;
}

Entity::~Entity() {
    delete headText;
    headText = nullptr;
}

void Entity::update() {
    Tile::update();
    frameEvents++;
    if(frameEvents > config->getValue("frameEntityExecuter"))
        frameEvents = 1;
    for (Texture*& tex : texLayers) {
        tex->dstRectTex.x = absolutePos.x;
        tex->dstRectTex.y = absolutePos.y;
    }
    for (int tmpLvl = 0; tmpLvl < config->lvlXpTable.size() && xp >= config->lvlXpTable[tmpLvl]; tmpLvl++)
        if (lvl < tmpLvl) lvl = tmpLvl;
    if(lvlBackBuffer != lvl){
        int oldHpMax = hpMax;
        //if (lvl != 1) hpMax += 50;
        for(int i = lvlBackBuffer; i < lvl; ++i) hpMax += hpMaxBooster;
        hp += hpMax - oldHpMax;
        if (hp > hpMax) hp = hpMax;
        lvlBackBuffer = lvl;
        attackPassive = startAttackPassive + 0.50 * lvl;
        defense = startDefense + 0.5 * lvl;
        attackCriticalPercent = startAttackCriticalPercent + 0.25 * lvl;
    }
    if (hpBackBuffer != hp) {
        std::string hpText = ((hp < 1000) ? ((hp < 100) ? ((hp < 10) ? ((hp == 0) ? "0000" : "000") : "00") : "0") : "");
        headText->content = name + " " + ((lvl < 10) ? "0" : "") + std::to_string(lvl) + " <" + hpText + std::to_string(hp) + ">";
        headText->update();
        hpBackBuffer = hp;
    }
    if (ai) {
        if (frameEvents % config->getValue("frameEntityExecuter") == 0) {
            entShiftX = entShiftY = 0;
            switch ((int)rand() % 4)
            {
                case 0: {
                    entShiftY = ENT_VELOCITY;
                    break;
                }
                case 1: {
                    entShiftX = -ENT_VELOCITY;
                    break;
                }
                case 2: {
                    entShiftY = -ENT_VELOCITY;
                    break;
                }
                case 3: {
                    entShiftX = ENT_VELOCITY;
                    break;
                }
            }
        }
        int shiftX = entShiftX;
        int shiftY = entShiftY;
        while(shiftY < 0 && (Tiles::checkCollision(absolutePos.x, absolutePos.y + shiftY) || Tiles::checkCollision(absolutePos.x + width - 1, absolutePos.y + shiftY))) ++shiftY;
        while (shiftY > 0 && (Tiles::checkCollision(absolutePos.x, absolutePos.y + shiftY + height) || Tiles::checkCollision(absolutePos.x + width - 1, absolutePos.y + shiftY + height))) --shiftY;
        while (shiftX < 0 && (Tiles::checkCollision(absolutePos.x + shiftX, absolutePos.y) || Tiles::checkCollision(absolutePos.x + shiftX, absolutePos.y + height - 1))) ++shiftX;
        while (shiftX > 0 && (Tiles::checkCollision(absolutePos.x + shiftX + width, absolutePos.y) || Tiles::checkCollision(absolutePos.x + shiftX + width, absolutePos.y + height - 1))) --shiftX;
        if (shiftY < 0 && constructPos.y - movementRange < absolutePos.y || shiftY > 0 && absolutePos.y < constructPos.y + movementRange); else shiftY = 0;
        if (shiftX < 0 && constructPos.x - movementRange < absolutePos.x || shiftX > 0 && absolutePos.x < constructPos.x + movementRange); else shiftX = 0;
        absolutePos += {shiftX, shiftY};
    }
}

void Entity::render() {
    Tile::render();
    if (relativeMode){
        headText->textRect.x = relativePos.x + (config->getValue("sizeTile") - headText->textRect.w) / 2;
        headText->textRect.y = relativePos.y - headText->textRect.h;
    }
    else{
        headText->textRect.x = absolutePos.x + (config->getValue("sizeTile") - headText->textRect.w) / 2;
        headText->textRect.y = absolutePos.y - headText->textRect.h;
    }
    headText->render();
}
