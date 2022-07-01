#pragma once

#include <SDL_ttf.h>
#include <string>

class Text {
private:
    /*! \struct Text_Color
 *  \brief Struktura zawierająca informacje o kolorze tekstu. */
    struct Text_Color{
        /*! \brief Wartość wypełnienia kolorem czerwonym (0 - 255) */
        Uint8 r;
        /*! \brief Wartość wypełnienia kolorem zielonym (0 - 255) */
        Uint8 g;
        /*! \brief Wartość wypełnienia kolorem niebieskich (0 - 255) */
        Uint8 b;
        /*! \brief Wartość wypełnienia kolorem czerwonym (0 - 255) */
        Uint8 a;
        explicit Text_Color(SDL_Color color) {
            this->r = color.r; this->g = color.g; this->b = color.b; this->a = color.a;
        }
        Text_Color& operator=(const SDL_Color& obj) {
            this->r = obj.r; this->g = obj.g; this->b = obj.b; this->a = obj.a; return *this;
        }
        Text_Color& operator=(const Text_Color& obj) {
            if(this == &obj) return *this;
            this->r = obj.r; this->g = obj.g; this->b = obj.b; this->a = obj.a; return *this;
        }
        bool operator==(const Text_Color& obj) const {
            return (r == obj.r) && (g == obj.g) && (b == obj.b) && (a == obj.a);
        }
        bool operator!=(const Text_Color &obj) const {
            return !(*this == obj);
        }
    };
    /*! \brief Łańcuch znaków przechowujący nazwę pliku czcionki.*/
    std::string fontFromFonts;
    /*! \brief Łańcuch znaków przechowujący treść tekstu w poprzednim buforowaniu.*/
    std::string contentBackBuffer;
    /*! \brief Wskaźnik do instancji klasy TTF_Font (SDL_ttf.h).*/
    TTF_Font* font;
    /*! \brief Wskaźnik do instancji klasy SDL_Surface z biblioteki SDL2 reprezentującej przestrzeń zawierający tekst.*/
    SDL_Surface* textSurface;
    /*! \brief Wskaźnik do instancji klasy SDL_Texture z biblioteki SDL2 reprezentującej teksturę wypełnioną tekstem.*/
    SDL_Texture* textTexture;
    /*! \brief Instancja struktury Text_Color przechowująca informacje o kolorze tekstu w poprzednim buforowaniu.*/
    Text_Color colorBackBuffer;
public:
    /*! \brief Instancja struktury Text_Color przechowująca informacje o obecnym kolorze tekstu.*/
    Text_Color color;
    /*! \brief Instancja struktury SDL_Rect z biblioteki SDL2 zawierająca informacje o tekście na płaszczyźnie. */
    SDL_Rect textRect;
    /*! \brief Łańcuch znaków przechowujący treść tekstu.*/
    std::string content;
    /**
     * \brief Konstruktor.
     * \param content Treść tekstu
     * \param size Rozmiar tekstu
     * \param posX Pozycja startowa tekstu względem współrzędnej X
     * \param posY Pozycja startowa tekstu względem współrzędnej Y
     * \param r Wartość wypełnienia kolorem czerwonym (0 - 255)
     * \param g Wartość wypełnienia kolorem zielonym (0 - 255)
     * \param b Wartość wypełnienia kolorem niebieskim (0 - 255)
     * \param a Wartość wypełnienia kanałem alpha (0 - 255)
     * \param fontFromFonts Łańcuch znaków przechowujący nazwę pliku czcionki (domyślnie: "comic.ttf")
     */
    Text(const std::string& content, int size, int posX, int posY, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const std::string& fontFromFonts = "comic.ttf");
    /**
     * \brief Konstruktor.
     * \param content Treść tekstu
     * \param size Rozmiar tekstu
     * \param posX Pozycja startowa tekstu względem współrzędnej X
     * \param posY Pozycja startowa tekstu względem współrzędnej Y
     * \param color Struktura zawierająca informacje o wypełnieniu r, g, b, a i wypełnienia kanałem alpha
     * \param fontFromFonts Łańcuch znaków przechowujący nazwę pliku czcionki (domyślnie: "comic.ttf")
     */
    Text(const std::string& content, int size, int posX, int posY, SDL_Color color, const std::string& fontFromFonts = "comic.ttf");
    /*! \brief Domyślny destruktor */
    ~Text();
    /*! \brief Wirtualna metoda zapewniająca aktualizowanie właściwości kafelka. */
    void update();
    /*! \brief Wirtualna metoda zapewniająca renderowanie kafelka na obszarze widzialnym. */
    void render();
};


