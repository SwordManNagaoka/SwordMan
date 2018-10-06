//----------------------------------------------------
//!@file	AddScoreEvent.hpp
//!@brief	スコアの追加イベントを作成します
//!@author	日比野　真聖
//!@date	2018/10/7
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Collision/Collision.hpp"
#include "../Components/BasicComponents.hpp"
#include "../ArcheType/Score.hpp"
#include "../GameController/GameController.h"


namespace Event
{
	class AddScoreEvent
	{
	public:
		static void Do()
		{
				std::vector<ECS::Entity*> addScores;
				ECS::Entity* totalScore;
				const auto& gameUI = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::GameUI);
				for (const auto& ui : gameUI)
				{
					if (ui->HasComponent<ECS::AddScoreTag>())
					{
						addScores.push_back(ui);
					}
					if (ui->HasComponent<ECS::TotalScoreDraw>())
					{
						totalScore = ui;
					}
				}
				const auto& attackCollisions = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Wepon);
				const auto& enemys = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
				for (const auto& collision : attackCollisions)
				{
					for (const auto& enemy : enemys)
					{
						if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*collision, *enemy))
						{
							const auto& players = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
							if (players.size() == 0) { return; }
							for (const auto& player : players)
							{
								//プレイヤーと敵の距離を検知します
								Vec2 playerPos = player->GetComponent<ECS::Position>().val;
								Vec2 collisionLength = Vec2(collision->GetComponent<ECS::HitBase>().w(), collision->GetComponent<ECS::HitBase>().h());
								Vec2 collisionPos = Vec2(collision->GetComponent<ECS::HitBase>().x(), collision->GetComponent<ECS::HitBase>().y());
								Vec2 enemyPos = enemy->GetComponent<ECS::Position>().val;

								//プレイヤーと敵の距離
								Vec2 distance = enemyPos - playerPos;
								float length = fabsf(distance.Length());
								//最小距離と最大距離の検出
								distance = (collisionPos + (collisionLength.x / 2.0f)) - playerPos;
								float minLength = fabsf(distance.Length());
								distance = (collisionPos + collisionLength.x) - playerPos;
								float maxLength = fabsf(distance.Length());

								//追加スコアとスコアの番号を検出
								int plusScore = DecideScore(length, minLength, maxLength);
								int addScoreNum = static_cast<int>(addScores.size());
								//スコアEntityを作成
								ECS::AddScoreArcheType()("font", Vec2(0,50 + (addScoreNum%3) * 32), plusScore);
								totalScore->GetComponent<ECS::TotalScoreDraw>().AddScore(plusScore);
								break;
							}
						}
					}
			}
		}
	private:
		//距離から得点の値を決める
		static int	DecideScore(const float length, const float minLength, const float maxLength)
		{
			if (length <= minLength)
			{
				return 200;
			}
			if (length >= maxLength - 20)
			{
				return 50;
			}
			if (minLength < length && length < maxLength - 30)
			{
				return 150;
			}
			return 100;
		}
	};
}