#pragma once

#include <SDL_render.h>
#include "../../Window/Window.h"
#include <string>

/*! \class Texture
 *  \brief Klasa reprezentująca pojedynczą instancje tekstury. */
class Texture {
public:
    /*! \brief Wskaźnik do instancji klasy SDL_Texture z biblioteki SDL2.*/
    SDL_Texture* sdlTex;
    /*! \brief Łańcuch znaków przechowujący ściężkę do tekstury.*/
    std::string textureDstPath;
    /*! \brief Instancja struktury SDL_Rect z biblioteki SDL2 zawierająca informacje żródłowe tekstury. */
    SDL_Rect srcRectTex;
    /*! \brief Instancja struktury SDL_Rect z biblioteki SDL2 zawierająca informacje docelowe tekstury. */
    SDL_Rect dstRectTex;
    /*! \brief Wskaźnik do instancji klasy reprezentującej okno aplikacji.*/
    Window* windowInstance;
    /**
     * \brief Konstruktor.
     * \param texturePath Ścieżka do tekstury
     * \param srcWidth Źródłowa szerokość tekstury
     * \param srcHeight Źródłowa wysokość tekstury
     * \param dstWidth Docelowa szerokość tekstury
     * \param dstHeight Docelowa szerokość tekstury
     * \param posX Pozycja startowa tesktury względem współrzędnej X (domyślnie: 0)
     * \param posY Pozycja startowa tesktury względem współrzędnej Y (domyślnie: 0)
     */
    Texture(const std::string &texturePath, int srcWidth, int srcHeight, int dstWidth, int dstHeight, int posX = 0, int posY = 0);
    /*! \brief Konstruktor kopiujący.*/
    Texture(const Texture& texture);
    /*! \brief Domyślny destruktor.*/
    ~Texture();
    /*! \brief Metoda umożliwiająca zmianę obecnej textury.*/
    void changeTexture(const std::string &texturePath);
    /**
     * \brief Metoda umożliwiająca rendering obecnej textury.
     * \param posX Pozycja tesktury względem współrzędnej X (domyślnie: 0)
     * \param posY Pozycja tesktury względem współrzędnej Y (domyślnie: 0)
     */
    void drawTexture(int posX = 0, int posY = 0);
    /**
     * \brief Metoda umożliwiająca rendering obecnej textury.
     * \param dstRect Wskażnik do instancji struktury SDL_Rect z biblioteki SDL2 zawierającej informacje docelowego pozycji renderowania tesktury
     */
    void drawTexture(SDL_Rect *dstRect);
};


