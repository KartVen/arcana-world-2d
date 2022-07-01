#pragma once

#include <vector>
#include <ostream>
#include "../Utility/Config.h"
#include "Camera.h"
#include "Entities/Player.h"
#include "Maps/Map.h"
#include "Screens/PauseScreen.h"
#include "Screens/OverScreen.h"
#include <iostream>

/*! \class Surface
 *  \brief Klasa, będąca reprezentantem całej przestrzeni/świata Aplikacji.*/
class Surface {
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Surface* selfInstance;
    /*! \brief Domyślny konstruktor.*/
    Surface();
    /*! \brief Domyślny destruktor.*/
    ~Surface();
    /*! \brief Wskaźnik do instancji klasy obsługującej zdarzenia.*/
    Events* eventsHandler;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Menu pauzy aplikacji.*/
    PauseScreen* pauseScreen;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Menu końcowe aplikacji.*/
    OverScreen* overScreen;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Kamerę.*/
    Camera* camera;
    /*! \brief Wskaźnik do instancji klasy reprezentującej pojedyńczego gracza.*/
    Player* player;
    /*! \brief Wskaźnik do instancji klasy reprezentującej pojedyńczą mapę.*/
    Map* map1;
    /*! \brief Wskaźnik do instancji klasy reprezentującej pojedyńczą scenę przestrzeni/świata.*/
    Scene* sceneManager1;
    /*! \brief Wartość zawierająca informację, czy zrestarować scenę.*/
    bool restart;
public:
    /**
     * \brief Statyczna metoda inicjalizująca i zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Surface* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroySurface();
    /**
     * \brief Metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    bool handleEvents();
     /** \brief Metoda zapewniająca losowanie bytów i dodawanie ich do przestrzeni/świata.
     * \param tiles Wskażnik na menedżer kafelków zarządającym sceną.
     * \param mode Tryb losowania
     */
    void randAndAddEntity(Tiles *tiles, int mode);
    /*! \brief Metoda zapewniająca aktualizowanie właściwości elementów przestrzeni/świata. */
    void update();
    /*! \brief Metoda zapewniająca renderowanie elementów przestrzeni/świata na obszarze widzialnym. */
    void render();
};
