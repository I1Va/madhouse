#pragma once

struct Tank {
    Cord pos;
    Dir dir;
    // delay of shooting
    // hp
    Tank() = default;

    TankInfo get_info() {
        TankInfo info;
        info.pos = pos;
        info.dir = dir;
        return info;
    }
};

struct Bullet {
    static constexpr int BULLET_SPEED = 1;

    Cord pos;
    Dir dir;
    int speed;           
    TankId owner;
    BulletId id;

    Bullet() = default;

    BulletInfo get_info() const {
        BulletInfo info;
        info.pos = pos;
        info.dir = dir;
        info.speed = speed;
        info.owner = owner;
        info.id = id;
        return info;
    }
};
