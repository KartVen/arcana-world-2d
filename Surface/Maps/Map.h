#pragma once

#include <vector>
#include "../../Utility/Base/Tile.h"
#include "../../Utility/Config.h"

class Map{
private:
    /*! \brief Wskaźnik do instancji klasy konfiguracyjnej.*/
    Config* config;
    /*! \brief Kontener sekwencyjny 2D zawierający wskaźniki do pojedyńczych kafelków.*/
    std::vector<std::vector<Tile*>> map;
public:
    /**
     * \brief Konstruktor.
     * \param levelMapPath Ścieżka do pliku mapy
     * \param delimChar Separator bitów mapy (domyślnie: ',')
     */
    explicit Map(const std::string& levelMapPath, char delimChar = ',');
    /*! \brief Konstruktor kopiujący */
    Map(const Map &map);
    /*! \brief Domyślny destruktor */
    ~Map();
    /**
     * \brief Metoda ładująca mapę ze ścieżki.
     * \param levelMapPath Ścieżka do pliku mapy
     * \param delimChar Separator bitów mapy (domyślnie: ',')
     */
    void loadNewMapFromPath(const std::string& levelMapPath, char delimChar = ',');
    /**
     * \brief Metoda aktualizowania mapy po zakresach ID dla X i Y.
     * \param startIdX Startowy ID kafelka względem osi X;
     * \param startIdY Startowy ID kafelka względem osi Y;
     * \param stopIdX Końcowy ID kafelka względem osi X;
     * \param stopIdY Końcowy ID kafelka względem osi Y;
     */
    void update(unsigned int startIdX = 0, unsigned int startIdY = 0, unsigned int stopIdX = 0, unsigned int stopIdY = 0);

    friend class Tiles;
};
