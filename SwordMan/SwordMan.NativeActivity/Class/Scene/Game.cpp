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
		mapCreator.Run(&mapLoader.GetStageData()/*, &mapLoader.GetEnemyData()*/);

		//敵の生成
		/*ECS::EnemyCommonData data;
		data.imageName = "enemy1";
		data.pos = Vec2(1500, 100);
		data.size = Vec2(96, 96);
		data.animNum = 2;
		data.changeAnimFrameTime = 20;
		data.jumpPower = 0;
		data.moveSpeed = 0;
		ECS::EnemyCommonArcheType()(data, 0);

		ECS::EnemyCommonData data2;
		data2.imageName = "enemy2";
		data2.pos = Vec2(2100, 150);
		data2.size = Vec2(96, 96);
		data2.animNum = 4;
		data2.changeAnimFrameTime = 10;
		data2.jumpPower = 0.0f;
		data2.moveSpeed = 3.0f;
		ECS::EnemyCommonArcheType()(data2, 1);

		ECS::EnemyCommonData data3;
		data3.imageName = "enemy3";
		data3.pos = Vec2(1600, 130);
		data3.size = Vec2(96, 96);
		data3.animNum = 5;
		data3.changeAnimFrameTime = 45;
		data3.jumpPower = -12.0f;
		data3.moveSpeed = 0.0f;
		ECS::EnemyCommonArcheType()(data3, 2);

		ECS::EnemyCommonData data4;
		data4.imageName = "enemy4";
		data4.pos = Vec2(2000, 160);
		data4.size = Vec2(96, 96);
		data4.animNum = 4;
		data4.changeAnimFrameTime = 10;
		data4.jumpPower = 0.0f;
		data4.moveSpeed = 0.0f;
		ECS::EnemyCommonArcheType()(data4, 3);*/
	}
	void Game::Update()
	{
		mapCreator.Run(&mapLoader.GetStageData()/*, &mapLoader.GetEnemyData()*/);
		auto& player = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
		auto& ground = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Ground);
		//地形との衝突応答を行う
		for (const auto& p : player)
		{
			p->GetComponent<ECS::Physics>().PushOutEntity(ground);
			p->GetComponent<ECS::Physics>().SetCollisionFunction(Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>);
		}
		auto& enemy = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
		for (const auto& e : enemy)
		{
			if (e->HasComponent<ECS::Physics>())
			{
				e->GetComponent<ECS::Physics>().PushOutEntity(ground);
				e->GetComponent<ECS::Physics>().SetCollisionFunction(Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>);
			}
		}
		ECS::EcsSystem::GetManager().Update();
	}

	void Game::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}

}
