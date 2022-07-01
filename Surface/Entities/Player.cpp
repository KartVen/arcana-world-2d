#include "Player.h"

Player* Player::selfInstance = nullptr;

Player::Player(const char *name, int posX, int posY, Texture *texture):
    Entity(name, posX, posY, (texture != nullptr)? texture:Textures::getTextures()->entity_player),
    VELOCITY(Config::getInstance()->getValue("velocity")){
    ai = false;
    collision = true;
    events = Events::getEvents();
    tilesManager = nullptr;
    shiftPosX = shiftPosY = 0;
    xpBackBuffer = xp = 0;
    startHpMax = hpMax = hp = 1000;
    hpMaxBooster = 50;
    startAttackPassive = attackPassive = 20;
    startDefense = defense = 10;
    startAttackCriticalPercent = attackCriticalPercent = 15;
    headText->color = {125, 50, 50, headText->color.a};
}

void Player::initPlayer(const char *name, int posX, int posY, Texture *texture) {
    if(selfInstance == nullptr) selfInstance = new Player(name, posX, posY, texture);
}

Player *Player::getInstance() {
    if(selfInstance == nullptr) {
        std::cerr<<"ERROR: Player has not been initiated..."<<std::endl;
        exit(2);
    }
    return selfInstance;
}

void Player::destroyPlayer() {
    if(selfInstance != nullptr) delete selfInstance;
    selfInstance = nullptr;
}

bool Player::handleEvent() {
    if(events->key.w.isClicked || events->key.UP.isClicked) {
        if(!events->key.a.isClicked && !events->key.d.isClicked && !events->key.LEFT.isClicked && !events->key.RIGHT.isClicked) {
            rotate = ROTATE::UP;
            animNexter = 1 - animNexter;
        }
            shiftPosY -= VELOCITY;
    }
    else if(events->key.s.isClicked || events->key.DOWN.isClicked) {
        if(!events->key.a.isClicked && !events->key.d.isClicked && !events->key.LEFT.isClicked && !events->key.RIGHT.isClicked) {
            rotate = ROTATE::DOWN;
            animNexter = 1 - animNexter;
        }
        shiftPosY += VELOCITY;
    }
    if(events->key.a.isClicked || events->key.LEFT.isClicked) {
        rotate = ROTATE::LEFT;
        animNexter = 1 - animNexter;
        shiftPosX -= VELOCITY;
    }
    else if(events->key.d.isClicked || events->key.RIGHT.isClicked) {
        rotate = ROTATE::RIGHT;
        animNexter = 1 - animNexter;
        shiftPosX += VELOCITY;
    }
    if(events->key.SPACE.isClicked){
        return tilesManager->attackEntity({ absolutePos.x, absolutePos.y, size.w, size.h }, rotate, &hp, hpMax, &xp, attackPassive, defense, attackCriticalPercent);
    }
    return true;
}

void Player::update() {
    if(tilesManager == nullptr) {
        std::cerr<<"Error: The Player does not have a TilesManager assigned..."<<std::endl;
        exit(2);
    }
    int sizeTile = config->getValue("sizeTile");
    int damageExecutor = (int) (config->getValue("frameEntityExecuter") / 1.25);
    if(shiftPosY != 0){
        if(absolutePos.y + shiftPosY < 0){
            absolutePos.y = 0;
        }
        else if(absolutePos.y + shiftPosY > sizeTile * config->getValue("sizeYInTiles") - height){
            absolutePos.y = sizeTile * config->getValue("sizeYInTiles") - height;
        }
        else{
            if(shiftPosY < 0){
                if(tilesManager->checkCollision(absolutePos.x, absolutePos.y + shiftPosY)
                   || tilesManager->checkCollision(absolutePos.x + width - 1, absolutePos.y + shiftPosY)){
                    shiftPosY = absolutePos.y - absolutePos.y / sizeTile * sizeTile;
                }
                Tile* entityColDetect1 = tilesManager->checkCollision_r(absolutePos.x, absolutePos.y + shiftPosY);
                Tile* entityColDetect2 = tilesManager->checkCollision_r(absolutePos.x + width - 1, absolutePos.y + shiftPosY);
                if (entityColDetect1 != nullptr || entityColDetect2 != nullptr) {
                    if (frameEvents < damageExecutor) hp -= lvl;
                    if (entityColDetect1 != nullptr) shiftPosY = entityColDetect1->absolutePos.y + entityColDetect1->size.h - absolutePos.y;
                    else if (entityColDetect2 != nullptr) shiftPosY = entityColDetect2->absolutePos.y + entityColDetect2->size.h - absolutePos.y;
                }
            } else{
                if(absolutePos.y % config->getValue("sizeTile") == 0){
                    if(tilesManager->checkCollision(absolutePos.x, absolutePos.y + sizeTile)
                       || tilesManager->checkCollision(absolutePos.x + width - 1, absolutePos.y + sizeTile)){
                        shiftPosY = 0;
                    }
                    if (tilesManager->checkCollision(absolutePos.x, absolutePos.y + sizeTile, true)
                        || tilesManager->checkCollision(absolutePos.x + width - 1, absolutePos.y + sizeTile, true)) {
                        if(frameEvents < damageExecutor) hp -= lvl;
                        shiftPosY = 0;
                    }
                } else{
                    if(tilesManager->checkCollision(absolutePos.x, absolutePos.y + shiftPosY + sizeTile)
                       || tilesManager->checkCollision(absolutePos.x + width - 1, absolutePos.y + shiftPosY + sizeTile)) {
                        shiftPosY = sizeTile - absolutePos.y % sizeTile;
                    }
                    Tile* entityColDetect1 = tilesManager->checkCollision_r(absolutePos.x, absolutePos.y + shiftPosY + sizeTile);
                    Tile* entityColDetect2 = tilesManager->checkCollision_r(absolutePos.x + width - 1, absolutePos.y + shiftPosY + sizeTile);
                    if (entityColDetect1 != nullptr || entityColDetect2 != nullptr) {
                        if (frameEvents < damageExecutor) hp -= lvl;
                        if (entityColDetect1 != nullptr) shiftPosY = entityColDetect1->absolutePos.y - (absolutePos.y + size.h);
                        else if (entityColDetect2 != nullptr) shiftPosY = entityColDetect2->absolutePos.y - (absolutePos.y + size.h);
                    }
                }
            }
            absolutePos.y += shiftPosY;
        }
        shiftPosY = 0;
    }
    if(shiftPosX != 0){
        if(absolutePos.x + shiftPosX < 0){
            absolutePos.x = 0;
        }
        else if(absolutePos.x + width + shiftPosX > sizeTile * config->getValue("sizeXInTiles")){
            absolutePos.x = sizeTile * config->getValue("sizeXInTiles") - width;
        }
        else{
            if(shiftPosX < 0){
                if(tilesManager->checkCollision(absolutePos.x + shiftPosX, absolutePos.y)
                   || tilesManager->checkCollision(absolutePos.x + shiftPosX, absolutePos.y + height - 1)){
                    shiftPosX = absolutePos.x - absolutePos.x / sizeTile * sizeTile;
                }
                Tile* entityColDetect1 = tilesManager->checkCollision_r(absolutePos.x + shiftPosX, absolutePos.y);
                Tile* entityColDetect2 = tilesManager->checkCollision_r(absolutePos.x + shiftPosX, absolutePos.y + height - 1);
                if (entityColDetect1 != nullptr || entityColDetect2 != nullptr) {
                    if (frameEvents < damageExecutor) hp -= lvl;
                    if (entityColDetect1 != nullptr) shiftPosX = entityColDetect1->absolutePos.x + entityColDetect1->size.w - absolutePos.x;
                    else if (entityColDetect2 != nullptr) shiftPosX = entityColDetect2->absolutePos.x + entityColDetect2->size.w - absolutePos.x;
                }
            } else {
                if(absolutePos.x % sizeTile == 0){
                    if (tilesManager->checkCollision(absolutePos.x + sizeTile, absolutePos.y)
                        || tilesManager->checkCollision(absolutePos.x + sizeTile, absolutePos.y + height - 1)){
                        shiftPosX = 0;
                    }
                    if (tilesManager->checkCollision(absolutePos.x + sizeTile, absolutePos.y, true)
                        || tilesManager->checkCollision(absolutePos.x + sizeTile, absolutePos.y + height - 1, true)) {
                        if (frameEvents < damageExecutor) hp -= lvl;
                        shiftPosX = 0;
                    }
                } else{
                    if(tilesManager->checkCollision(absolutePos.x + shiftPosX + sizeTile, absolutePos.y)
                       || tilesManager->checkCollision(absolutePos.x + shiftPosX + sizeTile, absolutePos.y + height - 1)){
                        shiftPosX = sizeTile - absolutePos.x % sizeTile;
                    }
                    Tile* entityColDetect1 = tilesManager->checkCollision_r(absolutePos.x + shiftPosX + sizeTile, absolutePos.y);
                    Tile* entityColDetect2 = tilesManager->checkCollision_r(absolutePos.x + shiftPosX + sizeTile, absolutePos.y + height - 1);
                    if (entityColDetect1 != nullptr || entityColDetect2 != nullptr) {
                        if (frameEvents < damageExecutor) hp -= lvl;
                        if (entityColDetect1 != nullptr) shiftPosX = entityColDetect1->absolutePos.x - (absolutePos.x + size.w);
                        else if (entityColDetect2 != nullptr) shiftPosX = entityColDetect2->absolutePos.x - (absolutePos.x + size.w);
                    }
                }
            }
            absolutePos.x += shiftPosX;
        }
        shiftPosX = 0;
    }
    texLayers.back()->srcRectTex.x = (rotate * 2 + animNexter) * texLayers.back()->srcRectTex.w;
    Entity::update();
}

void Player::reset() {
    absolutePos = constructPos;
    xp = 0;
    hpMax = hp = startHpMax;
    attackPassive = startAttackPassive;
    defense = startDefense;
    attackCriticalPercent = startAttackCriticalPercent;
    lvl = lvlBackBuffer = 1;
}

void Player::setTilesManager(Tiles *tilesManager) {
    this->tilesManager = tilesManager;
}

void Player::render() {
    Entity::render();
}
