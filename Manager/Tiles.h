#pragma once

#include "../Utility/Config.h"
#include "../Surface/Camera.h"
#include "../Surface/Maps/Map.h"
#include "../Surface/Entities/Player.h"

class Tiles;
using Scene = Tiles;

class Tiles {
private:
    /*! \brief Wskaźnik do instancji klasy konfiguracyjnej.*/
    Config* config;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Kamerę.*/
    Camera* camera;
public:
    static Map* map;
    static std::vector<Entity*> mapEntity;
private:
    int shiftRenderX, shiftRenderY;
    int startRenderIdX, startRenderIdY;
    int stopRenderIdX, stopRenderIdY;
    Entity *getEntity(const SDL_Rect& playerTile, int rotate);
public:
    explicit Tiles(const std::string& levelMapPath, char delimChar = ',');
    explicit Tiles(const Map &mapObj);
    ~Tiles();
    Tile *getTile(unsigned int idY, unsigned int idX);
    static void switchTile(Tile &tile, int token);
    void addEntity(Entity* entity);
    bool attackEntity(SDL_Rect playerTile, int rotate, int *hp, int hpMax, int *xp, int attackPassive, int defense, int attackCriticalPercent);
    bool attackEntity2(int rotate);
    inline unsigned int countEntity() const { return (unsigned int) mapEntity.size(); }
    void clearEntity();
    void showCollision();
    static bool checkCollision(int dstPosX, int dstPosY, bool entityOnly = false);
    static Entity* checkCollision_r(int dstPosX, int dstPosY);
    void update();
    void render();
};


