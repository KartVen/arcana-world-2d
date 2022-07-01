#pragma once

#include "Window/Window.h"
#include "Manager/Events.h"
#include "Surface/Surface.h"
#include "Surface/Screens/StartScreen.h"

/*! \class App
 *  \brief Główna klasa Aplikacji typu Singleton. */
class App{
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static App* selfInstance;
    /*! \brief Domyślny konstruktor.*/
    App();
    /*! \brief Domyślny destruktor.*/
    ~App();
    /*! \brief Wskaźnik do instancji klasy reprezentującej okno aplikacji.*/
    Window* windowInstance;
    /*! \brief Wskaźnik do instancji klasy obsługującej zdarzenia.*/
    Events* eventsHandler;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Menu startowe aplikacji.*/
    StartScreen* startScreen;
    /*! \brief Wartość przechowująca informację, czy aplikacja powinna zostać zatrzymana.*/
    bool appQuit;
    /*! \brief Wskaźnik do instancji klasy reprezentującej Przestrzeń/Świat gry.*/
    Surface* surfaceGame;
public:
    /**
     * \brief Statyczna metoda inicjalizująca i zwracająca własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static App* getApp();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyApp();
    /*! \brief Metoda zapewniająca działanie aplikacji.*/
    void runningApp();
    /**
     * \brief Metoda zapewniająca przechwytywanie zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    bool handleEvent();
    /*! \brief Metoda zapewniająca aktualizowanie elementów obszaru widzialnego aplikacji.*/
    void update();
    /*! \brief Metoda zapewniająca renderowanie elementów na obszarze widzialnym aplikacji.*/
    void render();
};

