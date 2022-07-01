#pragma once

#include "../../Utility/Base/Entity.h"

/*! \class Mag
 *  \brief Klasa reprezentująca pojedynczą instancje bytu / Maga. */
class Mag : public Entity{
public:
    /**
     * \brief Konstruktor.
     * \param xp Wartość startowego poziomu doświadczenia.
     * \param posX Pozycja startowa tesktury względem współrzędnej X
     * \param posY Pozycja startowa tesktury względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę Maga (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Mag(int xp, int posX, int posY, Texture* texture = nullptr);
    /*! \brief Domyślny desktuktor*/
    ~Mag() override = default;
    /*! \brief Metoda zapewniająca aktualizowanie właściwości Maga. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie Maga na obszarze widzialnym. */
    void render() override;
};


