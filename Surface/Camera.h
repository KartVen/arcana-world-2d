#pragma once

#include "../Window/Window.h"
#include "../Utility/Base/Entity.h"

/*! \class Camera
 *  \brief Klasa pośrednia tworząca egzystencjalną wersję kafelka/najmniejszego elementu mapy. */
class Camera {
private:
    struct PosCamera{
        int x, y;
        friend std::ostream& operator<<(std::ostream& scout, const PosCamera& obj){
            scout<<obj.x<<":"<<obj.y; return scout;
        }
    };
    /*! \brief Statyczny wskaźnik do własnej instancji klasy.*/
    static Camera* selfInstance;
    /*! \brief Domyślny konstruktor.*/
    Camera();
    /*! \brief Domyślny destruktor.*/
    ~Camera() = default;
    /*! \brief Wskaźnik do instancji klasy konfiguracyjnej.*/
    Config* config;
    /*! \brief Wskaźnik do instancji klasy reprezentującej okno aplikacji.*/
    Window* window;
    /*! \brief Instancja struktury SDL_Rect z biblioteki SDL2 reprezentującej okno aplikacji.*/
    SDL_Rect dstCameraRect;
    /*! \brief Wskaźnik do instancji klasy Entity reprezentującej przypiętego do kamery bytu.*/
    Entity* wrappedEntity;
    /*! \brief Instancja struktury zawierająca informacje o pozycji kamery wzgledem mapy. */
    PosCamera position;
public:
    /*! \brief Statyczna metoda inicjalizująca własną instancję.*/
    static void initCamera();
    /**
     * \brief Statyczna metoda zwracającą własną instancję.
     * \returns Wskaźnik do własnej instancji
     */
    static Camera* getInstance();
    /*! \brief Statyczna metoda usuwająca własną instancję.*/
    static void destroyCamera();
    /**
     * \brief Metoda ustawiająca byt, który zostaje podwycony przez kamerę.
     * \param entity Wskaźnik do konktretnego bytu, poprzez pośrednią klasę egzystencji
     */
    void setWrapEntity(Entity* entity);
    /**
     * \brief Metoda zwracająca o pozycji Kamery względem osi X na płaszczyźnie.
     * \returns Wartość zmiennej X struktury pozycji
     */
    inline int getPosX() const { return position.x; };
    /**
     * \brief Metoda zwracająca o pozycji Kamery względem osi Y na płaszczyźnie.
     * \returns Wartość zmiennej Y struktury pozycji
     */
    inline int getPosY() const { return position.y; };
    /*! \brief Wirtualna metoda zapewniająca aktualizowanie właściwości kamery. */
    void update();
    /*! \brief Wirtualna metoda zapewniająca renderowanie elementów przczepionych do kamery na obszarze widzialnym. */
    void render();
};


