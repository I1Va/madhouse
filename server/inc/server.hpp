#pragma once

#include <chrono>
#include <cstdint>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "API/textmsg_server.hpp"
// #include "API/client.hpp"

// // testmsg
// struct ServerCommand {
//     enum Type { 
//         MoveForward, 
//         TankRotate,
//         Spawn,
//         TurretFire,
//     };
//     Type type;
//     TankId tank_id;
//     RotationDir rot_dir; 
//     Cord tile_pos;
// };

class Server : public textmsg::Server {   
    // ServerWorld world_;
    
    std::vector<textmsg::Client*> clients_;
    std::unordered_set<textmsg::Plugin*> plugins_;
    std::unordered_map<std::string, textmsg::Plugin *> prefixTable_;

    // std::queue<ServerCommand> comand_queue;
    // std::vector<std::function<void(IServer &)>> scripts_;
    
public:
    ~Server() = default;
    Server() = default;

    std::vector<textmsg::Client*> allClients() override {
        return clients_;
    }

    bool registerPlugin(textmsg::Plugin *plugin) override {
        assert(plugin);
        if (plugins_.contains(plugin)) {
            std::cerr << "server already contains plugin:`" << plugin->name() << "`\n";
            return false;
        }

        plugins_.insert(plugin);
        plugin->onServerInit(this);

        for (const std::string &prefix : plugin->prefixes()) {
            if (!registerPrefix(prefix, plugin)) {
                std::cerr << "failed to register prefix`" << prefix << "` from plugin `" << plugin->name() << "`\n";
                return false;
            }
        }

        return true;
    }
    
    void addClient(textmsg::Client *client) {
        clients_.push_back(client);
    }

// TEMP
    void receive_message(textmsg::Message msg) {
    
    } 
private:
    bool registerPrefix(const std::string &prefix, textmsg::Plugin *self) {        
        if (prefixTable_.contains(prefix)) {
            return false;
        }
       
        prefixTable_[prefix] = self;
        return true;
    }

    // void update() override {
    //     for (auto launch_script : scripts_) launch_script(*this);

    //     execute_command_queue();
    //     world_.simulate_step();        

    //     broadcast(msg);
        
    // }


    // -> TEXT MESSAGES 
    // TankId spawn_tank_in_tile(const Cord tile_pos) override {
    //     ServerCommand comand;
    //     TankId id = world_.get_new_tank_id();
    //     comand.type = ServerCommand::Type::Spawn;
    //     comand.tank_id = id;
    //     comand.tile_pos = tile_pos;
    //     comand_queue.push(comand);
    //     return id;
    // }

    // void tank_move_torward(const TankId tank_id) override {
    //     ServerCommand comand;
    //     comand.type = ServerCommand::Type::MoveForward;
    //     comand.tank_id = tank_id;
    //     comand_queue.push(comand);
    // }
    
    // void tank_rotate(const TankId tank_id, const RotationDir dir) override {
    //     ServerCommand comand;
    //     comand.type = ServerCommand::Type::TankRotate;
    //     comand.tank_id = tank_id;
    //     comand.rot_dir = dir;
    //     comand_queue.push(comand);
    // }

    // void turret_fire(const TankId tank_id) override {
    //     ServerCommand comand;
    //     comand.type = ServerCommand::Type::TurretFire;
    //     comand.tank_id = tank_id;
    //     comand_queue.push(comand);
    // }    

    // int get_tank_info(TankId id, TankInfo &info) override {
    //     return world_.get_tank_info(id, info);
    // }

    // void add_npc_script(std::function<void(IServer &)> script) override {
    //     scripts_.push_back(script);
    // }

// private:
//     void execute_command_queue() {
//         while (!comand_queue.empty()) {
//             auto &command = comand_queue.front();
//             switch (command.type) {
//                 case ServerCommand::Type::MoveForward: world_.tank_move_forward(command.tank_id); break;
//                 case ServerCommand::Type::TankRotate: world_.tank_rotate(command.tank_id, command.rot_dir); break;
//                 case ServerCommand::Type::TurretFire: world_.turret_fire(command.tank_id); break;
//                 case ServerCommand::Type::Spawn: world_.spawn_tank_in_tile(command.tile_pos, command.tank_id); break;
//                 default:
//                     assert(false && "unknown command in queue" && (int) command.type);
//             }
//             comand_queue.pop();
//         }   
//     }
};
