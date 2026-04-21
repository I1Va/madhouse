#pragma once

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "API/plugins/server/general_logic_plugin_api.hpp"

// class ServerWorld { // GameWorld logic
// private:
//     GameMap map_;
//     uint64_t tick_=0;

//     std::map<uint64_t, Tank> tanks_; 
//     std::vector<Bullet> bullets_;
//     TankId tank_id_=0;
//     BulletId bullet_id_=0;

// public:
//     ServerWorld(const GameMap &map): map_(map) {}
    
//     TankId get_new_tank_id() { return tank_id_++; }
//     BulletId get_new_bullet_id() { return bullet_id_++; }
    
//     GameState create_snapshot() const {
//         GameState state;
//         state.map = map_;
//         state.tick = tick_;
//         std::transform(tanks_.begin(), tanks_.end(), 
//             std::back_inserter(state.tanks),
//             [](auto tank_pair) { return tank_pair.second.get_info(); });

//         std::transform(bullets_.begin(), bullets_.end(), 
//             std::back_inserter(state.bullets),
//             [](auto &bullet) { return bullet.get_info(); });

//         return state;
//     }

//     void spawn_tank_in_tile(const Cord tile_pos, const TankId id) {
//         tanks_[id] = Tank();
//         auto &tank = tanks_[id];
//         tank.pos = tile_pos;
//     }

//     void tank_rotate(const TankId tank_id, RotationDir rot_dir) {
//         if (!tanks_.contains(tank_id)) return;

//         tanks_[tank_id].dir = get_rotated_dir(tanks_[tank_id].dir, rot_dir); 
//     }

//     void turret_fire(const TankId tank_id) {
//         if (!tanks_.contains(tank_id)) return;

//         Tank &tank = tanks_[tank_id];
//         Bullet bullet;
//         bullet.id = get_new_bullet_id(); 
//         bullet.pos = tank.pos;
//         bullet.dir = tank.dir;
//         bullet.speed = Bullet::BULLET_SPEED;
//         bullet.owner = tank_id;
//         bullets_.push_back(bullet);

//         bullets_.push_back(bullet);
//     }

//      void simulate_step() {
//         for (auto it = bullets_.begin(); it != bullets_.end(); ) {
//             Cord delta = dir_to_cord(it->dir);
//             it->pos.x += delta.x * it->speed;
//             it->pos.y += delta.y * it->speed;

//             if (is_wall(it->pos)) {
//                 it = bullets_.erase(it);
//                 continue;
//             }
//             bool hit = false;
//             for (auto &[id, tank] : tanks_) {
//                 if (id == it->owner) continue;
//                 if (tank.pos == it->pos) {
//                     it = bullets_.erase(it);
//                     tanks_.erase(id);   // tank destroyed
//                     hit = true;
//                     break;
//                 }
//             }
//         if (hit) continue;
//         ++it;
//         }
//     }

//     bool is_wall(const Cord cord) {
//         if (cord.y >= (int) map_.grid.size()) return false;
//         if (cord.x >= (int) map_.grid[0].size()) return false;
//         if (cord.y < 0) return false;
//         if (cord.x < 0) return false;
//         return map_.grid[cord.y][cord.x].type == Tile::Type::Wall;
//     }

//     Cord get_tank_hitbox_size() const {
//         int sz = map_.tile_sz * 0.9; 
//         return {sz, sz};
//     }

//      bool is_tile_occupied(const Cord &cord, TankId exclude_id = 0) const {
//         for (const auto &[id, tank] : tanks_) {
//             if (id == exclude_id) continue;
//             if (tank.pos == cord) return true;
//         }
//         return false;
//     }

//     void tank_move_forward(const TankId tank_id) {
//         if (!tanks_.contains(tank_id)) return;

//         auto &tank = tanks_[tank_id];
//         Dir dir = tank.dir;
//         Cord pos = tank.pos;
//         Cord dir_vec = dir_to_cord(dir);

//         Cord new_pos = {
//             static_cast<int>(pos.x + dir_vec.x),
//             static_cast<int>(pos.y + dir_vec.y)
//         };

//         if (is_wall(new_pos)) return;
//         if (is_tile_occupied(new_pos, tank_id)) return;

//         tank.pos = new_pos;
//     }


//     int get_tank_info(TankId id, TankInfo &info) {
//         if (!tanks_.contains(id)) return 1;
//         info = tanks_[id].get_info();
//         return 0;
//     }

// private:
//     static Cord dir_to_cord(Dir dir) {
//     switch (dir) {
//             case Dir::UP:    return { 0, -1 }; // move up
//             case Dir::DOWN:  return { 0,  1 }; // move down
//             case Dir::LEFT:  return { -1, 0 }; // move left
//             case Dir::RIGHT: return { 1,  0 }; // move right
//             default: return {0, 0}; // no movement
//         }
//     }
// };

class IAGeneralLogicPlugin : public GeneralLogicPlugin{
    std::string name_ = "IAGenerLogicPlugin";
    std::vector<std::string> prefixes_ = {"general"};

public:
    IAGeneralLogicPlugin() = default;
    ~IAGeneralLogicPlugin() = default;

    const std::vector<std::string> &prefixes() const override { return prefixes_; }
    const std::string_view name() const override { return name_; }
    void onServerInit(textmsg::Server *server) override {
        std::cout << name() << "onServerInit\n";
    }
    void onMessage(textmsg::Client *client, const textmsg::Message &msg) override {
        std::cout << name() << "onMessage : " << msg.name << "\n";
    }
};
