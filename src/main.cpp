#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "window.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "init.hpp"

#include <iostream>

using namespace cayv;

struct Pos {
    int x, y;
};

constexpr Pos flowers[] = {
    {3, 5},
    {9, 4},
    {2, 3},
    {5, 3},
    {1, 1},
};

class AutismoFields : public Scene
{
public:
    AutismoFields(std::string name, Game* g) : Scene(name, g) {
        tex = IMG_LoadTexture(g->window->renderer, "res/gfx_desu.png");
        if (tex == nullptr) {
            std::cerr << "HOLY SHIT, FAILED TO LOAD THE TEXTURE! ABORT!" << std::endl;
            abort();
        }
    }
    void Draw() override
    {
        SDL_Renderer * ren = game->window->renderer;
        SDL_Rect grass = {0, 0, 32, 32};
        SDL_Rect flower = {64, 0, 32, 32};
        SDL_Rect smileychan = {32, 0, 32, 32};
        for (int y = 0; y < 240 / 32 + 1; ++y) {
            for (int x = 0; x < 320 / 32; ++x) {
                SDL_Rect dst = {x * 32, y * 32, 32, 32};
                SDL_RenderCopy(ren, tex, &grass, &dst);
            }
        }
        SDL_Rect dst = {scpos.x, scpos.y, 32, 32};
        SDL_RenderCopy(ren, tex, &smileychan, &dst);
        for (auto f : flowers) {
            SDL_Rect dst = {f.x * 32, f.y * 32, 32, 32};
            SDL_RenderCopy(ren, tex, &flower, &dst);
        }
    }
    void Logic() override {
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
    }
private:
    SDL_Texture * tex;
    Pos scpos = {196, 134};
};

int main()
{
    if (!init()) {
        return 1;
    }
    Window w("Simmer softly something's boilin", 640, 480, false, 320, 240);

    if (Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD) {
        std::cerr << "Mix_Init fail, yet still twerks... Ok." << std::endl;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "HOLY SHIT, CAN'T OPEN AUDIO! BAIL!" << std::endl;
        return 1;
    }
    Mix_Music* mus = Mix_LoadMUS("autismofields.xm");
    if (mus == NULL) {
        std::cout << "Music load fail" << std::endl;
        return 1;
    }
    Mix_PlayMusic(mus, -1);
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "Epic fail." << std::endl;
        return 1;
    }

    Game g(&w);
    g.AddScene(new AutismoFields("test", &g));
    g.SetScene("test");
    g.Cycle();

    cleanup();

    return 0;
}
