#include "Tiles.h"
#include "../Surface/Entities/Player.h"
#include "../Surface/Entities/Spider.h"
#include "../Surface/Entities/Mag.h"
#include "../Surface/Entities/Cactuser.h"
#include "../Surface/Entities/Bat.h"

Map* Tiles::map = nullptr;
std::vector<Entity*> Tiles::mapEntity = {};

void Tiles::switchTile(Tile &tile, int token) {
    Textures *texturesManager = Textures::getTextures();
    switch (token) {
        case 0:
            switch (rand() % 4) {
                case 1:
                    tile.addTexLayer(texturesManager->map_grass_1);
                    break;
                case 2:
                    tile.addTexLayer(texturesManager->map_grass_2);
                    break;
                case 3:
                    tile.addTexLayer(texturesManager->map_grass_3);
                    break;
                default:
                    tile.addTexLayer(texturesManager->map_grass_0);
                    break;
            }
            break;
        case 3:
            tile.addTexLayer(texturesManager->map_dirt);
            break;
        case 4:
            switch (rand() % 3) {
                case 1:
                    tile.addTexLayer(texturesManager->map_water_1);
                    break;
                case 2:
                    tile.addTexLayer(texturesManager->map_water_2);
                    break;
                default:
                    tile.addTexLayer(texturesManager->map_water_0);
                    break;
            }
            tile.collision = true;
            break;
        case 6:
            tile.addTexLayer(texturesManager->map_grass_0);
            tile.addTexLayer(texturesManager->map_flower_0);
            break;
        case 8:
            tile.addTexLayer(texturesManager->map_grass_0);
            tile.addTexLayer(texturesManager->map_tree_0);
            tile.collision = true;
            break;
        default:
            break;
    }
}

Tiles::Tiles(const std::string &levelMapPath, char delimChar) {
    config = Config::getInstance();
    camera = Camera::getInstance();
    map = new Map(levelMapPath, delimChar);
    mapEntity.resize(0);
    shiftRenderX = shiftRenderY = 0;
    startRenderIdX = startRenderIdY = 0;
    stopRenderIdX = stopRenderIdY = 0;
}

Tiles::Tiles(const Map &mapObj) {
    config = Config::getInstance();
    camera = Camera::getInstance();
    map = new Map(mapObj);
    mapEntity.resize(0);
    shiftRenderX = shiftRenderY = 0;
    startRenderIdX = startRenderIdY = 0;
    stopRenderIdX = stopRenderIdY = 0;
}

Tiles::~Tiles() {
    for (Entity *&entity: mapEntity)
        if (entity != nullptr)
            delete entity;
    if (map != nullptr)
        delete map;
    map = nullptr;
    std::vector<Entity *>().swap(mapEntity);
    config = nullptr;
    camera = nullptr;
}

Tile *Tiles::getTile(unsigned int idY, unsigned int idX) {
    if (idY > map->map.size()) return new Tile();
    if (idX > map->map[idY].size()) return new Tile();
    return map->map[idY][idX];
}

void Tiles::addEntity(Entity *entity) {
    if (entity == Player::getInstance()) return;
    if (mapEntity.empty()) {
        mapEntity.emplace_back(entity);
        return;
    }
    for (auto &entityMap: mapEntity) {
        if (entityMap->absolutePos.x < entity->absolutePos.x
            && entity->absolutePos.x < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w - 1) {
            if (entityMap->absolutePos.y < entity->absolutePos.y
                && entity->absolutePos.y < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h - 1)
                return;
            if (entityMap->absolutePos.y < entity->absolutePos.y + entity->texLayers.back()->dstRectTex.h - 1
                && entity->absolutePos.y + entity->texLayers.back()->dstRectTex.h - 1 <
                   entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h - 1)
                return;
        }
        if (entityMap->absolutePos.y < entity->absolutePos.y
            && entity->absolutePos.y < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h - 1) {
            if (entityMap->absolutePos.x < entity->absolutePos.x
                && entity->absolutePos.x < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w - 1)
                return;
            if (entityMap->absolutePos.x < entity->absolutePos.x + entity->texLayers.back()->dstRectTex.w - 1
                && entity->absolutePos.x + entity->texLayers.back()->dstRectTex.w - 1 <
                   entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w - 1)
                return;
        }
    }
    mapEntity.emplace_back(entity);
}

Entity * Tiles::getEntity(const SDL_Rect &playerTile, int rotate) {
    switch (rotate) {
        case ROTATE::DOWN: {
            int playerH1 = playerTile.y + playerTile.h - 1 + config->getValue("velocity") + 10;
            for (auto &entityMap: mapEntity) {
                if (entityMap->absolutePos.y <= playerH1 && playerH1 < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h) {
                    int entityW1 = entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w;
                    int playerW1 = playerTile.x + playerTile.w - 1;
                    if (entityMap->absolutePos.x <= playerTile.x && playerTile.x < entityW1 || entityMap->absolutePos.x <= playerW1 && playerW1 < entityW1)
                        return entityMap;
                }
            }
            break;
        }
        case ROTATE::LEFT: {
            int playerW0 = playerTile.x - config->getValue("velocity") - 10;
            for (auto &entityMap: mapEntity) {
                if (entityMap->absolutePos.x <= playerW0 && playerW0 < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w) {
                    int entityH1 = entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h;
                    int playerH1 = playerTile.y + playerTile.h - 1;
                    if (entityMap->absolutePos.y <= playerTile.y && playerTile.y < entityH1 || entityMap->absolutePos.y <= playerH1 && playerH1 < entityH1)
                        return entityMap;
                }
            }
            break;
        }
        case ROTATE::UP: {
            int playerH0 = playerTile.y - config->getValue("velocity") - 10;
            for (auto &entityMap: mapEntity) {
                if (entityMap->absolutePos.y <= playerH0 && playerH0 < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h) {
                    int entityW1 = entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w;
                    int playerW1 = playerTile.x + playerTile.w - 1;
                    if (entityMap->absolutePos.x <= playerTile.x && playerTile.x < entityW1 || entityMap->absolutePos.x <= playerW1 && playerW1 < entityW1)
                        return entityMap;
                }
            }
            break;
        }
        case ROTATE::RIGHT: {
            int playerW1 = playerTile.x + playerTile.w - 1 + config->getValue("velocity") + 10;
            for (auto &entityMap: mapEntity) {
                if (entityMap->absolutePos.x <= playerW1 && playerW1 < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w) {
                    int entityH1 = entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h;
                    int playerH1 = playerTile.y + playerTile.h - 1;
                    if (entityMap->absolutePos.y <= playerTile.y && playerTile.y < entityH1 || entityMap->absolutePos.y <= playerH1 && playerH1 < entityH1)
                        return entityMap;
                }
            }
            break;
        }
        default:
            return nullptr;
    }
    return nullptr;
}

bool Tiles::attackEntity(const SDL_Rect playerTile, const int rotate, int *hp, const int hpMax, int *xp, const int attackPassive, const int defense, const int attackCriticalPercent) {

    Entity *entity = getEntity(playerTile, rotate);
    if(entity){
        while(entity->hp > 0 && *hp > 0) {
            int playerDamage = (int) (attackPassive * ((rand() * 101 <= attackCriticalPercent) ? 1.3 : 1)) - ((rand() * 101 <= 10) ? entity->defense:0);
            int entityDamage = (int) (entity->attackPassive * ((rand() * 101 <= entity->attackCriticalPercent) ? 1.3 : 1)) - ((rand() * 101 <= 10) ? defense:0);
            if ((int) rand() % 2 == 1) {
                entity->hp -= (playerDamage > 0) ? playerDamage : 0;
                if (entity->hp < 0) break;
                *hp -= (entityDamage > 0) ? entityDamage : 0;
            } else {
                entity->hp -= (playerDamage > 0) ? playerDamage : 0;
                if (entity->hp < 0) break;
                *hp -= (entityDamage > 0) ? entityDamage : 0;
            }
        }
        if(*hp <= 0) {
            return false;
        }
        if(entity->hp <= 0){
            entity->active = false;
            *xp += (int) (entity->xp * 0.1);
            *hp += 100 + entity->lvl;
            return true;
        }
    }
    return true;
}

bool Tiles::attackEntity2(int rotate) {
    Player* playerTile = Player::getInstance();
    Entity *entity = getEntity({playerTile->absolutePos.x, playerTile->absolutePos.y, playerTile->size.w, playerTile->size.h}, rotate);
    if(entity){
        while(entity->hp > 0 && playerTile->hp > 0) {
            int playerDamage = (int) (playerTile->attackPassive * ((rand() * 101 <= playerTile->attackCriticalPercent) ? 1.3 : 1)) - ((rand() * 101 <= 10) ? entity->defense:0);
            int entityDamage = (int) (entity->attackPassive * ((rand() * 101 <= entity->attackCriticalPercent) ? 1.3 : 1)) - ((rand() * 101 <= 10) ? playerTile->defense:0);
            if ((int) rand() % 2 == 1) {
                entity->hp -= (playerDamage > 0) ? playerDamage : 0;
                if (entity->hp < 0) break;
                playerTile->hp -= (entityDamage > 0) ? entityDamage : 0;
            } else {
                entity->hp -= (playerDamage > 0) ? playerDamage : 0;
                if (entity->hp < 0) break;
                playerTile->hp -= (entityDamage > 0) ? entityDamage : 0;
            }
        }
        if(playerTile->hp <= 0) {
            return false;
        }
        if(entity->hp <= 0){
            entity->active = false;
            playerTile->xp += (int) (entity->xp * 0.1);
            playerTile->hp += 100 + entity->lvl;
            return true;
        }
    }
    return true;
}

void Tiles::clearEntity() {
    for (Entity* &entity: mapEntity)
        delete entity;
    std::vector<Entity*>(0).swap(mapEntity);
}

void Tiles::showCollision() {
    if (map == nullptr) {
        std::cout << "Map is nullptr..." << std::endl;
        return;
    }
    if (map->map.empty()) {
        std::cout << "Collision map is empty..." << std::endl;
        return;
    }
    for (auto &y: map->map) {
        for (auto x: y)
            std::cout << x->collision << " ";
        std::cout << std::endl;
    }
}

bool Tiles::checkCollision(int dstPosX, int dstPosY, bool entityOnly) {
    if (entityOnly) {
        for (auto& entityMap : mapEntity)
            if (entityMap->absolutePos.x <= dstPosX && dstPosX < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w
                && entityMap->absolutePos.y <= dstPosY && dstPosY < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h)
                return true;
        return false;
    }
    int x = dstPosX / Config::getInstance()->getValue("sizeTile");
    int y = dstPosY / Config::getInstance()->getValue("sizeTile");
    if (y >= Config::getInstance()->getValue("sizeYInTiles") || y < 0) return true;
    if (x >= Config::getInstance()->getValue("sizeXInTiles") || x < 0) return true;
    return map->map[y][x]->collision;
}

Entity* Tiles::checkCollision_r(int dstPosX, int dstPosY) {
    for (auto& entityMap : mapEntity)
        if (entityMap->absolutePos.x <= dstPosX && dstPosX < entityMap->absolutePos.x + entityMap->texLayers.back()->dstRectTex.w
            && entityMap->absolutePos.y <= dstPosY && dstPosY < entityMap->absolutePos.y + entityMap->texLayers.back()->dstRectTex.h)
            return entityMap;
    return nullptr;
}

void Tiles::update() {
    int sizeTile = config->getValue("sizeTile");
    shiftRenderY = camera->getPosY() % sizeTile;
    if (shiftRenderY == 0 && camera->getPosY() == sizeTile)
        shiftRenderY = sizeTile;

    if (camera->getPosY() <= sizeTile)
        startRenderIdY = 0;
    else
        startRenderIdY = camera->getPosY() / sizeTile;

    stopRenderIdY = (camera->getPosY() + Window::WINDOW_HEIGHT) / sizeTile;
    if (camera->getPosY() + Window::WINDOW_HEIGHT < Window::WINDOW_HEIGHT - sizeTile)
        stopRenderIdY++;

    shiftRenderX = camera->getPosX() % sizeTile;
    if (shiftRenderX == 0 && camera->getPosX() == sizeTile)
        shiftRenderX = sizeTile;

    if (camera->getPosX() <= sizeTile)
        startRenderIdX = 0;
    else
        startRenderIdX = camera->getPosX() / sizeTile;

    stopRenderIdX = (camera->getPosX() + Window::WINDOW_WIDTH) / sizeTile;
    if (camera->getPosX() + Window::WINDOW_WIDTH < Window::WINDOW_WIDTH - sizeTile)
        stopRenderIdX++;

    map->update(startRenderIdX, startRenderIdY, stopRenderIdX, stopRenderIdY);
    for (int entityLabel = 0; entityLabel < mapEntity.size(); entityLabel++) {
        if(!mapEntity[entityLabel]->active){
            delete mapEntity[entityLabel];
            mapEntity[entityLabel] = nullptr;
            mapEntity.erase(mapEntity.begin() + entityLabel);
            entityLabel--;
            continue;
        }
        mapEntity[entityLabel]->update();
    }
}

void Tiles::render() {
    for (int y = startRenderIdY; y <= stopRenderIdY && y < config->getValue("sizeYInTiles"); y++)
        for (int x = startRenderIdX; x <= stopRenderIdX && x < config->getValue("sizeXInTiles"); x++) {
            int tilePosX = (int) (x - startRenderIdX) * 32 - shiftRenderX;
            int tilePosY = (int) (y - startRenderIdY) * 32 - shiftRenderY;
            map->map[y][x]->relativeMode = true;
            map->map[y][x]->relativePos = {tilePosX, tilePosY};
            map->map[y][x]->render();
            map->map[y][x]->relativeMode = false;
        }
    int startRenderPxX = startRenderIdX * config->getValue("sizeTile");
    int stopRenderPxX = stopRenderIdX * config->getValue("sizeTile");
    int startRenderPxY = startRenderIdY * config->getValue("sizeTile");
    int stopRenderPxY = stopRenderIdY * config->getValue("sizeTile");
    for (auto &entityMap: mapEntity) {
        if (entityMap && startRenderPxX <= entityMap->absolutePos.x && entityMap->absolutePos.x <= stopRenderPxX
            && startRenderPxY <= entityMap->absolutePos.y && entityMap->absolutePos.y <= stopRenderPxY) {
            entityMap->relativeMode = true;
            entityMap->relativePos = {
                    entityMap->absolutePos.x - startRenderPxX - shiftRenderX,
                    entityMap->absolutePos.y - startRenderPxY - shiftRenderY
            };
            entityMap->render();
            entityMap->relativeMode = false;
        }
    }
}
