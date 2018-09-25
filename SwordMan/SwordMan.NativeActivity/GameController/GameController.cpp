#include "GameController.h"
#include "../ResourceManager/ResourceManager.hpp"
#include "../../Components/BasicComponents.hpp"
#include "../../Components/Renderer.hpp"
#include "../../Components/Collider.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Player.hpp"
#include "../Class/TouchInput.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Events/EventManager.hpp"
void GameController::ResourceLoad()
{
	ResourceManager::GetGraph().LoadDiv("image/player.png", "player", 2, 2, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/sword.png", "sword", 5, 5, 1, 192, 192);
	ResourceManager::GetGraph().LoadDiv("image/rolling", "rolling", 4, 4, 1, 288, 288);
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();	
	//初期シーン
	ECS::PlayerArcheType()(Vec2(150,300),Vec2(96,96));
	Scene::SceneManager::Get().ChangeScene(Scene::SceneManager::State::Game);
	//Event::EventManager().Get().Add(Scene::SceneManager::State::Game,Event::AAA);
}

void GameController::ResetGame()
{

}

void GameController::Update()
{
	TouchInput::GetInput().Update();
	pManager->Refresh();
	Event::EventManager::Get().Update();
	Scene::SceneManager::Get().Update();

}

void GameController::Draw()
{
	Scene::SceneManager::Get().Draw();
}
