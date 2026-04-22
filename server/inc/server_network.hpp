#pragma once

#include <memory>
#include "BmServerModule.hpp"

class Client;
void NETWORK_SEND_MESSAGE_TO_CLIENT(Client *client, bmsg::RawMessage msg);
size_t NETWORK_GET_CLIENT_ID(Client *client);

class ServerClient : public modlib::BmClient {
    Client *client_=nullptr;
public:
    ServerClient(Client *client) {
        assert(client);
        client_ = client;
    }

    void send(bmsg::RawMessage msg) override {
        NETWORK_SEND_MESSAGE_TO_CLIENT(client_, msg);
    }

    size_t id() const override {
        return NETWORK_GET_CLIENT_ID(client_);
    }
};

class ServerNetwork {
    std::unordered_map<size_t, std::unique_ptr<modlib::BmClient>> clients_; 
public:
    void connect(Client *client) {
        assert(client);

        auto serverClient = std::make_unique<ServerClient>(client);
        size_t id = serverClient->id();
        if (clients_.contains(id)) {
            std::cerr << "client " << id << "has been already added\n"; 
            return;
        }
        clients_[id] = std::move(serverClient);
    }

    modlib::BmClient *getServerClient(Client *client) {
        size_t id = NETWORK_GET_CLIENT_ID(client);
        if (!clients_.contains(id)) return nullptr;
        return clients_[id].get();
    }

    void send_message_to_client(modlib::BmClient *client, bmsg::RawMessage msg) {
        assert(client);
        client->send(msg);
    }
    
    void forAllClients(const std::function<void(modlib::BmClient* client)> cb) {
        assert(cb);
        for (auto &[id, client] : clients_) {
            cb(client.get());
        }
    }
};
