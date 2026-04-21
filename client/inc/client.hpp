#pragma once

#include <iostream>

#include "BmServerModule.hpp"

#include "graphics.hpp"

// #include <iostream>
// #include <exception>
// #include <memory>
// #include <string>

// #include "API/client.hpp"
// #include "API/server.hpp"
// #include "vec2.hpp"


// #include "client_world.hpp"


class Client : public modlib::BmClient {

    /** Send already encoded message to him */
    void send(bmsg::RawMessage msg) override {
        std::cout << "receied raw message from server : `" << msg.data() << "`\n"; 
    }

    /** Client's ID */
    size_t id() const override {
        return 1234;
    }

    Graphics graphics_;
    ClientWorld world_;

public:
    struct Config {
        Graphics::Config gfx_config;
    };

    Client(const Config &config): graphics_(config.gfx_config) {}

    void update() { 
        graphics_.render(world_); 
    }

    // // receive game state from server
    // void receive(GameState &state) override {
    //     world_.apply_game_state(state);
    // }

    // bool connect(const std::string &, int) override {
    //     return true;
    // }

    // bool isConnected() const override {
    //     return true;
    // }
};
