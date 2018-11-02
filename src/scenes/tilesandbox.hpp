#pragma once

#include "scene.hpp"

#include "SDL.h"
#include "SDL_mixer.h"

namespace cayv {

constexpr int W = 10;
constexpr int H = 10;

class TileSandbox : public Scene
{
public:
    TileSandbox(std::string name, Game* g);
    ~TileSandbox();
    void Draw() override;
    void Logic() override;
    void OnEvent(SDL_Event& e) override;
private:
    uint8_t & tileAt(int x, int y);
    void drawTiles();
    SDL_Texture * tex;
    // Tile cursor x/y
    int tcx = 0, tcy = 0;
    // Tile to pu
    int tileToPut = 1;
    uint8_t tiles[W * H] = {};
};

}
