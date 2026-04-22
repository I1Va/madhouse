#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <memory>

#include "BmServerModule.hpp"
#include "server_network.hpp"


class Server : public modlib::BmServer {       
    std::vector<std::unique_ptr<modlib::BmClient>> clients_; 
    ServerNetwork serverNetwork_;

    std::unordered_map<std::string, modlib::BmServerModule *> prefixOwners_;
    std::unordered_set<modlib::BmServerModule *> allPrefixListeners_;
    std::unordered_map<std::string, std::unordered_set<modlib::BmServerModule *>> prefixListeners_;
    
public:
    ~Server() = default;
    Server() = default;

    bool registerPrefix(std::string_view pref, modlib::BmServerModule *mod) override {
        assert(mod);
        std::string prefString(pref);
        if (prefixOwners_.contains(prefString)) {
            std::cerr << "prefix `" << pref << "` has been already registered\n";
            return false;
        }

        prefixOwners_[prefString] = mod;

        return true;
    }

    void listenPrefix(std::string_view pref, modlib::BmServerModule *mod) override {
        assert(mod);
        std::string prefString(pref);
        prefixListeners_[prefString].insert(mod);
    }

    void listenAll(modlib::BmServerModule *mod) override {
        assert(mod);
        allPrefixListeners_.insert(mod);
    }
    
    void forAllClients(const std::function<void(modlib::BmClient* client)> cb) override {
        assert(cb);
        for (auto &client : clients_) {
            cb(client.get());
        }
    }

    void send(bmsg::RawMessage msg) {
        std::cout << "server received message `" << msg.body() << "`\n";
        // Parse & Dispatch
    }

    void connect(Client *client) {
        assert(client);
        auto serverClient = serverNetwork_.connect(client);
        clients_.push_back(std::move(serverClient));
    }

    void update() {
        std::cout << "server update\n";
        // send `tick` message to all mods
    }
};