#pragma once

#include "scene.hpp"

#include "SDL.h"
#include "SDL_mixer.h"
#include "vector.hpp"

namespace cayv {

class AutismoFields : public Scene
{
public:
    AutismoFields(std::string name, Game* g);
    ~AutismoFields();
    void Draw() override;
    void Logic() override;
private:
    SDL_Texture * tex;
    Vector2f scpos = Vector2f(196, 134);
    Mix_Music* mus = Mix_LoadMUS("res/autismofields.xm");
    bool smileydance = false;
};

}
