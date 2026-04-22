#pragma once

#include <iostream>

#include "GLogicModule.hpp"
#include "modlib_manager.hpp"
#include "binmsg.hpp"

namespace modlib {

class IDAGLogicModule : public GLogicModule {
    const std::string modulePrefix = "core"; 

public:
    std::string_view id() const override { return "ida_bardak_glogic"; }
    std::string_view brief() const override { return "Core synchronization and tick broadcast"; }
    ModVersion version() const override { return ModVersion(1, 0, 0); }

    void onSetup(BmServer *server) override {
        server->registerPrefix(modulePrefix, this);
    }

    void onMessage(BmClient *client, bmsg::RawMessage msg) override {
        const bmsg::Header* head = msg.header();
        // client->send()

        if (head->type == "ping") {
            auto bufer = bmsg::generateEmptyMessage(modulePrefix, "pong", msg.header()->id);
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


    // Called by the server's main loop (from your server.hpp update sketch)
    void onTick() override {
        // Here you would serialize the global state or 
        // instruct other modules to broadcast their states.
    }
};

extern "C" Mod* modlib_create(ModManager*) { return new IDAGLogicModule(); }

} // namespace modlib