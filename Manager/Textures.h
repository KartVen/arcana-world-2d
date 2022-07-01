#pragma once

#include "../Utility/Base/Texture.h"

/*! \class Textures
 *  \brief Klasa będąca menedżerem tekstur w aplikacji.*/
class Textures {
private:
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Textures* selfInstance;
    /*! \brief Domyślny konstruktor.*/\
    Textures();
    /*! \brief Domyślny destruktor.*/
    ~Textures();
public:
    /*! \brief Statyczna metoda inicjalizująca własną instancję.*/
    static void initTextures();
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Textures* getTextures();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyTextures();
    Texture
        *default_default;
    Texture
        *entity_player,
        *entity_spider_0,
        *entity_mag_0,
        *entity_cactuser_0,
        *entity_bat_0;
    Texture
        *map_bush_red,
        *map_bush,
        *map_gold,
        *map_grass_0,
        *map_grass_1,
        *map_grass_2,
        *map_grass_3,
        *map_stone,
        *map_tree_0,
        *map_windmill,
        *map_dirt,
        *map_water_0,
        *map_water_1,
        *map_water_2,
        *map_flower_0;
};

