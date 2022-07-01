#pragma once

#include "../../Utility/Base/Entity.h"
#include "../../Utility/Base/Texture.h"

/*! \class Spider
 *  \brief Klasa reprezentująca pojedynczą instancje bytu / Pająka. */
class Spider : public Entity{
public:
    /**
     * \brief Konstruktor.
     * \param xp Wartość startowego poziomu doświadczenia.
     * \param posX Pozycja startowa tesktury względem współrzędnej X
     * \param posY Pozycja startowa tesktury względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę Pająka (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Spider(int xp, int posX, int posY, Texture* texture = nullptr);
    /*! \brief Domyślny desktuktor*/
    ~Spider() override = default;
    /*! \brief Metoda zapewniająca aktualizowanie właściwości Pająka. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie Pająka na obszarze widzialnym. */
    void render() override;
};