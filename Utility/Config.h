#pragma once

#include <string>
#include <map>
#include <vector>

/*! \class Config
 *  \brief Klasa konfiguracyjna Aplikacji. */
class Config {
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Config* selfInstance;
    /*! \brief Domyślny konstruktor.*/
    Config();
    /*! \brief Domyślny destruktor.*/
    ~Config();
    /*! \brief Kontener asocjacyjny zawierający podstawowe konfiguracje i ustawienia.*/
    std::map<std::string, int> config;
    /*! \brief Wartość zawierająca informację o poprawności załadowanej z pliku konfiguracji.*/
    bool correctlyLoaded;
    /*! \brief Wartość zawierająca informację, czy odczytać/zapisać plik konfiguracji.*/
    bool fileAccess;
public:
    /*! \brief Statyczna metoda inicjalizująca własną instancję.*/
    static void initConfig();
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Config* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyConfig();
    /**
     * \brief Metoda infomująca o poprawności kluczy konfiguracyjnych i ich wartości.
     * \returns 1 jeśli dane są poprawne, 0 gdy dane są niepoprawne
     */
    inline bool isCorrect() const { return correctlyLoaded; };
    /**
     * \brief Metoda informacyjna o wartościach kluczy konfiguracyjnych.
     * \param key Klucz konfiguracyjny
     * \returns Wartość spod klucza konfiguracyjnego.
     */
    inline int getValue(const std::string& key) const { return config.at(key); };
    /*! \brief Kontener sekwencyjny zawierający podstawową konfigurację poziomów.*/
    std::vector<int> lvlXpTable{0};
};


