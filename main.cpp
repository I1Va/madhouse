#include <vector>
#include <chrono>
#include <map>

#include "client.hpp"
#include "modlib_manager.hpp"
#include "server.hpp"

const char MAP_PATH[] = "content/maps/map1";
const size_t TILE_SZ = 50;

const char MAP_MOD_PATH[]           = "build/modules/ida_map_mod/libida.bardak.map.so";
const char GENERAL_LOGIC_MOD_PATH[] = "build/modules/ida_glogic_mod/libida.bardak.glogic.so";
const char PACMAN_MOD_PATH[]        = "server_plugins/pacman/build/ida_maplib.so";
const char TANK_MOD_PATH[]          = "server_plugins/tank/build/ida_maplib.so";


#define CHECK_MOD_LOAD(mod, path)                               \
{                                                               \
    if (mod == nullptr) {                                       \
        std::cerr << "failed to load mod `" << path << "`\n";   \
        return 1;                                               \
    }                                                           \
}                               

void NETWORK_SEND_MESSAGE_TO_CLIENT(Client *client, bmsg::RawMessage msg) {
    assert(client);
    client->send(msg);
}

size_t NETWORK_GET_CLIENT_ID(Client *client) {
    assert(client);
    return reinterpret_cast<size_t>(client);
}

int main() {
    Server server;

    ModManager modManager;

    // Mod *mapMod              = modManager.loadFromFile(MAP_MOD_PATH);           CHECK_MOD_LOAD(mapMod, MAP_MOD_PATH)
    Mod *generalGameLogicModRaw = modManager.loadFromFile(GENERAL_LOGIC_MOD_PATH); 
    CHECK_MOD_LOAD(generalGameLogicModRaw, GENERAL_LOGIC_MOD_PATH)
    modlib::BmServerModule *generalGameLogicMod = static_cast<modlib::BmServerModule *>(generalGameLogicModRaw);
    generalGameLogicMod->setServer(&server);

    Mod *mapMod = modManager.loadFromFile(MAP_MOD_PATH); 
    

    generalGameLogicMod->onSetup(&server);
    
    // Mod *pacmanMod           = modManager.loadFromFile(PACMAN_MOD_PATH);        CHECK_MOD_LOAD(pacmanMod, PACMAN_MOD_PATH)
    // Mod *tankMod             = modManager.loadFromFile(TANK_MOD_PATH);          CHECK_MOD_LOAD(tankMod, TANK_MOD_PATH)

    modManager.initLoaded();

    Client::Config config;
    config.gfx_config.screen_height = 600;
    config.gfx_config.screen_width = 800;
    Client client(config);


    server.connect(&client);


    std::vector<char> glogicPingMsgBuf = bmsg::generateEmptyMessage("core", "ping", 0);
    bmsg::RawMessage glogicPingMsg(std::string_view(glogicPingMsgBuf.data(), glogicPingMsgBuf.size()));
    server.send(&client, glogicPingMsg);


//     // npc1_init(server, {3, 3});
//     // npc2_init(server, {9, 15});
//     // npc3_init(server, {15, 5});
//     // serverd_npc_script(npc1_step);
//     // server.add_npc_script(npc2_step);
//     // server.add_npc_script(npc3_step);



    // const int FPS = 10;
    // const int frameDelay = 1000 / FPS;
    // Uint32 frameStart;
    // int frameTime;
    // bool running = true;
    // SDL_Event e;
    // while (running) {
    //     frameStart = SDL_GetTicks();

    //     while (SDL_PollEvent(&e)) {
    //         if (e.type == SDL_QUIT) running = 0;
    //     }

    //     server.update();

    //     client.update();

    //     frameTime = SDL_GetTicks() - frameStart;
    //     if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
        
    // }
}