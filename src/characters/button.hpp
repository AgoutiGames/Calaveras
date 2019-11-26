#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "core/game_character.hpp"

class GameScene;

class Button : public GameCharacter {
    public:
        Button(salmon::ActorRef actor, GameScene* scene);
        virtual Button* create(salmon::ActorRef actor, GameScene* scene) const override {return new Button(actor,scene);}

        void init() override;
        void update() override;

        static const char* type;
    protected:
        // Add members here
        std::string m_id;
        std::string m_sound;

    private:
        static const bool good;
};


#endif // BUTTON_HPP_INCLUDED
