#include "scene.hpp"

namespace cayv {

Scene::Scene(std::string n, Game* g) { name = n; game = g; }

void Scene::OnEnter() {}
void Scene::OnLeave() {}


void Scene::Draw() {}
void Scene::Logic() {}



}
