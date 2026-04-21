#include <vector>
#include <chrono>
#include <map>

#include "client.hpp"
#include "modlib_manager.hpp"
#include "server.hpp"

const char MAP_PATH[] = "content/maps/map1";
const size_t TILE_SZ = 50;

const char MAP_MOD_PATH[]           = "server_plugins/map/build/ida_maplib.so";
const char GENERAL_LOGIC_MOD_PATH[] = "server_plugins/general_logic/build/ida_maplib.so";
const char PACMAN_MOD_PATH[]        = "server_plugins/pacman/build/ida_maplib.so";
const char TANK_MOD_PATH[]          = "server_plugins/tank/build/ida_maplib.so";


#define CHECK_MOD_LOAD(mod, path)                               \
{                                                               \
    if (mod == nullptr) {                                       \
        std::cerr << "failed to load mod `" << path << "`\n";   \
        return 1;                                               \
    }                                                           \
}                               

int main() {
    Server server;
    ModManager modManager;

    Mod *mapMod              = modManager.loadFromFile(MAP_MOD_PATH);           CHECK_MOD_LOAD(mapMod, MAP_MOD_PATH)
    Mod *generalGameLogicMod = modManager.loadFromFile(GENERAL_LOGIC_MOD_PATH); CHECK_MOD_LOAD(generalGameLogicMod, GENERAL_LOGIC_MOD_PATH)
    Mod *pacmanMod           = modManager.loadFromFile(PACMAN_MOD_PATH);        CHECK_MOD_LOAD(pacmanMod, PACMAN_MOD_PATH)
    Mod *tankMod             = modManager.loadFromFile(TANK_MOD_PATH);          CHECK_MOD_LOAD(tankMod, TANK_MOD_PATH)




//     Client::Config config;
//     config.gfx_config.screen_height = map.grid.size() * map.tile_sz;
//     config.gfx_config.screen_width = map.grid[0].size() * map.tile_sz;

//     Client client_game(config);
 
//     // server.add_client(&client_game);

//     // npc1_init(server, {3, 3});
//     // npc2_init(server, {9, 15});
//     // npc3_init(server, {15, 5});
//     // server.add_npc_script(npc1_step);
//     // server.add_npc_script(npc2_step);
//     // server.add_npc_script(npc3_step);

//     const int FPS = 10;
//     const int frameDelay = 1000 / FPS;

//     Uint32 frameStart;
//     int frameTime;
//     bool running = true;
//     SDL_Event e;
//     while (running) {
//         frameStart = SDL_GetTicks();

//         while (SDL_PollEvent(&e)) {
//             if (e.type == SDL_QUIT) running = 0;
//         }

//         // server.update();
//         client_game.update();

//         frameTime = SDL_GetTicks() - frameStart;
//         if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
        
//     }
}