#pragma once

#include "SDL.h"

#include <string>

namespace cayv {

class Scene;

class Window {
public:
    Window(std::string title, int w, int h, bool fullscreen);
    Window(std::string title, int w, int h, bool fullscreen, int rw, int rh);
    void SetTitle(std::string title);

    void Draw(Scene* s);

    ~Window();

    int max_fps;
    SDL_Window* sdlwin;
    SDL_Renderer* renderer;
};

}
