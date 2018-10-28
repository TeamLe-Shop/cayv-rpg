#pragma once

#include "SDL.h"

#include <string>

namespace cayv {

class Window {
public:
    Window(std::string title, int w, int h, bool fullscreen);
    Window(std::string title, int w, int h, bool fullscreen, int rw, int rh);

    void DrawLoop();

    ~Window();
private:
    SDL_Window* sdlwin;
    SDL_Renderer* renderer;
};

};
