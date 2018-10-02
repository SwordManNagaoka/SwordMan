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
		mapLoader.LoadStageConstitution();

		mapCreator.SetMapParam(mapLoader.GetStageParam());
		mapCreator.FillUpFlatMap(ECS::MapArcheType());
		mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetStageData());

		//敵の生成
		ECS::NormalEnemyData normalData;
		normalData.commonData.imageName = "enemy1";
		normalData.commonData.pos = Vec2(1500, 40);
		normalData.commonData.id = 1;
		normalData.commonData.animNum = 2;
		normalData.commonData.changeAnimFrameTime = 20;
		normalData.collisionData.boxSize = Vec2(96, 96);
		normalData.collisionData.commonData.isCollision = true;
		ECS::EnemyCreator::Create<ECS::NormalEnemyData, ECS::NormalEnemyArcheType>(normalData);

		ECS::JumpMoveEnemyData jumpData;
		jumpData.commonData.imageName = "enemy3";
		jumpData.commonData.pos = Vec2(1800, 150);
		jumpData.commonData.id = 2;
		jumpData.commonData.animNum = 5;
		jumpData.commonData.changeAnimFrameTime = 10;
		jumpData.collisionData.boxSize = Vec2(96, 96);
		jumpData.collisionData.commonData.isCollision = true;
		jumpData.jumpPow = -24.0f;
		ECS::EnemyCreator::Create<ECS::JumpMoveEnemyData, ECS::JumpMoveEnemyArcheType>(jumpData);
	}
	void Game::Update()
	{
		mapCreator.Run(ECS::MapArcheType(), false, &mapLoader.GetStageData());
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
