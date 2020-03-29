#ifndef GAME_CHARACTER_HPP_INCLUDED
#define GAME_CHARACTER_HPP_INCLUDED

#include <map>
#include <string>

#include "actor_ref.hpp"

class GameScene;

/**
 * @brief The base class of a game character
 *
 * Each actor has to have a "type" property assigned in tiled which matches at least one of
 * the type strings of a child class of GameCharacter.
 *
 * @note Generate a proper child class quick and easy by launching "generate_new_character.py"
 *       and supplying the name of the class in PascalCase
 */
class GameCharacter : public salmon::ActorRef {
    public:
        GameCharacter(salmon::ActorRef actor, GameScene* scene);

        /**
         * @brief Creates a GameCharacter from an ActorRef
         * @return a parsed GameCharacter pointer if there was a child class with a type string
         *         that matched the "type" string property of the ActorRef
         */
        static GameCharacter* parse_character(salmon::ActorRef actor, GameScene* scene);

        /// Creates GameCharacter of distinct child type. Needed for constructing by matching type string.
        virtual GameCharacter* create(salmon::ActorRef actor, GameScene* scene) const = 0;

        /// Initializes the character. Add your custom initialization stuff here.
        virtual void init() = 0;
        /// Updates the character. Add game logic here.
        virtual void update() = 0;

        /// If a property with matching name and type exists, overwrite var with its value, otherwise don't touch var at all
        bool put(bool& var, std::string name);
        bool put(int& var, std::string name);
        bool put(float& var, std::string name);
        bool put(std::string& var, std::string name);

        /// Return true if currently suspended from updates
        bool suspended() {return m_suspended;}
        /// Suspend character from updating
        void suspend() {m_suspended = true;}
        /// Reenables updating actor per frame
        void unsuspend() {m_suspended = false;}

        /// Returns the name of the GameCharacter child class
        std::string virtual get_type() const = 0;
        static const char* type_string;

    protected:
        GameScene* m_scene;

        template <class T>
        static bool register_class(std::string type);
    private:
        bool m_suspended = false;
        static std::map<std::string, GameCharacter*>& get_dict();
};

template <class T>
bool GameCharacter::register_class(std::string type) {
    ActorRef dummy(nullptr);
    GameCharacter* character = new T(dummy,nullptr);
    get_dict()[type] = character;
    return true;
}

#endif // GAME_CHARACTER_HPP_INCLUDED
