#ifndef GAME_SCENE_HPP_INCLUDED
#define GAME_SCENE_HPP_INCLUDED

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "map_ref.hpp"
#include "audio_manager_ref.hpp"
#include "input_cache_ref.hpp"
#include "core/game_character.hpp"

class SceneManager;

/**
 * @brief The base class of a game scene
 *
 * Wraps ActorRefs into Characters whily supplying many getters for them.
 * By overloading init and update you get your custom game code to run.
 *
 * Each map has to have a "type" property assigned in tiled which matches at least one of
 * the type strings of a child class of GameScene.
 *
 * @note Generate a proper child class quick and easy by launching "generate_new_scene.py"
 *       and supplying the name of the class in PascalCase
 */
class GameScene : public salmon::MapRef {
    public:
        friend class SceneManager;

        GameScene(salmon::MapRef map, SceneManager* scene_manager);

        /**
         * @brief Creates a scene from a MapRef
         * @return a parsed GameScene pointer if there was a GameScene child with a type string
         *         that matched the "type" string property of the map
         */
        static GameScene* parse_scene(salmon::MapRef map, SceneManager* scene_manager);
        /// Creates GameScene of distinct child type. Needed for constructing by matching type string.
        virtual GameScene* create(salmon::MapRef map, SceneManager* scene_manager) const = 0;

        /// Initializes the scene. Make sure to call this base class init inside of the overriding child init function.
        virtual void init();
        /// Updates the scene. Make sure to call this base class init inside of the overriding child init function.
        virtual void update();


        /// If a property with matching name and type exists, overwrite var with its value, otherwise don't touch var at all
        bool put(bool& var, std::string name);
        bool put(int& var, std::string name);
        bool put(float& var, std::string name);
        bool put(std::string& var, std::string name);

        /// Returns true if the character resides in this scene
        bool is_valid(GameCharacter* character) const;

        /**
         * @brief Create a GameCharacter from an ActorRef and add to scene
         * @param actor The ActorRef which is used as a base for the GameCharacter
         * @return Nullptr if there is no GameCharacter child class whose type string is matching the type property of the actor
         *         otherwise just return the properly parsed GameCharacter pointer
         */
        GameCharacter* add_character(salmon::ActorRef actor);

        /**
         * @brief Create a GameCharacter from an actor template and add to scene
         * @param actor_template_name The name of the actor template which is used to create the actor
         * @return Nullptr if there is no matching actor template name, or if the layer doesn't exist or
         *         if there is no GameCharacter child class whose type string is matching the type property of the actor
         *         otherwise just return the properly parsed GameCharacter pointer
         */
        GameCharacter* add_character(std::string actor_template_name, std::string layer_name, std::string actor_name = "GENERATED");
        GameCharacter* add_character(const char* actor_template_name, std::string layer_name, std::string actor_name = "GENERATED")
        {return add_character(std::string(actor_template_name),layer_name,actor_name);}

        /**
         * @brief Create a GameCharacter from an already existing GameCharacter
         * @param character Pointer to the character to be duplicated
         * @return Nullptr if there is no matching actor template name, or if the layer doesn't exist
         *         otherwise just return the properly parsed GameCharacter pointer
         * @note Preserves members of the base ActorRef including position, scale and rotation.
         * @warning Doesn't preserve the members inside the GameCharacter child class!
         */
        GameCharacter* add_character(GameCharacter* character, std::string layer_name, std::string actor_name = "GENERATED");

        /**
         * @brief Create a GameCharacter from an already existing GameCharacter
         * @param character Pointer to the character to be duplicated
         * @return Nullptr if there is no matching actor template name, or if the layer doesn't exist
         *         otherwise just return the properly parsed GameCharacter pointer
         * @note Preserves all members of the copied GameCharacter
         */
        template <class T>
        GameCharacter* add_character(T* character, std::string layer_name, std::string actor_name = "GENERATED");

        /// Removes the supplied character from scene next frame. Safe to call even on dangling pointers but spits out a warning in log
        void remove_character(GameCharacter* game_character);

        // Instead of exposing scene manager we forward the only 4 functions safe to call from inside update

        /// Returns reference to input cache, holding information about keypresses, mouse state and gamepad state
        salmon::InputCacheRef get_input_cache();
        /// Return reference to the audio manager object of the game
        salmon::AudioManagerRef get_audio_manager();
        /// Shuts down the game in next frame
        void shutdown_game();
        /**
         * @brief Changes to this scene in next frame
         * @param relative path to next map/ .tmx file
         * @note The path is always relative to the directory of the currently loaded map
         */
        void next_scene(std::string map_filename);

        /// Returns the name of the game_scene child class
        std::string virtual get_type() const = 0;

        /// Returns a vector of pointers to all characters in this scene
        std::vector<GameCharacter*> get_characters();

        /// Returns character/s with matching name value
        GameCharacter* get_character_by_name(std::string name);
        std::vector<GameCharacter*> get_characters_by_name(std::string name);
        std::vector<GameCharacter*> filter_characters_by_name(std::vector<GameCharacter*> characters, std::string name);

        /// Returns character with a matching id. Nullptr if none found.
        GameCharacter* get_character_by_id(unsigned id);

        /// Returns characters which reside in the layer with the supplied name
        std::vector<GameCharacter*> get_characters_by_layer(std::string name);
        std::vector<GameCharacter*> filter_characters_by_layer(std::vector<GameCharacter*> characters, std::string name);

        /// Returns character/s of the supplied type. Same as get_character template method.
        GameCharacter* get_character_by_type(std::string type);
        std::vector<GameCharacter*> get_characters_by_type(std::string type);
        std::vector<GameCharacter*> filter_characters_by_type(std::vector<GameCharacter*> characters, std::string template_type);

        /// Returns character/s whose template name (ACTOR_NAME field inside Tiled) matches the supplied string.
        GameCharacter* get_character_by_template_name(std::string template_name);
        std::vector<GameCharacter*> get_characters_by_template_name(std::string template_name);
        std::vector<GameCharacter*> filter_characters_by_template_name(std::vector<GameCharacter*> characters, std::string template_name);

        /// Return character/s which match the supplied class/template parameter
        template <class T>
        T* get_character();
        template <class T>
        std::vector<T*> get_characters();
        template <class T>
        std::vector<T*> filter_characters(std::vector<GameCharacter*>);

        /// @warning the "by_attribute" character getters are only safe to call before calling "init" because
        ///          that calls init on each character which usually there get rid off their unsafe attribute values
        ///          and also saving space by that.

        /// Return the first character with a property of "name" and "attribute" value
        GameCharacter* get_character_by_attribute(std::string name, bool attribute);
        GameCharacter* get_character_by_attribute(std::string name, int attribute);
        GameCharacter* get_character_by_attribute(std::string name, float attribute);
        GameCharacter* get_character_by_attribute(std::string name, const char* attribute);
        GameCharacter* get_character_by_attribute(std::string name, std::string attribute);

        /// Return all characters with a property of "name" and "attribute" value
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, bool attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, int attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, float attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, const char* attribute);
        std::vector<GameCharacter*> get_characters_by_attribute(std::string name, std::string attribute);

        /// Return new character pointer vector only with matching property "name" and "attribute" value
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, bool attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, int attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, float attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, const char* attribute);
        std::vector<GameCharacter*> filter_characters_by_attribute(std::vector<GameCharacter*> characters, std::string name, std::string attribute);

        static const char* type_string;

    protected:
        SceneManager* m_scene_manager;
        std::vector<std::unique_ptr<GameCharacter>> m_characters;

        std::vector<GameCharacter*> m_kill_characters;
        void trigger_kill();
        std::vector<GameCharacter*> m_add_characters;
        void trigger_add();

        template <class T>
        static bool register_class(std::string type);
    private:
        bool remove_character_internal(GameCharacter* game_character);
        static std::map<std::string, GameScene*>& get_dict();
};

template <class T>
std::vector<T*> GameScene::filter_characters(std::vector<GameCharacter*> characters) {
    std::vector<T*> new_characters;
    for(GameCharacter* c : characters) {
        if(c->get_type() == T::type) {
            new_characters.push_back(static_cast<T*>(c));
        }
    }
    return new_characters;
}

template <class T>
std::vector<T*> GameScene::get_characters() {
    std::vector<GameCharacter*> characters = get_characters_by_type(T::type);
    std::vector<T*> new_characters;
    for(auto c : characters) {new_characters.push_back(static_cast<T*>(c));}
    return new_characters;
}

template <class T>
T* GameScene::get_character() {
    std::vector<T*> characters = get_characters<T>();
    if(characters.empty()) {return nullptr;}
    else {return characters.front();}
}

template <class T>
bool GameScene::register_class(std::string type) {
    MapRef dummy(nullptr);
    GameScene* scene = new T(dummy,nullptr);
    get_dict()[type] = scene;
    return true;
}

template <class T>
GameCharacter* GameScene::add_character(T* character, std::string layer_name, std::string actor_name) {
    // Duplicate the derived character type | Both reference the same actor
    T* new_char = new T(*character);
    // Duplicate the actor
    salmon::ActorRef actor = add_actor(*static_cast<salmon::ActorRef*>(character),layer_name,actor_name);
    if(!actor.good()) {return nullptr;}
    else {
        // Assign the actor to the new character
        *static_cast<salmon::ActorRef*>(new_char) = actor;
        m_add_characters.push_back(new_char);
        return m_add_characters.back();
    }
}


#endif // GAME_SCENE_HPP_INCLUDED
