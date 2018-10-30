#pragma once

#include <string>
#include <vector>

namespace cayv {

class Scene;
class Window;

class Game {
public:
    explicit Game(Window* w);

    void AddScene(Scene* s);
    void SetScene(std::string name);

    void Cycle();

    Window* window;
private:
    Scene* currentscene = nullptr;
    std::vector<Scene*> scenes;
};

}
