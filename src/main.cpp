#include "SDL.h"

#include "window.hpp"
#include "game.hpp"
#include "scene.hpp"

using namespace cayv;

class TestScene : public Scene
{
public:
    TestScene(std::string name, Game* g) : Scene(name, g) {}
    void Draw()
    {
        float t = SDL_GetTicks() / 360.f;
        SDL_Renderer* ren = game->window->renderer;
        SDL_SetRenderDrawColor(ren, (pow(cos(t), 2)),
                               255 * (pow(sin(t), 2)), 255, SDL_ALPHA_OPAQUE);
        SDL_Rect r = {0, 0, 150, 150};
        SDL_RenderFillRect(ren, &r);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }
};

int main()
{
    Window* w = new Window("Simmer softly something's boilin", 640, 480, false);
    w->max_fps = 60;

    Game g(w);
    g.AddScene(new TestScene("test", &g));
    g.SetScene("test");
    g.Cycle();

    return 0;
}
