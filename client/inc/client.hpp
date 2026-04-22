#pragma once

#include <iostream>

#include "BmServerModule.hpp"

#include "graphics.hpp"
#include "client_world.hpp"


class Client {
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

    // TEMP
    void send(bmsg::RawMessage msg) {
        std::cout << "client received " << msg.body() << "\n";
    }

    // void receive(GameState &state) override {
    //     world_.apply_game_state(state);
    // }
};
