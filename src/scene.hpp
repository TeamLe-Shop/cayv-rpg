#pragma once

#include <string>
#include "game.hpp"

namespace cayv {

class Scene {
public:
    Scene(std::string name, Game* g);
    virtual ~Scene();

    virtual void OnEnter();
    virtual void OnLeave();

    virtual void Draw();
    virtual void Logic();

    std::string name;
    Game* game;
};

}
