#include "tilesandbox.hpp"

#include "SDL_image.h"
#include "log.hpp"
#include "window.hpp"

namespace cayv {

static SDL_Rect tileIdToRect(int id) {
    return SDL_Rect{(id - 1) * 32, 0, 32, 32};
}

TileSandbox::TileSandbox(std::string name, Game* g) : Scene(name, g) {
    tex = IMG_LoadTexture(g->window->renderer, "res/gfx_desu.png");
    if (tex == nullptr) {
        log(SEVERE, "Couldn't load texture from res/gfx_desu.png");
        abort();
    }
    // We want some gosu transparency fx
    if (SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND) == -1) {
        log(SEVERE, "WHAT? NOT SUPPORTED? THE FUCK?");
    }
}

TileSandbox::~TileSandbox() {
    SDL_DestroyTexture(tex);
}

void TileSandbox::Draw() {
    SDL_Rect rect = {tcx * 32, tcy * 32, 32, 32};
    SDL_Rect txsrcrect = tileIdToRect(tileToPut);
    drawTiles();
    auto ren = game->window->renderer;
    SDL_SetTextureAlphaMod(tex, 196);
    SDL_RenderCopy(ren, tex, &txsrcrect, &rect);
    SDL_SetTextureAlphaMod(tex, 255);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderDrawRect(ren, &rect);
}

void TileSandbox::Logic() {
    int mx, my;
    auto button = SDL_GetMouseState(&mx, &my);
    tcx = mx / 64;
    tcy = my / 64;
    if (button & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        tileAt(tcx, tcy) = tileToPut;
    }
}

void TileSandbox::OnEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_LEFT) {
            tileToPut -= 1;
        } else if (e.key.keysym.sym == SDLK_RIGHT) {
            tileToPut += 1;
        }
    }
}

uint8_t & TileSandbox::tileAt(int x, int y) {
    if (x >= W || y >= H) {
        log(SEVERE, "OOB ACCESS");
        abort();
    }
    return tiles[y * W + x];
}

void TileSandbox::drawTiles() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            auto t = tileAt(x, y);
            if (t == 0) {
                continue;
            }
            SDL_Rect src = tileIdToRect(t);
            SDL_Rect dst = {x * 32, y * 32, 32, 32};
            SDL_RenderCopy(game->window->renderer, tex, &src, &dst);
        }
    }
}

}
