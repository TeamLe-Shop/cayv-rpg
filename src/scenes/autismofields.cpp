#include "autismofields.hpp"

#include "SDL_image.h"
#include "log.hpp"
#include "window.hpp"

namespace cayv {

constexpr Pos flowers[] = {
    {3, 5},
    {9, 4},
    {2, 3},
    {5, 3},
    {1, 1},
};

AutismoFields::AutismoFields(std::string name, Game* g) : Scene(name, g) {
    tex = IMG_LoadTexture(g->window->renderer, "res/gfx_desu.png");
    if (tex == nullptr) {
        log(SEVERE, "HOLY SHIT, FAILED TO LOAD THE TEXTURE! ABORT!");
        abort();
    }
    if (mus == NULL) {
        log(SEVERE, "Music load fail");
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
    SDL_Rect dst = {scpos.x, scpos.y, 32, 32};
    SDL_RenderCopy(ren, tex, &smileychan, &dst);
    for (auto f : flowers) {
        SDL_Rect dst = {f.x * 32, f.y * 32, 32, 32};
        SDL_RenderCopy(ren, tex, &flower, &dst);
    }
}

void AutismoFields::Logic() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) {
        scpos.x -= 2;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        scpos.x += 2;
    }
    if (state[SDL_SCANCODE_UP]) {
        scpos.y -= 2;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        scpos.y += 2;
    }
}

}