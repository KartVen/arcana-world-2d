#include "Bat.h"
#include "../../Manager/Tiles.h"
#include <cmath>
#include "Player.h"

Bat::Bat(int xp, int posX, int posY, Texture *texture):
    Entity("Bat", posX, posY, Textures::getTextures()->entity_bat_0) {
    this->xp = xp;
    for (int v = 0; v < config->lvlXpTable.size() && xp >= config->lvlXpTable[v]; v++) lvl = v;
    startHpMax = hpMax = hp = 99 + 2 * lvl;
    startAttackPassive = attackPassive = 8 + 1.1 * lvl;
    startDefense = defense = 8 + 1.1 * lvl;
    startAttackCriticalPercent = attackCriticalPercent = 7.5 + 1.1 * lvl;
    hpMaxBooster = 1;
}

void Bat::update() {
    ai = true;
    Player* player = Player::getInstance();
    SDL_Point playerPoints[] = {
        {player->absolutePos.x, player->absolutePos.y}, {player->absolutePos.x + player->size.w, player->absolutePos.y},
        {player->absolutePos.x, player->absolutePos.y + player->size.h}, {player->absolutePos.x + player->size.w, player->absolutePos.y + player->size.h}
    };
    SDL_Point eyePoints[] = {
        {absolutePos.x - eyeRange, absolutePos.y - eyeRange}, {(int)(absolutePos.x + 1.5 * eyeRange), (int)(absolutePos.y + 1.5 * eyeRange)}
    };
    if (eyePoints[0].x < playerPoints[0].x && playerPoints[0].x < eyePoints[1].x && eyePoints[0].y < playerPoints[0].y && playerPoints[0].y < eyePoints[1].y
        || eyePoints[0].x < playerPoints[1].x && playerPoints[1].x < eyePoints[1].x && eyePoints[0].y < playerPoints[1].y && playerPoints[1].y < eyePoints[1].y
        || eyePoints[0].x < playerPoints[2].x && playerPoints[2].x < eyePoints[1].x && eyePoints[0].y < playerPoints[2].y && playerPoints[2].y < eyePoints[1].y
        || eyePoints[0].x < playerPoints[3].x && playerPoints[3].x < eyePoints[1].x && eyePoints[0].y < playerPoints[3].y && playerPoints[3].y < eyePoints[1].y)
        ai = false;
    Entity::update();
}

void Bat::render() {
    Entity::render();
}
