#include "Window.h"
#include "../Utility/Config.h"
#include <iostream>

Window* Window::selfInstance = nullptr;
int Window::WINDOW_WIDTH = 1024;//800;
int Window::WINDOW_HEIGHT = 768;//608;
//bool Window::running = false;

Window::Window():
    objWindow(nullptr),
    objRenderer(nullptr),
    running(false){
    running = createWindow();
}

Window::~Window() {
    running = false;
    SDL_DestroyWindow(objWindow);
    objWindow = nullptr;
    SDL_DestroyRenderer(objRenderer);
    objRenderer = nullptr;
    IMG_Quit();
    SDL_Quit();
}

bool Window::createWindow() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error: SDL_Init Initializing failed: %s\n", SDL_GetError());
        return false;
    }

    if(TTF_Init() != 0){
        printf("Error: TTF_Init Initializing failed: %s\n", SDL_GetError());
        return false;
    }

    objWindow = SDL_CreateWindow(
            "ArcanaWorld2D",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if(objWindow == nullptr){
        printf("Error: Window Creating failed: %s\n", SDL_GetError());
        return false;
    }

    objRenderer = SDL_CreateRenderer(objWindow, -1, SDL_RENDERER_ACCELERATED);

    if(objRenderer) SDL_SetRenderDrawColor(objRenderer, 0, 0, 0, 255);

    SDL_Surface *icon = SDL_LoadBMP("assets/textures/icon/icon.bmp");
    if (icon)
    {
        SDL_SetColorKey(icon, true, SDL_MapRGB(icon->format, 0, 0, 0));
        SDL_SetWindowIcon(objWindow, icon);
    }
    else
        printf("Failed to load window icon! (%s)\n", SDL_GetError());
    SDL_FreeSurface(icon);
    icon = nullptr;

    updateSurface();

    running = true;
    return true;
}

void Window::initWindow() {
    if(selfInstance == nullptr) selfInstance = new Window();
}

Window *Window::getInstance() {
    if(selfInstance == nullptr){
        std::cerr<<"ERROR: Window has not been initiated..."<<std::endl;
        exit(2);
    }
    return selfInstance;
}

void Window::destroyWindow() {
    if(selfInstance == nullptr) return;
    delete selfInstance;
    selfInstance = nullptr;
}

void Window::drawTexture(SDL_Texture *objTexture, SDL_Rect *srcRect, SDL_Rect *dstRect) {
    if(objTexture != nullptr)
        SDL_RenderCopy(objRenderer, objTexture, srcRect, dstRect);
}

bool Window::updateSurface() {
    return (bool) SDL_UpdateWindowSurface(objWindow);
}