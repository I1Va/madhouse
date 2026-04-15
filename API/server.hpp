// #pragma once

// #include <vector>
// #include <cstdint>
// #include <functional>

// class IClient;

// struct Cord {
//     int x;
//     int y;

//     bool operator==(const Cord &other) const {
//         return x == other.x && y == other.y;
//     }
// };

// struct Tile {
//     enum class Type {
//         Wall,
//         Floor,
//     };
//     Type type= Type::Floor;
// };

// struct GameMap {
//     std::vector<std::vector<Tile>> grid;
//     size_t tile_sz=0;
//     GameMap
//     (
//         const size_t height, const size_t width,
//         const size_t itile_sz
//     ): 
//     grid(height, std::vector<Tile>(width)),
//     tile_sz(itile_sz)
//     {}

//     GameMap()=default;
// };

// using TankId = uint64_t;
// using BulletId = uint64_t;

// enum class Dir {
//     LEFT,
//     RIGHT,
//     UP,
//     DOWN
// };

// enum class RotationDir {
//     LEFT,
//     RIGHT,
// };

// inline Dir get_next_dir(const Dir dir) {
//     switch (dir) {
//         case Dir::UP:    return Dir::RIGHT;
//         case Dir::RIGHT: return Dir::DOWN;
//         case Dir::DOWN:  return Dir::LEFT;
//         case Dir::LEFT:  return Dir::UP;
//         default: return Dir::UP;
//     }
// }

// inline Dir get_prev_dir(const Dir dir) {
//     switch (dir) {
//         case Dir::UP:    return Dir::LEFT;
//         case Dir::RIGHT: return Dir::UP;
//         case Dir::DOWN:  return Dir::RIGHT;
//         case Dir::LEFT:  return Dir::DOWN;
//         default: return Dir::UP;
//     }
// }

// inline Dir get_rotated_dir(const Dir dir, const RotationDir rot_dir) {
//     if (rot_dir == RotationDir::LEFT) {
//         return get_prev_dir(dir);
//     } else {
//         return get_next_dir(dir);
//     }   
// } 

// struct TankInfo {
//     Cord pos;
//     Dir dir;
// };

// struct BulletInfo {
//     Cord pos;
//     Dir dir;
//     int speed;           
//     TankId owner;
//     BulletId id;  
// };

// struct GameState {
//     GameMap map;
//     uint64_t tick; 
//     std::vector<TankInfo> tanks;
//     std::vector<BulletInfo> bullets;
// };

// class IServer {
// public:
//     virtual ~IServer() = default;
//     virtual void add_client(IClient *client) = 0;
//     virtual void update() = 0;

//     virtual TankId spawn_tank_in_tile(const Cord tile_pos) = 0;
//     virtual void tank_move_torward(const TankId tank_id) = 0;
//     virtual void tank_rotate(const TankId tank_id, const RotationDir dir) = 0;
//     virtual void turret_fire(const TankId tank_id) = 0;
//     virtual int get_tank_info(TankId id, TankInfo &info) = 0;
//     virtual void add_npc_script(std::function<void(IServer &)> script) = 0;

//     // virtual void send_event(int event_id) = 0;
//     // virtual void subscr_on_event(int event_id) = 0;
// };
