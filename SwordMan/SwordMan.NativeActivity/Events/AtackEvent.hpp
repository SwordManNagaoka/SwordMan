//----------------------------------------------------
//!@file	AttackEvent.hpp
//!@brief	当たり判定イベントを作成します
//!@author	日比野　真聖
//!@date	2018/9/16
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../GameController/GameController.h"
#include "../Collision/Collision.hpp"
#include "../Components/BasicComponents.hpp"
#include "../System/System.hpp"
#include "../../Components/EntityHealthState.hpp"
#include ".././ArcheType/Effect.hpp"
#include "../Components/EntityCounter.hpp"
#include "../Components/EnemyEffectMove.hpp"

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
				for (const auto& enemy : enemys)
				{
					if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*attackCollision, *enemy))
					{
						EnemyDestroy(*enemy,*attackCollision);
						break;
					}
				}
			}
		}

		static void PlayerToEnemy()
		{
			const auto& player = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
			const auto& enemys = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
			
			if (player.size() == 0) { return; }
			for (const auto& enemy : enemys)
			{	
				if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*player[0], *enemy))
				{
					if (player[0]->GetComponent<ECS::EntityHealthState>().GetCurrentState() == ECS::EntityHealthState::State::Damage) { return; }
					player[0]->GetComponent<ECS::EntityHealthState>().ChangeState(ECS::EntityHealthState::State::Damage);
					break;
				}
			}
		}
	private:
		//敵の倒されたときの処理
		static void EnemyDestroy(ECS::Entity& enemy,ECS::Entity& collision)
		{
			//攻撃された方向と逆の方向へ跳ねる
			Vec2 collisionPos = collision.GetComponent<ECS::Position>().val;
			collisionPos.x += 96.0f;
			Vec2 enemyPos = enemy.GetComponent<ECS::Position>().val;
			//方向ベクトル
			Vec2 dirVec = (enemyPos - collisionPos).Normalize();
			enemy.AddComponent<ECS::EnemyEffectMove>().SetDirMove(dirVec,18.0f);
			
			enemy.DeleteComponent<ECS::HitBase>();
			enemy.DeleteComponent<ECS::EnemyDefaultMove>();
			if (enemy.HasComponent<ECS::Physics>())
			{
				enemy.DeleteComponent<ECS::Physics>();
			}
			if (enemy.HasComponent<ECS::EnemyJumpMove>())
			{
				enemy.DeleteComponent<ECS::EnemyJumpMove>();
			}
			if (enemy.HasComponent<ECS::TriggerJumpMove>())
			{
				enemy.DeleteComponent<ECS::TriggerJumpMove>();
			}
			enemy.AddComponent<ECS::EntityCounter>().SetSpecifyCnt(30-1);
			enemy.AddComponent<ECS::KillEntity>(30);
		}
	};
}