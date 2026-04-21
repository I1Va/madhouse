#pragma once

#include <unordered_set>

#include "vec2.hpp"
// #include "API/client.hpp"
// #include "API/server.hpp"


struct Cord {
    int x;
    int y;

    bool operator==(const Cord &other) const {
        return x == other.x && y == other.y;
    }
};

struct Tile {
    enum class Type {
        Wall,
        Floor,
    };
    Type type= Type::Floor;
};

struct GameMap {
    std::vector<std::vector<Tile>> grid;
    size_t tile_sz=0;
    GameMap
    (
        const size_t height, const size_t width,
        const size_t itile_sz
    ): 
    grid(height, std::vector<Tile>(width)),
    tile_sz(itile_sz)
    {}

    GameMap()=default;
};

using TankId = uint64_t;
using BulletId = uint64_t;

enum class Dir {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class RotationDir {
    LEFT,
    RIGHT,
};

inline Dir get_next_dir(const Dir dir) {
    switch (dir) {
        case Dir::UP:    return Dir::RIGHT;
        case Dir::RIGHT: return Dir::DOWN;
        case Dir::DOWN:  return Dir::LEFT;
        case Dir::LEFT:  return Dir::UP;
        default: return Dir::UP;
    }
}

inline Dir get_prev_dir(const Dir dir) {
    switch (dir) {
        case Dir::UP:    return Dir::LEFT;
        case Dir::RIGHT: return Dir::UP;
        case Dir::DOWN:  return Dir::RIGHT;
        case Dir::LEFT:  return Dir::DOWN;
        default: return Dir::UP;
    }
}

inline Dir get_rotated_dir(const Dir dir, const RotationDir rot_dir) {
    if (rot_dir == RotationDir::LEFT) {
        return get_prev_dir(dir);
    } else {
        return get_next_dir(dir);
    }   
} 

struct TankInfo {
    Cord pos;
    Dir dir;
};

struct BulletInfo {
    Cord pos;
    Dir dir;
    int speed;           
    TankId owner;  
};

struct GameState {
    GameMap map;
    uint64_t tick; 
    std::vector<TankInfo> tanks;
    std::vector<BulletInfo> bullets;
};
    
struct Tank {
    Vec2f pos;
    Dir dir;
    Vec2f hitbox_sz;
    // delay of shooting
    // hp
    Tank() = default;
};

struct Bullet {
    static constexpr float bullet_tile_scale=0.7;

    Vec2f pos;
    Dir dir;
    Vec2f hitbox_sz;
    BulletId id;

    Bullet() = default;
};

class ClientWorld {
    uint64_t tick_;
    GameMap map_;
    std::vector<Tank> tanks_;
    std::vector<Bullet> bullets_;

public:
    void apply_game_state(GameState &state) {
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
        
        bullets_.clear();
        std::transform(state.bullets.begin(), state.bullets.end(), 
            std::back_inserter(bullets_),
            [&state, this](auto &bullet_info) { 
                Bullet bullet;
                bullet.pos = Vec2f((bullet_info.pos.x + 0.5) * state.map.tile_sz, (bullet_info.pos.y + 0.5) * state.map.tile_sz);
                bullet.dir = bullet_info.dir;
                bullet.hitbox_sz = Vec2f(map_.tile_sz, map_.tile_sz) * Bullet::bullet_tile_scale;
                return bullet;
            });
    }

    uint64_t tick() const { return tick_; }
    const GameMap &map() const { return map_; }
    const std::vector<Tank> &tanks() const { return tanks_; }
    const std::vector<Bullet> &bullets() const { return bullets_; }
};