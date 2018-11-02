#include "scene.hpp"

namespace cayv {

Scene::Scene(std::string n, Game* g) :
    name(n), game(g) {}
Scene::~Scene() {}

void Scene::OnEnter() {}
void Scene::OnLeave() {}
void Scene::OnEvent(SDL_Event& e) {}


void Scene::Draw() {}
void Scene::Logic() {}



}
