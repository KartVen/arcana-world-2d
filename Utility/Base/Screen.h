#pragma once

/*! \class Screen
 *  \brief Klasa bazowa, będaca informacją o Ekranie.*/
class Screen {
public:
    bool running = false;
    /**
     * \brief Metoda zapewniająca przechwytywanie / obsługę zdarzeń.
     * \returns TRUE jeśli zdarzenia zostały obsłużone poprawnie, FALSE jeśli nie
     */
    virtual bool handleEvents() = 0;
    /*! \brief Wirtualna metoda zapewniająca aktualizowanie elementów właściwości menu. */
    virtual void update() = 0;
    /*! \brief Wirtualna metoda zapewniająca renderowanie elementów menu na obszarze widzialnym. */
    virtual void render() = 0;
};