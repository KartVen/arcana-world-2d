#pragma once

#include "../../Utility/Base/Entity.h"

/*! \class Cactuser
 *  \brief Klasa reprezentująca pojedynczą instancje bytu / Kaktusera. */
class Cactuser : public Entity{
public:
    /**
     * \brief Konstruktor.
     * \param xp Wartość startowego poziomu doświadczenia.
     * \param posX Pozycja startowa tesktury względem współrzędnej X
     * \param posY Pozycja startowa tesktury względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę Kaktusera (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Cactuser(int xp, int posX, int posY, Texture *texture = nullptr);
    /*! \brief Domyślny desktuktor*/
    ~Cactuser() override = default;
    /*! \brief Metoda zapewniająca aktualizowanie właściwości Kaktusera. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie Kaktusera na obszarze widzialnym. */
    void render() override;
};


