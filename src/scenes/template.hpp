#ifndef TEMPLATE_HPP_INCLUDED
#define TEMPLATE_HPP_INCLUDED

#include "core/game_scene.hpp"

class SceneManager;

class Template : public GameScene {
    public:
        Template(salmon::MapRef map, SceneManager* scene_manager);
        Template* create(salmon::MapRef map, SceneManager* scene_manager) const override {return new Template(map,scene_manager);}

        void init() override;
        void update() override;

        static const char* type;
    protected:
        // Add members here
        
    private:
        static const bool good;
};

#endif // TEMPLATE_HPP_INCLUDED
