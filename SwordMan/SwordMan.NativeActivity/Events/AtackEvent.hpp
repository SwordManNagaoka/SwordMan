﻿//----------------------------------------------------
//!@file	AttackEvent.hpp
//!@brief	当たり判定イベントを作成します
//!@author	日比野　真聖
//!@date	2018/9/16
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../GameController/GameController.h"
#include "../Collision/Collision.hpp"
#include "../System/System.hpp"
//アーキタイプ
#include "../ArcheType/Score.hpp"
#include "../ArcheType/Effect.hpp"
//コンポーネント
#include "../Components/BasicComponents.hpp"
#include "../Components/EnemyDefaultMove.hpp"
#include "../Components/Jump.hpp"
#include "../Components/EntityHealthState.hpp"
#include "../Components/EntityCounter.hpp"
#include "../Components/EnemyEffectMove.hpp"
#include "../Components/EnemyJumpMove.hpp"
#include "../Components/TotalScoreDraw.hpp"

namespace Event
{
	class CollisionEvent
	{
	public:
		static void AttackCollisionToEnemy()
		{
			const auto& attackCollisions = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Wepon);
			const auto& enemys = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
			for (const auto& attackCollision : attackCollisions)
			{
				if (!attackCollision->HasComponent<ECS::HitBase>()) { continue; }
				for (const auto& enemy : enemys)
				{
					if (!enemy->HasComponent<ECS::HitBase>()) { continue; }
					if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*attackCollision, *enemy))
					{
						EnemyDestroy(*enemy, *attackCollision);
						break;
					}
				}
			}
			EnemyDestroyEffect();
		}

		static void PlayerToEnemy()
		{
			const auto& player = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
			if (player.size() == 0) { return; }

			const auto& enemys = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
			for (const auto& enemy : enemys)
			{
				if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*player[0], *enemy))
				{
					if (player[0]->GetComponent<ECS::EntityHealthState>().GetCurrentState() == ECS::EntityHealthState::State::Damage) { return; }
					player[0]->GetComponent<ECS::EntityHealthState>().ChangeState(ECS::EntityHealthState::State::Damage);
					Sound damage("damage");
					damage.Play(false, true);
					break;
				}
			}
		}
	private:
		//敵の倒されたときの処理
		static void EnemyDestroy(ECS::Entity& enemy, ECS::Entity& collision)
		{
			//攻撃された方向と逆の方向へ跳ねる
			Vec2 collisionPos = collision.GetComponent<ECS::Position>().val;
			collisionPos.x += 96.0f;
			Vec2 enemyPos = enemy.GetComponent<ECS::Position>().val;
			//方向ベクトル
			Vec2 dirVec = (enemyPos - collisionPos).Normalize();
			enemy.AddComponent<ECS::EnemyEffectMove>().SetDirMove(dirVec, 36.0f);

			//スコアの決定
			DecideScore(enemy, collision);

			enemy.DeleteComponent<ECS::HitBase>();
			enemy.DeleteComponent<ECS::EnemyDefaultMove>();
			enemy.DeleteComponent<ECS::EnemyJumpMove>();
			enemy.DeleteComponent<ECS::TriggerJumpMove>();
			if (enemy.HasComponent<ECS::Physics>())
			{
				enemy.DeleteComponent<ECS::Physics>();
			}
			enemy.GetComponent<ECS::Color>().red = 255;
			enemy.GetComponent<ECS::Color>().blue = 128;
			enemy.GetComponent<ECS::Color>().green = 128;
			enemy.GetComponent<ECS::AlphaBlend>().alpha = 192;
			enemy.AddComponent<ECS::EntityCounter>().SetSpecifyCnt(30 - 1);
			enemy.AddComponent<ECS::KillEntity>(30);
		}
	private:
		//スコアを決定する
		static void DecideScore(ECS::Entity& enemy, ECS::Entity& collision)
		{
			std::vector<ECS::Entity*> addScores;
			ECS::Entity* totalScore = nullptr;
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

			if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(collision, enemy))
			{
				const auto& players = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
				if (players.size() == 0) { return; }
				Vec2 playerPos = players[0]->GetComponent<ECS::Position>().val;


				//敵との距離を計算
				Vec2 enemyPos = enemy.GetComponent<ECS::Position>().val;
				Vec2 enemySize = Vec2(enemy.GetComponent<ECS::HitBase>().w() / 2.0f, enemy.GetComponent<ECS::HitBase>().h() / 2.0f);
				float enemyLength = fabsf(enemySize.Length());

				//コリジョンの幅と高さ
				Vec2 collisionPos = collision.GetComponent<ECS::Position>().val;
				collisionPos.x += 96.0f;
				Vec2 collisionSize = Vec2(collision.GetComponent<ECS::HitBase>().w() / 2.0f, collision.GetComponent<ECS::HitBase>().h() / 2.0f);
				float collisionLength = fabsf(collisionSize.Length());

				//プレイヤーと敵の距離
				Vec2 distance = enemyPos - collisionPos;
				float length = fabsf(distance.Length());
				float scoreLength = collisionLength + enemyLength;

				int plusScore = CalcScore(length, scoreLength);
				//追加スコアとスコアの番号を検出
				int addScoreNum = static_cast<int>(addScores.size());
				//エフェクト作成
				EnemyHitEffect(enemy, plusScore);
				//スコアEntityを作成
				//スコアEntityを作成
				Vec2 pos(0, 50 + (addScoreNum * 32));
				if (!addScores.empty() && addScores.back()->GetComponent<ECS::Position>().val.y == pos.y)
				{
					pos.y += 32;
				}
				ECS::AddScoreArcheType()("font", pos, plusScore);
				if (totalScore->HasComponent<ECS::TotalScoreDraw>())
				{
					totalScore->GetComponent<ECS::TotalScoreDraw>().AddScore(plusScore);
				}
				
			}
		}
		//スコアの計算
		static int CalcScore(const float distance, const float scoreLength)
		{
			int plusScore = 0;
			if (distance >= scoreLength * 0.8f)
			{
				plusScore = 50;
			}
			else if (distance >= scoreLength * 0.6f)
			{
				plusScore = 100;
			}
			else if (distance >= scoreLength * 0.4f)
			{
				plusScore = 150;
			}
			else if (distance >= 0)
			{
				plusScore = 200;
			}
			return plusScore;
		}
		private:
			//敵の当たり判定時のエフェクト
			static void EnemyHitEffect(const ECS::Entity& enemy, const int score)
			{
				//エフェクトの作成
				//サウンドをつける
				Sound hit("hit");
				ECS::EffectData effect;
				effect.imageName = "hitWeak";
				effect.pos = enemy.GetComponent<ECS::Position>().val;
				effect.killTime = 12;
				effect.changeChipFrameTime = 3;
				effect.chipNum = 4;
				if (score >= 200)
				{
					//サウンドをつける
					Sound smash("smash");
					smash.Play(false, true);
					effect.imageName = "hitStrong";
					effect.changeChipFrameTime = 3;
					effect.chipNum = 5;
					effect.killTime = 15;
				}
				hit.Play(false, true);
				ECS::Entity* effectEntity = ECS::EffectArcheType()(effect);
				effectEntity->GetComponent<ECS::AnimationDraw>().Offset(Vec2(-48.0f, -48.0f));
			}
			//敵の爆発時のエフェクト
			static void EnemyDestroyEffect()
			{
				const auto& enemys = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
				for (const auto& enemy : enemys)
				{
					if (!enemy->HasComponent<ECS::KillEntity>()) { continue; }
					if (enemy->GetComponent<ECS::EntityCounter>().IsSpecifyCnt())
					{
						//サウンドをつける
						Sound s("bomb");
						s.Play(false, true);
						ECS::EffectData effect;
						effect.imageName = "bomb";
						effect.pos = enemy->GetComponent<ECS::Position>().val;
						effect.changeChipFrameTime = 3;
						effect.chipNum = 4;
						effect.killTime = 12;
						ECS::Entity* effectEntity = ECS::EffectArcheType()(effect);
						effectEntity->GetComponent<ECS::AnimationDraw>().Offset(Vec2(-48.0f, -48.0f));
						break;
					}
				}
			}
	};
}