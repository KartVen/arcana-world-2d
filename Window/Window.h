#pragma once

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/*! \class Window
 *  \brief Klasa, będąca reprezentantem Okna Aplikacji.*/
class Window {
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Window* selfInstance;
    /*! \brief Wskaźnik do instancji klasy SDL_Window z biblioteki SDL2 określającej okno.*/
    SDL_Window* objWindow;
    /*! \brief Wskaźnik do instancji klasy SDL_Renderer z biblioteki SDL2 określającej obszar widzialny.*/
    SDL_Renderer* objRenderer;
    /**
     * \brief Metoda tworząca okno.
     * \returns TRUE jeśli wszystko przebiegło pomyślnie, FALSE jeśli nie
     */
    bool createWindow();
    /*! \brief Wartośc określająca, czy okno jest uruchomione */
    bool running;
    /*! \brief Domyślny konstruktor.*/
    Window();
    /*! \brief Domyślny destruktor.*/
    ~Window();
public:
    /*! \brief Statyczna wartośc rozmiaru szerokości okna.*/
    static int WINDOW_WIDTH;
    /*! \brief Statyczna wartośc rozmiaru wysokości okna.*/
    static int WINDOW_HEIGHT;
    /*! \brief Statyczna metoda inicjalizująca własną instancję.*/
    static void initWindow();
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Window* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyWindow();
    /**
     * \brief Metoda informująca o stanie uruchomienia okna.
     * \returns TRUE jeśli uruchamianie przebiegło pomyślnie, FALSE jeśli nie
     */
    inline bool isRunning() const { return running; };
    /**
     * \brief Metoda renderująca teksturę na obszarze widzialnym.
     * \param objTexture Wskaźnik do instancji klasy Texture reprezentującej teksturę do renderowania
     * \param srcRect Wskażnik do instancji struktury SDL_Rect z biblioteki SDL2 zawierającej informacje źródłowe renderowanej tesktury
     * \param dstRect Wskażnik do instancji struktury SDL_Rect z biblioteki SDL2 zawierającej informacje docelowe renderowanej tesktury
     */
    void drawTexture(SDL_Texture* objTexture, SDL_Rect* srcRect, SDL_Rect* dstRect);
    /** \brief Metoda zwracająca SDL_Renderer z biblioteki SDL2
     * \returns Wskaźnik do instancji klasy SDL_Renderer
     * */
    inline SDL_Renderer* getSDLRenderer() const { return objRenderer; };
    /** \brief Metoda zwracająca SDL_Window z biblioteki SDL2
     * \returns Wskaźnik do instancji klasy SDL_Window
     * */
    inline SDL_Window* getSDLWindow() const { return objWindow; };
    /*! \brief Metoda zapewniająca aktualizowanie właściwości elementów przestrzeni/świata aplikacji. */
    bool updateSurface();
};


