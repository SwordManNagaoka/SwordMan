#include "GameController.h"
#include "../ResourceManager/ResourceManager.hpp"
#include "../../Components/BasicComponents.hpp"
#include "../../Components/Renderer.hpp"
#include "../../Components/Collider.hpp"
#include "../../ArcheType/Map.hpp"
#include "../Class/MapLoader.hpp"
#include "../../ArcheType/Player.hpp"

void GameController::ResourceLoad()
{
	ResourceManager::GetGraph().Load("image/a.png","a");
	ResourceManager::GetGraph().Load("image/ground01.png", "map");
}

GameController::GameController()
{
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();
	auto& e = pManager->AddEntity();
	e.AddComponent<ECS::Position>(100.f,100.f);
	e.AddComponent<ECS::CircleColiider>(20.f);
	e.AddComponent<ECS::SimpleDraw>("a");
	MapLoader("stage/maptest.csv", "map", Vec2(5, 5), 13, 8, 96, ECS::MapArcheType());
	ECS::PlayerArcheType()(Vec2(0,0),Vec2(48,48));
}

void GameController::ResetGame()
{

}

void GameController::Update()
{
	pManager->Refresh();
	pManager->Update();

	if (touchInput.Press(0))
	{
		DrawFormatString(touchInput.GetTouchIDPos(0).x, touchInput.GetTouchIDPos(0).y, GetColor(0,255,0),"タップ0番が押されています");
	}
	if (touchInput.Press(1))
	{
		DrawFormatString(touchInput.GetTouchIDPos(1).x, touchInput.GetTouchIDPos(1).y, GetColor(255, 255, 0), "タップ1番が押されています");
	}
	touchInput.Run();
}

void GameController::Draw()
{
	pManager->Draw2D();
}
