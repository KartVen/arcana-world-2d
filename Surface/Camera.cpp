#include "Camera.h"

Camera* Camera::selfInstance = nullptr;

Camera::Camera():
    position({0,0}),
    dstCameraRect({0,0,0,0}),
    config(Config::getInstance()),
    window(Window::getInstance()),
    wrappedEntity(nullptr){
}

void Camera::initCamera() {
    if(selfInstance == nullptr) selfInstance = new Camera();
}

Camera *Camera::getInstance() {
    if(selfInstance == nullptr){
        std::cerr<<"ERROR: Camera has not been initiated..."<<std::endl;
        exit(3);
    }
    return selfInstance;
}

void Camera::destroyCamera() {
    if(selfInstance != nullptr) delete selfInstance;
    selfInstance = nullptr;
}

void Camera::setWrapEntity(Entity *entity) {
    if(entity == nullptr){
        std::cerr<<"Wrapping Entity is 'nullptr'"<<std::endl;
        exit(3);
    }
    wrappedEntity = entity;
    dstCameraRect.h = entity->height;
    dstCameraRect.w = entity->width;
}

void Camera::update() {
    int tmpPosX = (Window::WINDOW_WIDTH - wrappedEntity->width) / 2;
    position.x = wrappedEntity->absolutePos.x - tmpPosX;
    if(position.x < 0)
        position.x = 0;
    else if(position.x > config->getValue("sizeTile") * config->getValue("sizeXInTiles") - Window::WINDOW_WIDTH)
        position.x = config->getValue("sizeTile") * config->getValue("sizeXInTiles") - Window::WINDOW_WIDTH;

    int tmpPosY = (Window::WINDOW_HEIGHT - wrappedEntity->height) / 2;
    position.y = wrappedEntity->absolutePos.y - tmpPosY;
    if(position.y < 0)
        position.y = 0;
    else if(position.y > config->getValue("sizeTile") * config->getValue("sizeYInTiles") - Window::WINDOW_HEIGHT)
        position.y = config->getValue("sizeTile") * config->getValue("sizeYInTiles") - Window::WINDOW_HEIGHT;

    dstCameraRect.x = wrappedEntity->absolutePos.x - position.x;
    dstCameraRect.y = wrappedEntity->absolutePos.y - position.y;
}

void Camera::render() {
    window->drawTexture(wrappedEntity->texLayers.back()->sdlTex, &wrappedEntity->texLayers.back()->srcRectTex, &dstCameraRect);
    wrappedEntity->headText->textRect.x = dstCameraRect.x + (config->getValue("sizeTile") - wrappedEntity->headText->textRect.w) / 2;
    wrappedEntity->headText->textRect.y = dstCameraRect.y - wrappedEntity->headText->textRect.h;
    wrappedEntity->headText->render();
}
