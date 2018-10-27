#include "SDL.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>

struct Pos {
    int x, y;
};

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win;
    SDL_Renderer * ren;
    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP, &win, &ren);
    SDL_SetWindowTitle(win, "Cayv RPG - Autismo Fields");
    SDL_RenderSetLogicalSize(ren, 320, 240);
    Mix_Init(MIX_INIT_MOD);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024);
    Mix_Music* mus = Mix_LoadMUS("autismofields.xm");
    Mix_PlayMusic(mus, -1);
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "Epic fail." << std::endl;
        return 1;
    }
    SDL_Texture * tex = IMG_LoadTexture(ren, "res/gfx_desu.png");
    if (tex == NULL) {
        std::cout << "Texture load fail." << std::endl;
        return 1;
    }

    bool quit = false;

    Pos flowers[] = {
        { 3, 5},
        { 9, 4},
        { 2, 3},
        {5, 3},
        {1, 1},
    };

    Pos scpos = {196, 134};

    while (!quit) {
        Uint32 frame_begin = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
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
        SDL_RenderClear(ren);
        SDL_Rect grass = {0, 0, 32, 32};
        SDL_Rect flower = {64, 0, 32, 32};
        SDL_Rect smileychan = {32, 0, 32, 32};
        for (int y = 0; y < 240 / 32 + 1; ++y) {
            for (int x = 0; x < 320 / 32; ++x) {
                SDL_Rect dst = {x * 32, y * 32, 32, 32};
                SDL_RenderCopy(ren, tex, &grass, &dst);
            }
        }
        for (auto f : flowers) {
            SDL_Rect dst = {f.x * 32, f.y * 32, 32, 32};
            SDL_RenderCopy(ren, tex, &flower, &dst);
        }
        SDL_Rect dst = {scpos.x, scpos.y, 32, 32};
        SDL_RenderCopy(ren, tex, &smileychan, &dst);
        SDL_RenderPresent(ren);
        Uint32 time_took = SDL_GetTicks() - frame_begin;
        const Uint32 IDEAL_FRAME_TIME_MS = 17;
        if (time_took < IDEAL_FRAME_TIME_MS) {
            SDL_Delay(IDEAL_FRAME_TIME_MS - time_took);
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
