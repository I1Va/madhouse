#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "API/plugins/server/map_plugin_api.hpp"

struct Tile {
    enum class Type {
        Wall,
        Floor,
    };
    Type type= Type::Floor;
};

class GameMap {
    std::vector<std::vector<Tile>> grid_;

public:
    bool loadMap(const std::string &path) {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "failed to load map from file `" << path << "`\n";
            return false;
        }

        int height = 0;
        int width = 0;
        file >> height >> width;

        grid_.resize(height);
        for (auto& row : grid_) {
            row.resize(width);
        }   
    
        std::string key;

        std::map<std::string, Tile::Type> tile_map;
        tile_map["Wall"] = Tile::Type::Wall;
        tile_map["Floor"] = Tile::Type::Floor;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                file >> key;
                if (!tile_map.contains(key)) key = "Floor";
                grid_[y][x].type = tile_map[key];            
            }
        }
    
        return true;
    }


};

class IAMapPlugin : public MapPlugin {
    std::string name_ = "IAMapPlugin";
    std::vector<std::string> prefixes_ = {"map"};

    GameMap map_;

public:
    IAMapPlugin() = default;
    ~IAMapPlugin() = default;

    const std::vector<std::string> &prefixes() const override { return prefixes_; }
    const std::string_view name() const override { return name_; }
    void onServerInit(textmsg::Server *server) override {
        std::cout << name() << "onServerInit\n";
    }
    void onMessage(textmsg::Client *client, const textmsg::Message &msg) override {
        std::cout << name() << "onMessage : " << msg.name << "\n";
    }

    void loadMap(const std::string path) override {
        map_.loadMap(path);
    }
};