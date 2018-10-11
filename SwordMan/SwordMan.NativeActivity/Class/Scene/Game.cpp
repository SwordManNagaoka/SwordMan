#include "Game.h"
#include "../../GameController/GameController.h"
#include "../../ECS/ECS.hpp"
#include "../../ArcheType/Map.hpp"
#include "../../ArcheType/Player.hpp"
#include "../../Events/EventManager.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Class/TouchInput.hpp"
#include "../../ArcheType/Enemy.hpp"
#include "../../ArcheType/HealthUI.hpp"
#include "../../ArcheType/Score.hpp"
#include "../../ArcheType/Button.hpp"


namespace Scene
{
	Game::Game() :
		mapLoader("stage/mapparamtest.csv")
	{
		mapLoader.LoadStageConstitution();
		mapCreator.SetMapParam(mapLoader.GetStageParam());
		mapCreator.FillUpFlatMap();
		//ステージの生成
		mapCreator.Run(&mapLoader.GetStageData(), &mapLoader.GetSkyData(),&mapLoader.GetEnemyData());
		//Entityの生成
		ECS::PlayerArcheType()(Vec2(250, 300), Vec2(64, 96));
		for (int i = 0; i < 3; ++i)
		{
			ECS::HealthUIArcheType()(i,Vec2(500 + i * 144, 640));
		}
		ECS::TotalScoreArcheType()("font", Vec2(0, 0));
	}
	Game::~Game()
	{

	}
	void Game::Update()
	{
		mapCreator.Run(&mapLoader.GetStageData(), &mapLoader.GetSkyData(), &mapLoader.GetEnemyData());
		
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
