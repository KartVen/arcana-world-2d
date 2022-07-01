#pragma once

#include <SDL_events.h>
#include <iostream>

/*! \class Events
 *  \brief Klasa reprezentująca obsługę wszystkich zdarzeń Aplikacji.*/
class Events {
private:
    /*! \struct WinKey
 *  \brief Struktura zawierająca informacje o przyciskach głównych okna. */
    struct WinKey{
        bool MINIMALIZE = false;
        bool QUIT = false;
    };
    /*! \struct KeyState
     * \brief Struktura zawierająca informacje pojedyńczego przycisku. */
    struct KeyState {
            bool down = false;
            bool up = true;
            bool isClicked = false;
            bool wasClicked = false;
            bool lockMode = false;
        private:
            bool clickedStamper = false;
        public:
            explicit KeyState(bool lockMode = false){
                this->lockMode = lockMode;
            }
            inline KeyState &operator=(bool state) {
                if(lockMode && !state && clickedStamper){
                    state = !state;
                }
                down = state; up = !state;
                wasClicked = isClicked; isClicked = state; clickedStamper = state;
                return *this;
            }
            void set(){ clickedStamper = true; }
            void reset(){ clickedStamper = false; }
    };
    /*! \struct Key
     * \brief Struktura zawierająca informacje o przyciskach. */
    struct Key{
        KeyState ESCAPE{true}, SPACE{true};
        KeyState w, a, s, d;
        KeyState UP, LEFT, DOWN, RIGHT;
    };
    /*! \struct Position
     * \brief Struktura zawierająca informacje o pozycji. */
    struct Position{
        int x = 0, y = 0;
        Position& operator=(SDL_MouseMotionEvent& obj){
            x = obj.x; y = obj.y; return *this;
        }
    };
    /*! \struct Mouse
     * \brief Struktura zawierająca informacje o pozycji i przyciskach myszy. */
    struct Mouse{
        Position position;
        KeyState btnLeft, btnMiddle, btnRight;
    };
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Events* selfInstance;
    /*! \brief Domyślny konstruktor.*/
    Events() = default;
    /*! \brief Domyślny destruktor.*/
    ~Events() = default;
    /*! \brief Instancja struktury zawierającej przyciski główne okna*/
    WinKey winKey;
public:
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Events* getEvents();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyEvents();
    /*! \brief Instancja struktury zawierającej eventy okna z biblioteki SDL2*/
    SDL_Event sdlEvent{};
    /*! \brief Metoda aktulizująca stany przycisków.*/
    void updateKeyState();
    /*! \brief Instancja struktury zawierającej informacje o myszy*/
    Mouse mouse;
    /*! \brief Instancja struktury zawierającej informacjeo przyciskach*/
    Key key;
    /**
     * \brief Metoda informująca, czy klawisz Zakmnij inicjalizuje wyłączenie aplikacji.
     * \returns TRUE jeśli powinno wyjść, FALSE jeśli nie
     */
    inline bool isQUIT() const { return winKey.QUIT; };
};


