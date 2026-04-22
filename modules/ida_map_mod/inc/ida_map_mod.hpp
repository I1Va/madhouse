#pragma once
#include "modlib_mod.hpp"
#include "MapModule.hpp"
#include <vector>

namespace modlib {

class IDAMapModule : public MapModule {
    std::vector<std::vector<Tile>> m_grid;
    int m_tile_sz = 10;

public:
    std::string_view id() const override { return "isd.bardak.map"; }
    std::string_view brief() const override { return "Provides grid and collision detection"; }
    ModVersion version() const override { return ModVersion(1, 0, 0); }

    bool isWall(Cord cord) const override {
        if (cord.y >= (int)m_grid.size() || cord.y < 0) return false;
        if (cord.x >= (int)m_grid[0].size() || cord.x < 0) return false;
        return m_grid[cord.y][cord.x].type == Tile::Wall;
    }

    void loadMap() override { /* Logic to load map from disk */ }
};

extern "C" Mod* modlib_create(ModManager*) { return new IDAMapModule(); }

} // namespace modlib