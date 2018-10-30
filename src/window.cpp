#include "window.hpp"

#include "log.hpp"
#include "scene.hpp"

#include "SDL.h"

#include <stdlib.h>
#include <string>

namespace cayv {

Window::Window(std::string title, int w, int h, bool fullscreen) :
    max_fps(60)
{
    if (w < 1 || h < 1) {
        log(SEVERE, "Invalid window dimensions");
        exit(1);
    }

    int flags = 0;
    if (fullscreen) flags = flags | fullscreen;

    SDL_CreateWindowAndRenderer(w, h, flags, &sdlwin, &renderer);
    if (sdlwin == nullptr || renderer == nullptr) {
        log(SEVERE, "SDL Window init error: %s", SDL_GetError());
        exit(1);
    }
    SDL_SetWindowTitle(sdlwin, title.c_str());
}

Window::Window(std::string title, int w, int h, bool fulls, int rw, int rh)
    : Window(title, w, h, fulls)
{
    if (rw < 1 || rh < 1) {
        log(SEVERE, "Invalid renderer dimensions");
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, rw, rh);
}

void Window::Draw(Scene* s)
{
    SDL_RenderClear(renderer);
    s->Draw();
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(sdlwin);
}

}
