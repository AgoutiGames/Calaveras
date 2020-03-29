#ifndef CLOUD_HPP_INCLUDED
#define CLOUD_HPP_INCLUDED

#include "core/game_character.hpp"

class GameScene;

class Cloud : public GameCharacter {
    public:
        Cloud(salmon::ActorRef actor, GameScene* scene);
        virtual Cloud* create(salmon::ActorRef actor, GameScene* scene) const override {return new Cloud(actor,scene);}

        void init() override;
        void update() override;
        std::string get_type() const override {return type;}

        static const char* type;
    protected:
        // Add members here
        float m_speed = 1.0f;

    private:
        static const bool good;
};


#endif // CLOUD_HPP_INCLUDED
