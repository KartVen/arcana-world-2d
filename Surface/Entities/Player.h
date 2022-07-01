#pragma once

#include "../../Utility/Base/Entity.h"
#include "../../Manager/Events.h"
#include "../../Manager/Tiles.h"

class Player : public Entity{
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Player* selfInstance;
    /**
     * \brief Konstruktor.
     * \param name Nazwa gracza
     * \param posX Pozycja startowa bytu względem współrzędnej X
     * \param posY Pozycja startowa bytu względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę bytu (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    Player(const char* name, int posX, int posY, Texture* texture = nullptr);
    /*! \brief Domyślny desktuktor*/
    ~Player() override = default;
    /*! \brief Wskaźnik do instancji klasy obsługującej zdarzenia.*/
    Events* events;
    /*! \brief Wskaźnik do instancji klasy reprezentującej menedżer kafelków.*/
    Tiles* tilesManager;
    /*! Wartość liczbowa określająca przesunięcie po współrzędniej X na płaszczyźnie.*/
    int shiftPosX;
    /*! Wartość liczbowa określająca przesunięcie po współrzędniej Y na płaszczyźnie.*/
    int shiftPosY;
    /*! Wartość określająca stałe przemieszecznie gracza.*/
    const int VELOCITY;
public:
     /* \brief Statyczna metoda inicjalizująca własną instancję.
     * \param name Nazwa gracza
     * \param posX Pozycja startowa bytu względem współrzędnej X
     * \param posY Pozycja startowa bytu względem współrzędnej Y
     * \param texture Wskaźnik do instancji klasy Texture reprezentującej teksturę bytu (domyślnie: wskaźnik nullptr przeszktałcany na "default_default.png")
     */
    static void initPlayer(const char* name, int posX, int posY, Texture* texture = nullptr);
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Player* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyPlayer();
    /*! \brief Metoda resetująca statystyki gracza.*/
    void reset();
    /*! \brief Metoda ustawiająca odpowiedni menedźer kafelków do wskaźnika.
     * \param tilesManager Menedźer kafelków / Scena
     * */
    void setTilesManager(Tiles *tilesManager);
    /**
     * \brief Metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    bool handleEvent() override;
    /*! \brief Metoda zapewniająca aktualizowanie właściwości Gracza. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie Gracza na obszarze widzialnym. */
    void render() override;
};


