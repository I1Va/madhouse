#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "API/plugins/server/special_logic_plugin_api.hpp"
#include "API/textmsg_server.hpp"

// #pragma once

// struct Tank {
//     Cord pos;
//     Dir dir;
//     // delay of shooting
//     // hp
//     Tank() = default;

//     TankInfo get_info() {
//         TankInfo info;
//         info.pos = pos;
//         info.dir = dir;
//         return info;
//     }
// };

// struct Bullet {
//     static constexpr int BULLET_SPEED = 1;

//     Cord pos;
//     Dir dir;
//     int speed;           
//     TankId owner;
//     BulletId id;

//     Bullet() = default;

//     BulletInfo get_info() const {
//         BulletInfo info;
//         info.pos = pos;
//         info.dir = dir;
//         info.speed = speed;
//         info.owner = owner;
//         info.id = id;
//         return info;
//     }
// };


class IATankPlugin : public SpecialLogicPlugin {
    std::string name_ = "IATankPlugin";
    std::vector<std::string> prefixes_ = {"tank"};

public:
    IATankPlugin() = default;
    ~IATankPlugin() = default;

    const std::vector<std::string> &prefixes() const override { return prefixes_; }
    const std::string_view name() const override { return name_; }
    void onServerInit(textmsg::Server *server) override { 
        // server->get_plugin_by_type("map_plugin")
        std::cout << name() << "onServerInit\n";
    }
    void onMessage(textmsg::Client *client, const textmsg::Message &msg) override {
        if (msg.name == "rotate") {
            size_t len = msg.args.size();
            if (len != 2) {
                std::cerr << "IATankPlugin " << msg.prefix << ""  << "invalid number of args (expected 2)\n";
            }
            
            msg.args[0]
        }
    
        std::cout << name() << "onMessage : " << msg.name << "\n";
    }

    void loadMap(const std::string path) override {
        map_.loadMap(path);
    }
private:
    bool check_message(const textmsg::Message &msg) const {

    }
};
