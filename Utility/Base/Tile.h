#pragma once

#include "Texture.h"
#include "../../Manager/Textures.h"
#include <iostream>
#include <vector>

/*! \class Tile
 *  \brief Klasa bazowa, będaca informacją o kafelku/najmniejszym elemencie mapy.*/
class Tile{
private:
    /*! \brief Statyczna wartość zawierająca informację o ostatnim zaistaniałym ID kafelka.*/
    static unsigned int lastTileID;
    /*! \struct Pos
 *  \brief Struktura zawierająca informacje o pozycji kafelka. */
    struct Pos {
        /*! \brief Wartość współrzędnej X na płaszczyźnie.*/
        int x = 0;
        /*! \brief Wartość współrzędnej Y na płaszczyźnie.*/
        int y = 0;
        Pos& operator=(const Pos& obj) = default;
        inline friend std::ostream& operator<<(std::ostream& scout, const Pos& obj){ scout << obj.x << ":" << obj.y; return scout; }
        Pos& operator+=(const Pos& obj) { x += obj.x; y += obj.y; return *this; }
        Pos& operator-=(const Pos& obj) { x -= obj.x; y -= obj.y; return *this; }
        explicit operator SDL_Point() const { return { x, y }; }
    };
    /*! \struct Size
 *  \brief Struktura zawierająca informacje o rozmiarze kafelka. */
    struct Size {
        /*! \brief Wartość szerokości na płaszczyźnie.*/
        int w = 0;
        /*! \brief Wartość wysokości na płaszczyźnie.*/
        int h = 0;
        Size& operator=(const Size& obj) = default;
        inline friend std::ostream& operator<<(std::ostream& scout, const Size& obj){ scout << obj.w << ":" << obj.h; return scout; }
    };
protected:
    /*! \brief Kontener sekwencyjny zawierający wartwy tekstur kafelka.*/
    std::vector<Texture*> texLayers;
    /*! \brief Wartość zawierająca informację o uruchomieniu trybu relatywnej pozycji.*/
    bool relativeMode;
public:
    /*! \brief Wartość zawierająca informację o ID obecnego kafelka*/
    const unsigned int tileID;
    /*! \brief Domyślny konstruktor.*/
    Tile();
    /*! \brief Kontruktor kopiujący.*/
    Tile(const Tile& tileObj);
    /*! \brief Wirtualny destruktor.*/
    virtual ~Tile();
    /*! \brief Instancja struktury zawierająca informacje o pozycji kafelka podczas początkowej inicjalizacji. */
    Pos constructPos;
    /*! \brief Instancja struktury zawierająca informacje o pozycji kafelka względem mapy. */
    Pos absolutePos;
    /*! \brief Instancja struktury zawierająca informacje o pozycji kafelka względem relatywnych punktów np. pola widzenia/kamery. */
    Pos relativePos;
    /*! \brief Instancja struktury zawierająca informacje o rozmiarze kafelka. */
    Size size;
    /*! \brief Wartość przechowująca informację, czy kafelek powinien kolidować. */
    bool collision;
    /*! \brief Wartość przechowująca informację, czy kafelek jest bytem. */
    bool entity;
    /*! \brief Wartość przechowująca informację, czy kafelek jest aktywny / powinien być renderowany. */
    bool active;
    /**
     * \brief Wirtualna metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    inline virtual bool handleEvent() { return true; };
    //void changeTexLayer(int idLayer, Texture* newTexture);
    /*! \brief Metoda dodająca nowa warstwę na stos tekstur. */
    void addTexLayer(Texture* newTexture);
    /*! \brief Wirtualna metoda zapewniająca aktualizowanie właściwości kafelka. */
    virtual void update();
    /*! \brief Wirtualna metoda zapewniająca renderowanie kafelka na obszarze widzialnym. */
    virtual void render();

    friend class Camera;
    friend class Entity;
    friend class Tiles;
};