#include <cmath>
#include "App.h"
#include "Utility/Config.h"
#include <iostream>

App* App::selfInstance = nullptr;

App::App() {
    appQuit = false;
    windowInstance = nullptr;
    eventsHandler = nullptr;

    Config::initConfig();
    //if(!Config::getInstance()->isCorrect()) appQuit = true;

    Window::initWindow();
    windowInstance = Window::getInstance();
    if(!windowInstance->isRunning()) appQuit = true;

    startScreen = StartScreen::getInstance();

    eventsHandler = Events::getEvents();
    Textures::initTextures();
    surfaceGame = Surface::getInstance();
}

App::~App() {
    StartScreen::destroyScreen();
    startScreen = nullptr;
    Config::destroyConfig();
    Textures::destroyTextures();
    Window::destroyWindow();
    windowInstance = nullptr;
    Events::destroyEvents();
    eventsHandler = nullptr;
    Surface::destroySurface();
    surfaceGame = nullptr;
}

App *App::getApp() {
    if(selfInstance == nullptr) selfInstance = new App();
    return selfInstance;
}

void App::runningApp() {
    Uint64 realTimeTicks = 0;
    const double oneFrameTime = 1000.0/60;
    while(!appQuit){
        realTimeTicks = SDL_GetPerformanceCounter();

        appQuit = !handleEvent();
        update();
        render();
        windowInstance->updateSurface();

        realTimeTicks = SDL_GetPerformanceCounter() - realTimeTicks;
        SDL_Delay((Uint32) floor((Uint64) oneFrameTime - (realTimeTicks/SDL_GetPerformanceFrequency() * 1000.0f)));
    }
}

void App::destroyApp() {
    delete selfInstance;
    selfInstance = nullptr;
}

bool App::handleEvent() {
    eventsHandler->updateKeyState();
    if(eventsHandler->isQUIT()) return false;
    if(startScreen->running) return startScreen->handleEvents();
    return surfaceGame->handleEvents();
}

void App::update() {
    if(startScreen->running) {
        startScreen->update();
    }
    else
        surfaceGame->update();
}

void App::render() {
    SDL_RenderClear(Window::getInstance()->getSDLRenderer());
    if(startScreen->running) {
        startScreen->render();
    }
    else
        surfaceGame->render();
    SDL_RenderPresent(Window::getInstance()->getSDLRenderer());
}


