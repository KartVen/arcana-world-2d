#include "Text.h"
#include "../../Window/Window.h"

Text::Text(const std::string& content, int size, int posX, int posY, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const std::string& fontFromFonts):
    color({r,g,b,a}),
    colorBackBuffer({r,g,b,a}),
    textRect({posX, posY,0, 0}){
    this->fontFromFonts = fontFromFonts;
    this->content = content;
    contentBackBuffer = content;
    font = TTF_OpenFont(("assets/fonts/" + fontFromFonts).c_str(), size);
    textSurface = TTF_RenderText_Solid(font, content.c_str(), {r,g,b,a});
    textTexture = SDL_CreateTextureFromSurface(Window::getInstance()->getSDLRenderer(), textSurface);
    textRect.w = textSurface->w; textRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;
}

Text::Text(const std::string &content, int size, int posX, int posY, SDL_Color color, const std::string &fontFromFonts):
    color(color),
    colorBackBuffer(color),
    textRect({posX, posY,0, 0}){
    this->fontFromFonts = fontFromFonts;
    contentBackBuffer = this->content = content;
    font = TTF_OpenFont(("assets/fonts/" + fontFromFonts).c_str(), size);
    textSurface = TTF_RenderText_Solid(font, content.c_str(), color);
    textTexture = SDL_CreateTextureFromSurface(Window::getInstance()->getSDLRenderer(), textSurface);
    textRect.w = textSurface->w; textRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;
}

Text::~Text() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
}

void Text::update() {
    if(contentBackBuffer != content || colorBackBuffer!=color){
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;

        textSurface = TTF_RenderText_Solid(font, content.c_str(), {color.r, color.g, color.b, color.a});
        textTexture = SDL_CreateTextureFromSurface(Window::getInstance()->getSDLRenderer(), textSurface);

        SDL_FreeSurface(textSurface);
        textSurface = nullptr;

        contentBackBuffer = content;
        colorBackBuffer = color;
    }
}

void Text::render() {
    Window::getInstance()->drawTexture(textTexture, nullptr, &textRect);
}
