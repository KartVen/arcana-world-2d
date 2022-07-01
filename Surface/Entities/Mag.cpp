#include "Mag.h"
#include "Player.h"

Mag::Mag(int xp, int posX, int posY, Texture *texture):
    Entity("Mag", posX, posY, (texture != nullptr)? texture:Textures::getTextures()->entity_mag_0){
    this->xp = xp;
    for (int v = 0; v < config->lvlXpTable.size() && xp >= config->lvlXpTable[v]; v++) lvl = v;
    startHpMax = hpMax = hp = 499 + 2 * lvl;
    attackPassive = attackPassive = 2 + 1.1 * lvl;
    startDefense = defense = 1 + 1.1 * lvl;
    startAttackCriticalPercent = attackCriticalPercent = 2 + 1.1 * lvl;
    hpMaxBooster = 4;
}

void Mag::update() {
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

void Mag::render() {
    Entity::render();
}