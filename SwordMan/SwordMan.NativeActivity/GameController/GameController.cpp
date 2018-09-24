#include "GameController.h"
#include "../ResourceManager/ResourceManager.hpp"
#include "../../Components/BasicComponents.hpp"
#include "../../Components/Renderer.hpp"
#include "../../Components/Collider.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Player.hpp"
#include "../Class/TouchInput.hpp"

void GameController::ResourceLoad()
{
	ResourceManager::GetGraph().Load("image/a.png","a");
	//ResourceManager::GetGraph().Load("image/ground01.png", "map");
}

GameController::GameController():
	mapLoader("stage/mapparamtest.csv")
{
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();
	auto& e = pManager->AddEntity();
	e.AddComponent<ECS::Position>(100.f,100.f);
	e.AddComponent<ECS::CircleColiider>(20.f);
	e.AddComponent<ECS::SimpleDraw>("a");
	ECS::PlayerArcheType()(Vec2(0,0),Vec2(48,48));

	mapLoader.LoadMapArray();

	mapCreator.SetMapParam(mapLoader.GetMapParam());
	mapCreator.FillUpFlatMap(ECS::MapArcheType());
	mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetMapData());
}

void GameController::ResetGame()
{

}

void GameController::Update()
{
	pManager->Refresh();
	pManager->Update();

	
	TouchInput::GetInput().Run();
	mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetMapData());
}

void GameController::Draw()
{
	pManager->Draw2D();
}
