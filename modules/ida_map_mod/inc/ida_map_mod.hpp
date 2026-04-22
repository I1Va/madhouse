#pragma once
#include "modlib_mod.hpp"
#include "Map.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace modlib {

class IDATile : public Tile {
    Vec2i pos_;
    std::vector<Unit *> units_;
    bool isWalkable_;

public:
    IDATile(const Vec2i pos, const bool isWalkable): 
        pos_(pos), isWalkable_(isWalkable) {}
    ~IDATile() = default;

    
    Vec2i pos() const override { return pos_; }
    void setPos(const Vec2i newPos) override {pos_ = newPos; }

    const std::vector<Unit*> &units() override { return units_; }

    void addUnit(Unit *unit) override {
        auto it = std::find(units_.begin(), units_.end(), unit);
        if (it == units_.end()) {
            units_.push_back(unit);
        }
    }

    void removeUnit(Unit* unit) override {
        assert(unit);
        auto it = std::remove(units_.begin(), units_.end(), unit);        
        if (it != units_.end()) {
            units_.erase(it, units_.end());
        }
    }

    bool isWalkable() const override { return isWalkable_; }
    void setWalkable(const bool walkable) { isWalkable_ = walkable; }
};

class IDAMapModule : public Map {
    const std::string modulePrefix_ = "map"; 

    std::unordered_map<size_t, std::unique_ptr<Unit>> units_;
    std::vector<std::vector<std::unique_ptr<IDATile>>> grid_;
    size_t nextId = 0;

    Unit *addUnit(Vec2i pos, size_t id, std::unique_ptr<Unit> &&u) override {
        u->setMap(this);
        u->setTile(at(pos));
        at(pos)->addUnit(u.get());
        units_[id] = std::move(u);
    };

    void moveUnit(Unit *u, Vec2i pos) override {
        assert(u);
        
        u->tile()->removeUnit(u);
        u->setTile(at(pos));
        u->tile()->addUnit(u);
    }

    void removeUnit(Unit *u) override {
        assert(u);
        size_t id = u->id();
        units_.erase(id);
    }

    void initializeGrid() {
        const int width = 20;
        const int height = 20;

        grid_.reserve(height);

        for (int y = 0; y < height; ++y) {
            std::vector<std::unique_ptr<IDATile>> row;
            row.reserve(width);

            for (int x = 0; x < width; ++x) {
                auto tile = std::make_unique<IDATile>();

                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    tile->setWalkable(false); 
                } else {
                    tile->setWalkable(true);
                }
                row.push_back(std::move(tile));
            }
            grid_.push_back(std::move(row));
        }
    }

  
public:
    IDAMapModule() {
        initializeGrid();
    }
    ~IDAMapModule() = default;

    std::string_view id() const override { return "ida.bardak.map"; }
    std::string_view brief() const override { return "Provides grid and collision detection"; }
    ModVersion version() const override { return ModVersion(1, 0, 0); }

    Unit *byId(size_t id) override {
        if (!units_.contains(id)) return nullptr;
        return units_[id].get();
    }

    Vec2i size() const override {
        if (grid_.size() == 0) return {0, 0};
        return Vec2i(grid_.size(), grid_[0].size());
    }

    Tile *at(Vec2i pos) override {
        if (grid_.size() <= pos.x) return nullptr;
        if (grid_[pos.x].size() <= pos.y) return nullptr;
        return grid_[pos.x][pos.y].get();
    }

    size_t getNewUnitId() override {
        return nextId++;
    }
};

extern "C" Mod* modlib_create(ModManager*) { return new IDAMapModule(); }

} // namespace modlib