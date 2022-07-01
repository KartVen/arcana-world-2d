#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string &texturePath, int srcWidth, int srcHeight, int dstWidth, int dstHeight, int posX, int posY):
    srcRectTex({0, 0, srcWidth, srcHeight}),
    dstRectTex({ posX, posY, dstWidth, dstHeight }),
    sdlTex(nullptr),
    textureDstPath(texturePath),
    windowInstance(Window::getInstance()){
    changeTexture(texturePath);
}

Texture::Texture(const Texture &texture):
        srcRectTex(texture.srcRectTex),
        dstRectTex(texture.dstRectTex),
        sdlTex(nullptr),
        textureDstPath(texture.textureDstPath),
        windowInstance(Window::getInstance()){
    changeTexture(textureDstPath);
}

Texture::~Texture() {
    SDL_UnlockTexture(sdlTex);
    if(sdlTex != nullptr)
        SDL_DestroyTexture(sdlTex);
    sdlTex = nullptr;
    windowInstance = nullptr;
}

void Texture::changeTexture(const std::string& texturePath) {
    SDL_Surface* textureSurface = IMG_Load(texturePath.c_str());
    sdlTex = SDL_CreateTextureFromSurface(windowInstance->getSDLRenderer(), textureSurface);
    SDL_FreeSurface(textureSurface);
}

void Texture::drawTexture(int posX, int posY) {
    if(posX != dstRectTex.x || posY != dstRectTex.y){
        dstRectTex.x = posX;
        dstRectTex.y = posY;
    }
    windowInstance->drawTexture(sdlTex, &srcRectTex, &dstRectTex);
}

void Texture::drawTexture(SDL_Rect *dstRect) {
    windowInstance->drawTexture(sdlTex, &srcRectTex, dstRect);
}

