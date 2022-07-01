#pragma once

#include <iostream>
#include "../Config.h"
#include "Texture.h"
#include "../../Manager/Textures.h"
#include "Tile.h"
#include "Text.h"

enum ROTATE { DOWN, LEFT, UP, RIGHT };

/*! \class Entity
 *  \brief Klasa pośrednia tworząca egzystencjalną wersję kafelka/najmniejszego elementu mapy. */
class Entity : public Tile{
    /*
    struct SquareEye {
        int posUL = 0;
        int posUR = Config::getInstance()->getValue("sizeTile");
        int posDL = 0;
        int posDR = Config::getInstance()->getValue("sizeTile");
        SquareEye& operator=(const Pos& entityPos) {
            posUL = entityPos.x - 1 * Config::getInstance()->getValue("sizeTile");
            posUR = entityPos.x + 1 * Config::getInstance()->getValue("sizeTile");
            posDL = entityPos.x - 1 * Config::getInstance()->getValue("sizeTile");
            posDR = entityPos.x + 1 * Config::getInstance()->getValue("sizeTile");
            return *this;
        }
    };*/
protected:
    /*! \brief Wskaźnik do instancji klasy konfiguracyjnej.*/
    Config* config;
public:
    /*! \brief Łańcuch znaków przechowujący nazwę bytu.*/
    std::string name;
    /*! \brief Wartość ilości poziomu doświadczenia bytu.*/
    int xp;
    /*! \brief Wartość ilości poziomu doświadczenia bytu w poprzednim buforowaniu.*/
    int xpBackBuffer;
    /*! \brief Wartość obecnego poziomu bytu.*/
    int lvl;
    /*! \brief Wartość poziomu bytu w poprzednim buforowaniu.*/
    int lvlBackBuffer;
    /*! \brief Wskaźnik do instancji klasy Text zawierająca tekst nagłówka bytu.*/
    Text* headText;
    /*! \brief Wartość szerokości tekstury bytu.*/
    int width;
    /*! \brief Wartość szerokości tekstury bytu.*/
    int height;
    /*! \brief Wartość liczbowa orientacji bytu.*/
    int rotate;
    /*! \brief Wartość liczbowa klatki animacji bytu.*/
    int animNexter;
    /*! \brief Wartość startowego maksymalnego poziomu zdrowia bytu.*/
    int startHpMax;
    /*! \brief Wartość obecnego maksymalnego poziomu zdrowia bytu.*/
    int hpMax;
    /*! \brief Wartość dodawanego maksymalnego zdrowia przy każdym poziomie.*/
    int hpMaxBooster;
    /*! \brief Wartość obecnego poziomu zdrowia bytu.*/
    int hp;
    /*! \brief Wartość obecnego poziomu zdrowia bytu poziomu w poprzednim buforowaniu.*/
    int hpBackBuffer;
    /*! \brief Wartość liczbowa startowego ataku pasywnego.*/
    int startAttackPassive;
    /*! \brief Wartość liczbowa obecnego ataku pasywnego.*/
    int attackPassive;
    /*! \brief Wartość liczbowa startowa obrony.*/
    int startDefense;
    /*! \brief Wartość liczbowa obecnej obrony.*/
    int defense;
    /*! \brief Wartość procentowa startowego ataku krytycznego.*/
    int startAttackCriticalPercent;
    /*! \brief Wartość procentowa obecnego ataku krytycznego.*/
    int attackCriticalPercent;
    /*! \brief Wartość określająca uruchomienie sztucznej inteligencji.*/
    bool ai;
    /*! \brief Wartość określająca stałe przemieszecznie bytu.*/
    int ENT_VELOCITY;
    /*! \brief Wartość liczbowa określająca zasięg poruszania sie bytu.*/
    int movementRange;
    /*! \brief Wartość liczbowa określająca zasięg widzenia sie bytu.*/
    int eyeRange;
    /*! \brief Wartość liczbowa określająca przesunięcie po współrzędniej X na płaszczyźnie.*/
    int entShiftX;
    /*! \brief Wartość liczbowa określająca przesunięcie po współrzędniej Y na płaszczyźnie.*/
    int entShiftY;
    /*! \brief Wartość liczbowa licznika przechwyconych aktywności konktretnej metody dla pojendyńczej klatki.*/
    int frameEvents;
    /*! \brief Wartość określająca, czy entity zostanie renderowane na obszarze widzialnym.*/
    bool active;
    /**
     * \brief Konstruktor.
     * \param name Nazwa bytu
     * \param posX Pozycja startowa bytu względem współrzędnej X
     * \param posY Pozycja startowa bytu względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę bytu (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Entity(const std::string& name, int posX, int posY, Texture* texture = nullptr);
    /*! \brief Destruktor*/
    ~Entity() override;
    /**
     * \brief Metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    inline bool handleEvent() override { return true; }
    /*! \brief Metoda zapewniająca aktualizowanie właściwości bytu. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie bytu na obszarze widzialnym. */
    void render() override;

    friend class Camera;
};


