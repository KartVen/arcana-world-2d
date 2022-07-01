#pragma once

#include <vector>
#include "../../Utility/Base/Text.h"
#include "../../Manager/Events.h"
#include "../../Utility/Base/Screen.h"

/*! \class PauseScreen
 *  \brief Klasa, będąca reprezentantem Menu wstrzymania Aplikacji.*/
class PauseScreen : public Screen {
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static PauseScreen* selfInstance;
    /*! \brief Wskaźnik do instancji klasy obsługującej zdarzenia.*/
    Events* eventsHandler;
    /*! \brief Instancja struktury SDL_Rect z biblioteki SDL2 zawierająca informacje o sferze menu. */
    SDL_Rect bgMenuRect;
    /*! \brief Wskaźnik do instancji klasy Text zawierający tekst tytułu gry*/
    Text *titleGame;
    /*! \brief Kontener sekwencyjny zawierający wskaźniki do pojedyńczych kafelków.*/
    std::vector<Text*> menuLabels;
    /*! \brief Tablica instancji struktury SDL_Color przechowująca informacje o danych kolorach.*/
    SDL_Color color[2];
    /*! \brief Wartość zawierająca informację o stanie klawisza jako executer.*/
    int keyState;
    /*! \brief Domyślny konstruktor.*/
    PauseScreen();
    /*! \brief Domyślny destruktor.*/
    ~PauseScreen();
public:
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static PauseScreen* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyScreen();
    /*! \brief Wartość zawierająca informację o stanie uruchomienia menu.*/
    bool running;
    /**
     * \brief Metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    bool handleEvents() override;
    /*! \brief Metoda zapewniająca aktualizowanie elementów właściwości menu. */
    void update() override;
    /*! \brief Metoda zapewniająca renderowanie elementów menu na obszarze widzialnym. */
    void render() override;
};


