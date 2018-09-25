#include "Game.h"
#include "../../GameController/GameController.h"
#include "../../ECS/ECS.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Player.hpp"
#include "../../Events/EventManager.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Class/TouchInput.hpp"
namespace Scene
{
	Game::Game() :
		mapLoader("stage/mapparamtest.csv")
	{
		mapLoader.LoadMapArray();

		mapCreator.SetMapParam(mapLoader.GetMapParam());
		mapCreator.FillUpFlatMap(ECS::MapArcheType());
		mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetMapData());
	}
	void Game::Update()
	{
		mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetMapData());
		auto& player = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
		auto& ground = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Ground);
		//地形との衝突応答を行う
		for (const auto& p : player)
		{
			p->GetComponent<ECS::Physics>().PushOutEntity(ground);
			p->GetComponent<ECS::Physics>().SetCollisionFunction(Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>);
			p->GetComponent<ECS::TriggerJumpMove>().SetJumpTrigger(TouchInput::GetInput().Push(0));
			p->GetComponent<ECS::TriggerJumpMove>().SetFallTrigger(TouchInput::GetInput().Free(0));
		}
		ECS::EcsSystem::GetManager().Update();
	}

	void Game::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}

}
