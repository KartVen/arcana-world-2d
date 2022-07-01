#include <SDL_ttf.h>
#include "OverScreen.h"
#include "../../Window/Window.h"

OverScreen* OverScreen::selfInstance = nullptr;

OverScreen::OverScreen():
        bgMenuRect({0,0,0,0}){
    eventsHandler = Events::getEvents();
    //SDL_SetRenderDrawColor(Window::getInstance()->getSDLRenderer(), 0, 0, 0, (double) 10/100 * 255);
    //SDL_SetRenderDrawBlendMode(Window::getInstance()->getSDLRenderer(), SDL_BLENDMODE_BLEND);
    SDL_Color colorSetter = {255,255,255,255};

    titleGame = new Text(
            "Game Over",
            (double) Window::WINDOW_HEIGHT/4 * 125/192,
            0,
            (double) Window::WINDOW_HEIGHT * 106/768,
            colorSetter
    );

    titleGame->textRect.x = ((double) Window::WINDOW_WIDTH - titleGame->textRect.w)/2;

    const char* labels[] = { "New Game", "Quit" };

    int tmpPosY = (double) Window::WINDOW_HEIGHT * 4/7;
    int tmpSize = (double) Window::WINDOW_HEIGHT/9 * 500/768;
    for(unsigned int label = 0; label < sizeof(labels)/sizeof(*labels); label++){
        menuLabels.emplace_back(new Text(labels[label], tmpSize, 0, 0, colorSetter));
        menuLabels.back()->textRect.x = ((double) Window::WINDOW_WIDTH - menuLabels.back()->textRect.w)/2;
        menuLabels.back()->textRect.y = tmpPosY + label * menuLabels.back()->textRect.h;
    }

    menuLabels.resize(menuLabels.size());
    running = false;
    keyState = 0;
}

OverScreen::~OverScreen() {
    for(Text* label : menuLabels) delete label;
}

OverScreen *OverScreen::getInstance() {
    if(selfInstance == nullptr) selfInstance = new OverScreen();
    return selfInstance;
}

void OverScreen::destroyScreen() {
    if(selfInstance != nullptr) delete selfInstance;
    selfInstance = nullptr;
}

bool OverScreen::handleEvents() {
    for(unsigned int label = 0; label < menuLabels.size(); label++){
        bool labelY = menuLabels[label]->textRect.y <= eventsHandler->mouse.position.y && eventsHandler->mouse.position.y < menuLabels[label]->textRect.y + menuLabels[label]->textRect.h;
        bool labelX = menuLabels[label]->textRect.x <= eventsHandler->mouse.position.x && eventsHandler->mouse.position.x < menuLabels[label]->textRect.x + menuLabels[label]->textRect.w;
        if(labelY && labelX){
            menuLabels[label]->color = {33,44,238,255};
            if(eventsHandler->mouse.btnLeft.isClicked){
                if(label == 0) running = false;
                else if(label == 1) return false;
            }
        } else
            menuLabels[label]->color = {255, 255, 255, 255};
    }
    return true;
}

void OverScreen::update() {
    bgMenuRect.h = Window::WINDOW_HEIGHT;
    bgMenuRect.w = Window::WINDOW_WIDTH;

    for(Text* label : menuLabels) label->update();
}

void OverScreen::render() {
    SDL_RenderFillRect(Window::getInstance()->getSDLRenderer(), &bgMenuRect);
    titleGame->render();
    for(Text* label : menuLabels) label->render();
}