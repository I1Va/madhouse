#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "API/textmsg_server.hpp"

class IAMapPlugin : public textmsg::Plugin {
    std::string name_ = "IAMapPlugin";
    std::vector<std::string> prefixes_ = {"map"};

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
};