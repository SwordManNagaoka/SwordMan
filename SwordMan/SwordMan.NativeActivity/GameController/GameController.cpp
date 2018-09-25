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
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();	
	//初期シーン
	ECS::PlayerArcheType()(Vec2(50,300),Vec2(48,48));
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
