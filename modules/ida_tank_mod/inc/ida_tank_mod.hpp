#pragma once

#include "BmServerModule.hpp"

#include "MapModule.hpp"

#include "modlib_manager.hpp"
#include <map>

namespace modlib {

struct Tank {
    Cord pos;
    int dir;
};

class TankLogicImpl : public BmServerModule {
    MapModule* m_map = nullptr;
    std::map<size_t, Tank> m_tanks;

public:
    std::string_view id() const override { return "isd.bardak.char.tank"; }
    std::string_view brief() const override { return "Tank movement and shooting logic"; }
    ModVersion version() const override { return ModVersion(1, 0, 0); }

    void onResolveDeps(ModManager *mm) override {
        // Find the map module strictly before allowing gameplay
        m_map = mm->anyOfType<MapModule>();
        if (!m_map) throw std::runtime_error("Tank logic requires MapModule!");
    }

    void onSetup(BmServer *server) override {
        server->registerPrefix("tank", this);
    }

    void onConnect(BmClient *client) override {
        // Spawn tank for new player
        m_tanks[client->id()] = Tank{{0, 0}, 0}; 
    }

    void onDisconnect(BmClient *client) override {
        m_tanks.erase(client->id());
    }

    void onMessage(BmClient *client, bmsg::RawMessage msg) override {
        const bmsg::Header* head = msg.header();
        if (head->type != "MOVE") return;

        // Parse movement logic using bmsg::Reader logic
        const char* ptr = reinterpret_cast<const char*>(msg.bodyPtr());
        if (msg.body().size() < sizeof(Cord)) return;
        
        Cord delta;
        std::memcpy(&delta, ptr, sizeof(Cord));

        auto& tank = m_tanks[client->id()];
        Cord new_pos = {tank.pos.x + delta.x, tank.pos.y + delta.y};

        // Query MapModule for collision
        if (!m_map->isWall(new_pos)) {
            tank.pos = new_pos;
            
            // Broadcast new position to all clients
            server()->forAllClients([&](BmClient* c) {
                // c->send(movement_update_msg);
            });
        }
    }
};

extern "C" Mod* modlib_create(ModManager*) { return new TankLogicImpl(); }

} // namespace modlib