#include "Game.h"
#include "../../GameController/GameController.h"
#include "../../ECS/ECS.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Player.hpp"
#include "../../Events/EventManager.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Class/TouchInput.hpp"
#include "../../ArcheType/Enemy.hpp"


namespace Scene
{
	Game::Game() :
		mapLoader("stage/mapparamtest.csv")
	{
		mapLoader.LoadMapArray();

		mapCreator.SetMapParam(mapLoader.GetMapParam());
		mapCreator.FillUpFlatMap(ECS::MapArcheType());
		mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetMapData());

		//敵の生成
		ECS::Enemy1ArcheType()("enemy1", Vec2(1500, 40), Vec2(96, 96));
		ECS::Enemy2ArcheType()("enemy2", Vec2(1800, 160), Vec2(96, 96));
		ECS::Enemy3ArcheType()("enemy3", Vec2(1500, 400), Vec2(96, 96));
		ECS::Enemy4ArcheType()("enemy4", Vec2(1300, 300), Vec2(96, 96));
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
		}
		ECS::EcsSystem::GetManager().Update();
	}

	void Game::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}

}
