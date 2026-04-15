#pragma once

#include <unordered_set>

#include "vec2.hpp"
#include "API/client.hpp"
#include "API/server.hpp"

namespace client 
{

struct Tank {
    Vec2f pos;
    api::Dir dir;
    Vec2f hitbox_sz;
    // delay of shooting
    // hp
    Tank() = default;
};

struct Bullet {
    static constexpr float bullet_tile_scale=0.7;

    Vec2f pos;
    api::Dir dir;
    Vec2f hitbox_sz;
    api::BulletId id;

    Bullet() = default;
};

class ClientWorld {
    uint64_t tick_;
    api::GameMap map_;
    std::vector<Tank> tanks_;
    
    std::unordered_set<api::BulletId> prev_bullets_;
    std::vector<Bullet> active_bullets_;
    std::vector<Bullet> death_bullets_;

public:
    void apply_game_state(api::GameState &state) {
        tick_ = state.tick;
        map_ = state.map;
        
        tanks_.clear();
        std::transform(state.tanks.begin(), state.tanks.end(), 
            std::back_inserter(tanks_),
            [&state, this](auto &tank_info) { 
                Tank tank;
                tank.pos = Vec2f(tank_info.pos.x * state.map.tile_sz, tank_info.pos.y * state.map.tile_sz);
                tank.dir = tank_info.dir;
                tank.hitbox_sz = Vec2f(map_.tile_sz, map_.tile_sz);
                return tank;
            });
        
        active_bullets_.clear();
        death_bullets_.clear();
    
        std::transform(state.bullets.begin(), state.bullets.end(), 
            std::back_inserter(active_bullets_),
            [&state, this](auto &bullet_info) { 
                Bullet bullet;
                bullet.pos = Vec2f((bullet_info.pos.x + 0.5) * state.map.tile_sz, (bullet_info.pos.y + 0.5) * state.map.tile_sz);
                bullet.dir = bullet_info.dir;
                bullet.hitbox_sz = Vec2f(map_.tile_sz, map_.tile_sz) * Bullet::bullet_tile_scale;
                return bullet;
            });

        for (auto &bullet : active_bullets_) {
            if (prev_bullets_.contains(bullet.id)) {
                death_bullets_.push_back(bullet);
            }
        }

        prev_bullets_.clear();
        std::transform(state.bullets.begin(), state.bullets.end(),
               std::inserter(prev_bullets_, prev_bullets_.end()),
               [](const auto& bullet) { return bullet.id; });
    }

    uint64_t tick() const { return tick_; }
    const api::GameMap &map() const { return map_; }
    const std::vector<Tank> &tanks() const { return tanks_; }
    const std::vector<Bullet> &active_bullets() const { return active_bullets_; }
    const std::vector<Bullet> &death_bullets() const { return death_bullets_; }
};




} // namespace client 