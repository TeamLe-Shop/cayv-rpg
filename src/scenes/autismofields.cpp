#include "autismofields.hpp"

#include "SDL_image.h"
#include "log.hpp"
#include "window.hpp"
#include "vector.hpp"

namespace cayv {

Vector2f flowers[] = {
    Vector2f(3, 5),
    Vector2f(2, 3),
    Vector2f(4, 9),
    Vector2f(0, 1),
    Vector2f(1, 1),
};

AutismoFields::AutismoFields(std::string name, Game* g) : Scene(name, g) {
    tex = IMG_LoadTexture(g->window->renderer, "res/gfx_desu.png");
    if (tex == nullptr) {
        log(SEVERE, "Couldn't load texture from res/gfx_desu.png");
        abort();
    }
    if (mus == NULL) {
        log(SEVERE, "Failed to load music from res/autismofields.xm");
        exit(1);
    }
    Mix_PlayMusic(mus, -1);
}

AutismoFields::~AutismoFields() {
    SDL_DestroyTexture(tex);
    Mix_FreeMusic(mus);
}

void AutismoFields::Draw() {
    SDL_Renderer * ren = game->window->renderer;
    SDL_Rect grass = {0, 0, 32, 32};
    SDL_Rect flower = {64, 0, 32, 32};
    SDL_Rect smileychan = {32, 0, 32, 32};
    for (int y = 0; y < 240 / 32 + 1; ++y) {
        for (int x = 0; x < 320 / 32; ++x) {
            SDL_Rect dst = {x * 32, y * 32, 32, 32};
            SDL_RenderCopy(ren, tex, &grass, &dst);
        }
    }
    SDL_Rect dst = {(int)scpos.x, (int)scpos.y, 32, 32};
    SDL_RenderCopy(ren, tex, &smileychan, &dst);
    for (auto f : flowers) {
        SDL_Rect dst = {(int)f.x * 32, (int)f.y * 32, 32, 32};
        SDL_RenderCopy(ren, tex, &flower, &dst);
    }
}

void AutismoFields::Logic() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Uint32 t = SDL_GetTicks();
    Vector2f speed(0, 0);
    if (!smileydance) {
        if (state[SDL_SCANCODE_LEFT]) {
            speed.x -= 1;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            speed.x += 1;
        }
        if (state[SDL_SCANCODE_UP]) {
            speed.y -= 1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            speed.y += 1;
        }

        if (state[SDL_SCANCODE_T]) {
            smileydance = true;
        }

        scpos = scpos + (speed.normalise() * 2);
    } else {
        if (state[SDL_SCANCODE_F]) {
            smileydance = false;
        }

        scpos = Vector2f(100, 100) + Vector2f(0, 50).rotateby(t / 200.f);

    }

}

}
