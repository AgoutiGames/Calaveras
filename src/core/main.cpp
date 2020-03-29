#include "core/scene_manager.hpp"

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>

    SceneManager* game;

    void one_iteration();

    int main() {
        game = new SceneManager("scenes/menu.tmx");
        emscripten_set_main_loop(&one_iteration, 0, 0);
        return 0;
    }

    void one_iteration() {game->run();}

#else
    int main() {
        // The very sleek game loop
        // The map "entry point" is kinda hardcoded in here.
        // Either change to your liking or stick to defaults.
        SceneManager game("scenes/menu.tmx");

        // Run the game until it doesn't run anymore :-D
        while(game.run()) {}
        return 0;
    }
#endif
