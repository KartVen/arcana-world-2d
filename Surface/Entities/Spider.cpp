#include "Spider.h"
#include "Player.h"

Spider::Spider(int xp, int posX, int posY, Texture *texture):
    Entity("Spider", posX, posY, (texture != nullptr)? texture:Textures::getTextures()->entity_spider_0){
    this->xp = xp;
    for (int v = 0; v < config->lvlXpTable.size() && xp >= config->lvlXpTable[v]; v++) lvl = v;
    startHpMax = hpMax = hp = 299 + 2 * lvl;
    startAttackPassive = attackPassive = 4 + 1.1 * lvl;
    startDefense = defense = 3 + 1.1 * lvl;
    startAttackCriticalPercent = attackCriticalPercent = 2.5 + 1.1 * lvl;
    hpMaxBooster = 3;
}

void Spider::update() {
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

void Spider::render() {
    Entity::render();
}
