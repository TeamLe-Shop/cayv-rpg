#include "window.hpp"

#include "log.hpp"

#include "SDL.h"

#include <stdlib.h>
#include <string>

namespace cayv {

Window::Window(std::string title, int w, int h, bool fullscreen)
{
    if (w < 1 || h < 1) {
        log(SEVERE, "Invalid window dimensions");
        exit(1);
    }

    int flags = 0;
    if (fullscreen) flags = flags | fullscreen;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(w, h, flags, &sdlwin, &renderer);
    SDL_SetWindowTitle(sdlwin, title.c_str());
    SDL_RenderSetLogicalSize(renderer, w, h);
}

Window::Window(std::string title, int w, int h, bool fulls, int rw, int rh)
{
    if (rw < 1 || rh < 1) {
        log(SEVERE, "Invalid renderer dimensions");
        exit(1);
    }

    Window(title, w, h, fulls);
    SDL_RenderSetLogicalSize(renderer, rw, rh);
}

void Window::DrawLoop()
{
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(sdlwin);
    SDL_Quit();
}

};
