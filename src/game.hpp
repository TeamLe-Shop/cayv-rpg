#pragma once

#include <string>
#include <vector>
#include <memory>

namespace cayv {

class Scene;
class Window;

class Game {
public:
    explicit Game(Window* w);

    void AddScene(std::unique_ptr<Scene> s);
    void SetScene(std::string name);

    void Cycle();

    Window* window;
private:
    Scene* currentscene = nullptr;
    std::vector<std::unique_ptr<Scene>> scenes;
};

}
