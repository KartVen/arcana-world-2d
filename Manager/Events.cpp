#include <iostream>
#include "Events.h"

Events *Events::selfInstance = nullptr;

Events *Events::getEvents() {
    if (selfInstance == nullptr) selfInstance = new Events();
    return selfInstance;
}

void Events::destroyEvents() {
    delete selfInstance;
    selfInstance = nullptr;
}

void Events::updateKeyState() {
    winKey = { /*.MINIMALIZE =*/ false, /*.QUIT =*/ false};

    key.SPACE.reset();
    key.ESCAPE.reset();

    SDL_PollEvent(&sdlEvent);

    switch (sdlEvent.type) {
        case SDL_QUIT:
            winKey.QUIT = true;
            break;
        case SDL_KEYDOWN:
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key.ESCAPE = true;
                    break;
                case SDLK_SPACE:
                    key.SPACE = true;
                    break;
                case SDLK_w:
                    key.w = true;
                    break;
                case SDLK_a:
                    key.a = true;
                    break;
                case SDLK_s:
                    key.s = true;
                    break;
                case SDLK_d:
                    key.d = true;
                    break;
                case SDLK_UP:
                    key.UP = true;
                    break;
                case SDLK_LEFT:
                    key.LEFT = true;
                    break;
                case SDLK_DOWN:
                    key.DOWN = true;
                    break;
                case SDLK_RIGHT:
                    key.RIGHT = true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key.ESCAPE = false;
                    break;
                case SDLK_SPACE:
                    key.SPACE = false;
                    break;
                case SDLK_w:
                    key.w = false;
                    break;
                case SDLK_a:
                    key.a = false;
                    break;
                case SDLK_s:
                    key.s = false;
                    break;
                case SDLK_d:
                    key.d = false;
                    break;
                case SDLK_UP:
                    key.UP = false;
                    break;
                case SDLK_LEFT:
                    key.LEFT = false;
                    break;
                case SDLK_DOWN:
                    key.DOWN = false;
                    break;
                case SDLK_RIGHT:
                    key.RIGHT = false;
                    break;
            }
        case SDL_MOUSEMOTION:
            mouse.position = sdlEvent.motion;
            break;
        case SDL_MOUSEBUTTONUP:
            switch (sdlEvent.button.button) {
                case SDL_BUTTON_LEFT:
                    mouse.btnLeft = false;
                    break;
                case SDL_BUTTON_MIDDLE:
                    mouse.btnMiddle = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouse.btnRight = false;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (sdlEvent.button.button) {
                case SDL_BUTTON_LEFT:
                    mouse.btnLeft = true;
                    break;
                case SDL_BUTTON_MIDDLE:
                    mouse.btnMiddle = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouse.btnRight = true;
                    break;
            }
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_WaitEvent(&sdlEvent);
            break;
    }

    SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
}
