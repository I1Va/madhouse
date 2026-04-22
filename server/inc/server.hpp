#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <memory>

#include "BmServerModule.hpp"
#include "server_network.hpp"


class Server : public modlib::BmServer {       
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
        serverNetwork_.forAllClients(cb);
    }

    void send(Client *client, bmsg::RawMessage msg) {
        if (!msg.isCorrect()) {
            std::cerr << "Dropping malformed message (invalid length or header)\n";
            return;
        }

        const bmsg::Header* head = msg.header();
        
        std::string prefix(static_cast<std::string_view>(head->pref));

        std::unordered_set<modlib::BmServerModule *> curPrefReceives; 
        for (auto* listener : allPrefixListeners_) {
            curPrefReceives.insert(listener);
        }
        if (prefixListeners_.contains(prefix)) {
            for (auto* listener : prefixListeners_.at(prefix)) {
                curPrefReceives.insert(listener);
            }
        }

        if (prefixOwners_.contains(prefix)) {
            curPrefReceives.insert(prefixOwners_[prefix]);
        } else {
            std::cerr << "No owner registered for prefix: " << prefix << "\n";
        }

        modlib::BmClient *serverClient = serverNetwork_.getServerClient(client);
        for (auto* listener : curPrefReceives) {
            listener->onMessage(serverClient, msg);
        }
    }

    void connect(Client *client) {
        serverNetwork_.connect(client);
    }

    void update() {
        std::cout << "server update\n";
        // send `tick` message to all mods
    }
};