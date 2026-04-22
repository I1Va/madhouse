#pragma once
#include "modlib_mod.hpp"
#include "MapModule.hpp"

#include <string>
#include <vector>

namespace modlib {

class IDAMapModule : public MapModule {
    const std::string modulePrefix_ = "map"; 

    std::vector<std::vector<Tile>> grid_;
  
public:
    std::string_view id() const override { return "isd.bardak.map"; }
    std::string_view brief() const override { return "Provides grid and collision detection"; }
    ModVersion version() const override { return ModVersion(1, 0, 0); }

    bool isWall(Cord cord) const override {
        if (cord.y >= (int) grid_.size() || cord.y < 0) return false;
        if (cord.x >= (int) grid_[0].size() || cord.x < 0) return false;
        return grid_[cord.y][cord.x].type == Tile::Wall;
    }

    void loadMap() override { /* Logic to load map from disk */ }

    void onSetup(BmServer *server) override {
        server->registerPrefix(modulePrefix_, this);
    }

    void onMessage(BmClient *client, bmsg::RawMessage msg) override {
        const bmsg::Header* head = msg.header();
        // client->send()

        if (head->type == "ping") {
            auto bufer = bmsg::generateEmptyMessage(modulePrefix_, "pong", msg.header()->id);
            bmsg::RawMessage pingMsg(std::string_view(bufer.data(), bufer.size()));
            client->send(pingMsg);
        
            // map = mapMod.get_map()
            // map.hide_info(client_id)
            // map.encode()
    
            // send into to the right client
            // server()->forAllClients()
        }
    }

    void onResolveDeps(ModManager *mm) override {
        assert(mm);
        // mapMod = mm.get_any
    }

    void onDepsResolved(ModManager *mm) override {
        assert(mm);
    }

    void onBeforeCleanup(ModManager *mm) override {

    }
};

extern "C" Mod* modlib_create(ModManager*) { return new IDAMapModule(); }

} // namespace modlib