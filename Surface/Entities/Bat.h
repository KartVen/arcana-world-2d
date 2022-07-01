#pragma once

#include "../../Utility/Base/Entity.h"

/*! \class Bat
 *  \brief Klasa reprezentująca pojedynczą instancje bytu / Nietoperza. */
class Bat : public Entity {
public:
    /**
     * \brief Konstruktor.
     * \param xp Wartość startowego poziomu doświadczenia.
     * \param posX Pozycja startowa tesktury względem współrzędnej X
     * \param posY Pozycja startowa tesktury względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę Nietoperza (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Bat(int xp, int posX, int posY, Texture* texture = nullptr);
    /*! \brief Domyślny desktuktor*/
    ~Bat() override = default;
    /*! \brief Metoda zapewniająca aktualizowanie właściwości Nietoperza. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie Nietoperza na obszarze widzialnym. */
    void render() override;
};


