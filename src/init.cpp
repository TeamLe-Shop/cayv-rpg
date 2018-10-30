#include "init.hpp"
#include "log.hpp"

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

namespace cayv {

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log(SEVERE, "Fayld to init SDL: %s", SDL_GetError());
        return false;
    }
    if (Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD) {
        log(WARN, "Mix_Init fail, yet still twerks... Ok.");
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        log(SEVERE, "HOLY SHIT, CAN'T OPEN AUDIO! BAIL!");
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        log(SEVERE, "Epic fail.");
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
