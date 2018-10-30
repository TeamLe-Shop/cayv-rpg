#include "init.hpp"
#include "log.hpp"

#include "SDL.h"

namespace cayv {

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log(SEVERE, "Fayld to init SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}

}
