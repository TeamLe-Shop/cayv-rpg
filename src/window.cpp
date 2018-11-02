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
        log(SEVERE, "Failed to create window/renderer: {}", SDL_GetError());
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
    // Always set clear color explicitly, so that whatever render color
    // the various scenes draw shit with don't override this clear color.
    // Make it a fugly magenta so areas where the scene doesn't render anything are noticeable.
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    // Also set default render color to white, so scenes always render with white by default,
    // until they explicitly set another color.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    s->Draw();
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(sdlwin);
}

}
