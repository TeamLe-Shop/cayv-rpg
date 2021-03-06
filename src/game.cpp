#include "game.hpp"

#include "window.hpp"
#include "scene.hpp"
#include "log.hpp"

#include "SDL.h"

namespace cayv {

Game::Game(Window* w)
{
    window = w;
}

void Game::Cycle()
{
    bool quit = false;
    Uint32 ideal_ticks = 1000 / window->max_fps;

    while (!quit) {
        Uint32 st = SDL_GetTicks();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            currentscene->OnEvent(e);
            if (e.type == SDL_QUIT) quit = true;
        }
        window->Draw(currentscene);
        currentscene->Logic();
        if (window->max_fps > 0) {
            Uint32 dt = SDL_GetTicks() - st;
            if (dt < ideal_ticks) SDL_Delay(ideal_ticks - dt);
        }
    }
}

void Game::AddScene(std::unique_ptr<Scene> s)
{
    scenes.push_back(std::move(s));
}

void Game::SetScene(std::string name)
{
    Scene* x = nullptr;
    for (auto & s : scenes) {
        if (name == s->name) {
            x = s.get();
            break;
        }
    }

    if (x == nullptr) {
        log(WARN, "Attempted to switch to invalid state {}", name);
        return;
    }

    if (currentscene != nullptr) currentscene->OnLeave();

    x->OnEnter();

    currentscene = x;
}

}
