#ifndef JUMP_STAGE_HPP_INCLUDED
#define JUMP_STAGE_HPP_INCLUDED

#include "core/game_scene.hpp"

class SceneManager;

class JumpStage : public GameScene {
    public:
        JumpStage(salmon::MapRef map, SceneManager* scene_manager);
        JumpStage* create(salmon::MapRef map, SceneManager* scene_manager) const override {return new JumpStage(map,scene_manager);}

        void init() override;
        void update() override;

        static const char* type;
    protected:
        // Add members here
        
    private:
        static const bool good;
};

#endif // JUMP_STAGE_HPP_INCLUDED
