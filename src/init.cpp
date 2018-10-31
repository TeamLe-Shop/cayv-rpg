#include "init.hpp"
#include "log.hpp"

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

namespace cayv {

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log(SEVERE, "Failed to init SDL: {S}", SDL_GetError());
        return false;
    }
    if (Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD) {
        log(WARN, "Mix_Init reported to fail.");
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        log(SEVERE, "Couldn't open audio.");
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        log(SEVERE, "IMG_Init failed");
        return false;
    }
    return true;
}

void cleanup() {
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    SDL_Quit();
}

}
