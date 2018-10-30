#pragma once

#include "scene.hpp"

#include "SDL.h"
#include "SDL_mixer.h"

namespace cayv {

struct Pos {
    int x, y;
};

class AutismoFields : public Scene
{
public:
    AutismoFields(std::string name, Game* g);
    void Draw() override;
    void Logic() override;
private:
    SDL_Texture * tex;
    Pos scpos = {196, 134};
    Mix_Music* mus = Mix_LoadMUS("res/autismofields.xm");
};

}
