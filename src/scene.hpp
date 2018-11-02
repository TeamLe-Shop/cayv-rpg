#pragma once

#include <string>
#include "game.hpp"
#include "SDL.h"

namespace cayv {

class Scene {
public:
    Scene(std::string name, Game* g);
    virtual ~Scene();

    virtual void OnEnter();
    virtual void OnLeave();
    virtual void OnEvent(SDL_Event& event);

    virtual void Draw();
    virtual void Logic();

    std::string name;
    Game* game;
};

}
