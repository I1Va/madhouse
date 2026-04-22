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
public:
    std::unique_ptr<modlib::BmClient> connect(Client *client) {
        assert(client);
        return std::make_unique<ServerClient>(client);
    }

    void send_message_to_client(modlib::BmClient *client, bmsg::RawMessage msg) {
        assert(client);
        client->send(msg);
    }
};
