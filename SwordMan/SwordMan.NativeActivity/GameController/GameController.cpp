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
#include "../../Events/AtackEvent.hpp"
#include "../../ArcheType/Enemy.hpp"


void GameController::ResourceLoad()
{
	ResourceManager::GetGraph().Load("image/a.png", "health");
	ResourceManager::GetGraph().LoadDiv("image/sword.png", "sword", 5, 5, 1, 192, 192);
	ResourceManager::GetGraph().LoadDiv("image/rolling.png", "rolling", 4, 4, 1, 288, 288);
	ResourceManager::GetGraph().LoadDiv("image/enemy01.png", "enemy1", 2, 2, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy02.png", "enemy2", 4, 4, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy03.png", "enemy3", 6, 6, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy04.png", "enemy4", 4, 4, 1, 96, 96);

	ResourceManager::GetGraph().LoadDiv("image/goal.png", "goal", 1, 1, 1, 144, 192);
	ResourceManager::GetGraph().LoadDiv("image/player.png", "player", 6, 2, 3, 96, 96);
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();	
	//初期シーン
	ECS::PlayerArcheType()(Vec2(250,300),Vec2(64,96));
	
	Scene::SceneManager::Get().ChangeScene(Scene::SceneManager::State::Game);

	//イベント関数の登録
	Event::EventManager().Get().Add(Scene::SceneManager::State::Game, Event::CollisionEvent::AttackCollisionToEnemy);
	Event::EventManager().Get().Add(Scene::SceneManager::State::Game, Event::CollisionEvent::PlayerToEnemy);
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
