#include <memory>

#include "window.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "init.hpp"
#include "log.hpp"
#include "scenes/autismofields.hpp"

using namespace cayv;

int main()
{
    if (!init()) {
        return 1;
    }
    Window w("Simmer softly something's boilin", 640, 480, false, 320, 240);

    Game g(&w);
    g.AddScene(std::make_unique<AutismoFields>("test", &g));
    g.SetScene("test");
    g.Cycle();

    cleanup();

    return 0;
}
