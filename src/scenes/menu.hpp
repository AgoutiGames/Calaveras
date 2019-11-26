#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <string>

#include "core/game_scene.hpp"

class SceneManager;

class Menu : public GameScene {
    public:
        Menu(salmon::MapRef map, SceneManager* scene_manager);
        Menu* create(salmon::MapRef map, SceneManager* scene_manager) const override {return new Menu(map,scene_manager);}

        void init() override;
        void update() override;

        void button_pressed(std::string id);

        static const char* type;
    protected:
        // Add members here

    private:
        static const bool good;
};

#endif // MENU_HPP_INCLUDED
