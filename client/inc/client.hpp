#pragma once

#include <iostream>

#include "BmServerModule.hpp"

#include "graphics.hpp"
#include "client_world.hpp"

class Reader {
    const char* m_ptr;
    size_t m_remaining;

public:
    explicit Reader(std::string_view buffer) 
        : m_ptr(buffer.data()), m_remaining(buffer.size()) {}


    template <typename T>
    T read() {
        static_assert(std::is_trivially_copyable_v<T>, "Type must be POD/Trivially Copyable");
        
        if (m_remaining < sizeof(T)) {
            throw std::runtime_error("BMSG Reader: Unexpected end of stream");
        }

        T value;
        std::memcpy(&value, m_ptr, sizeof(T));
        
        m_ptr += sizeof(T);
        m_remaining -= sizeof(T);
        
        return value;
    }

    std::string_view readString() {
        uint16_t len = read<uint16_t>();

        if (m_remaining < len) {
            throw std::runtime_error("BMSG Reader: String length exceeds buffer");
        }

        std::string_view result(m_ptr, len);
        
        m_ptr += len;
        m_remaining -= len;
        
        return result;
    }

    bool empty() const { return m_remaining == 0; }
    size_t remaining() const { return m_remaining; }
};

class Client {
    Graphics graphics_;
    ClientWorld world_;

public:
    struct Config {
        Graphics::Config gfx_config;
    };

    Client(const Config &config): graphics_(config.gfx_config) {}

    void update() { 
        graphics_.render(world_); 
    }

    // TEMP
    void send(bmsg::RawMessage msg) {
        // bmsg::RawMessage msg(buffer);
        if (!msg.isCorrect()) {
            return;
        }
        const bmsg::Header* head = msg.header();
        
        std::string_view prefix = head->pref;
        std::string_view type = head->type;

        dispatch(prefix, type, msg.body());
    }
private:
    void dispatch(std::string_view prefix, std::string_view type, std::string_view body) {
        Reader reader(body);
        GameState d;
        if (type == "game state") {

        }
    }
    // void receive(GameState &state) override {
    //     world_.apply_game_state(state);
    // }
};
