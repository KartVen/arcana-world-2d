#include "Surface.h"
#include "Entities/Spider.h"
#include "Entities/Mag.h"
#include "Entities/Cactuser.h"
#include "Entities/Bat.h"

Surface* Surface::selfInstance = nullptr;

Surface::Surface() {
    restart = false;
    eventsHandler = Events::getEvents();
    auto posTile = [](unsigned int tile){ return (tile - 1) * Config::getInstance()->getValue("sizeTile"); };

    Camera::initCamera();
    Player::initPlayer("Player", posTile(3), posTile(38));

    pauseScreen = PauseScreen::getInstance();
    overScreen = OverScreen::getInstance();
    camera = Camera::getInstance();
    player = Player::getInstance();

    map1 = new Map("assets/data/map/0.map");

    sceneManager1 = new Scene(*map1);
    randAndAddEntity(sceneManager1,1);

    camera->setWrapEntity(player);
    player->setTilesManager(sceneManager1);

}

Surface::~Surface() {
    eventsHandler = nullptr;
    PauseScreen::destroyScreen();
    pauseScreen = nullptr;
    OverScreen::destroyScreen();
    overScreen = nullptr;
    Camera::destroyCamera();
    camera = nullptr;
    Player::destroyPlayer();
    player = nullptr;
    delete map1;
    map1 = nullptr;
    delete sceneManager1;
    sceneManager1 = nullptr;
}

Surface *Surface::getInstance() {
    if(selfInstance == nullptr) selfInstance = new Surface();
    return selfInstance;
}

void Surface::destroySurface() {
    if(selfInstance != nullptr) delete selfInstance;
    selfInstance = nullptr;
}

bool Surface::handleEvents() {
    if(pauseScreen->running)
        return pauseScreen->handleEvents();
    if(eventsHandler->key.ESCAPE.isClicked && !eventsHandler->key.ESCAPE.wasClicked){
        pauseScreen->running = true; return true;
    }
    else{
        if(overScreen->running){
            if(overScreen->handleEvents()){
                bool newGame = overScreen->handleEvents();
                if(newGame && !restart){
                    randAndAddEntity(sceneManager1,1);
                    restart = true;
                }
                player->reset();
                return true;
            } else
                return false;
        }
        else{
            overScreen->running = !player->handleEvent();
            if(sceneManager1->countEntity() == 0) overScreen->running = true;
            restart = false;
        }

    }
    return true;
}

void Surface::randAndAddEntity(Tiles *tilesManager, int mode) {
    tilesManager->clearEntity();
    auto posTile = [](unsigned int tile){ return (tile - 1) * Config::getInstance()->getValue("sizeTile"); };
    switch (mode) {
        default: {
            unsigned int entityMapYX[17][2] = {
                    {4,  3}, {15, 2}, {24, 10}, {16, 17}, {36, 17}, {9,  19}, {31, 24}, {19, 27}, {22, 30},
                    {13, 36}, {29, 37}, {15, 42}, {32, 43}, {25, 44}, {18, 49}, {39, 54}, {24, 58}
            };
            for (auto &pos: entityMapYX) {
                int randEntityType = rand() % 4;
                int xp = rand() % Config::getInstance()->lvlXpTable.back();
                if (randEntityType == 0)
                    tilesManager->addEntity(new Bat(xp / 4, posTile(pos[1]), posTile(pos[0])));
                else if (randEntityType == 1)
                    tilesManager->addEntity(new Cactuser(xp / 3, posTile(pos[1]), posTile(pos[0])));
                else if (randEntityType == 2)
                    tilesManager->addEntity(new Spider(xp / 2, posTile(pos[1]), posTile(pos[0])));
                else if (randEntityType == 3)
                    tilesManager->addEntity(new Mag(xp, posTile(pos[1]), posTile(pos[0])));

            }
            break;
        }
    }
}

void Surface::update() {
    if(pauseScreen->running)
        pauseScreen->update();
    else if(overScreen->running)
        overScreen->update();
    else {
        player->update();
        camera->update();
        sceneManager1->update();
    }
}

void Surface::render() {
    sceneManager1->render();
    camera->render();
    if(pauseScreen->running) pauseScreen->render();
    if(overScreen->running) overScreen->render();
}
