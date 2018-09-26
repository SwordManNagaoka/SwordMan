//----------------------------------------------------
//!@file	EnemyDefaultMove.hpp
//!@brief	敵の基本的な動作のコンポーネントを作成します
//!@author	日比野　真聖
//!@date	2018/9/25
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../../Components/Collider.hpp"
#include "../../Components/Renderer.hpp"
#include "../GameController/GameController.h"
#include "../Components/AnimationController.hpp"


namespace ECS
{
	class EnemyDefaultMove : public Component
	{
	public:
		void Initialize() override
		{
			auto& grounds = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::Ground);

			if (grounds[0]->HasComponent<ECS::Velocity>())
			{
				vel = grounds[0]->GetComponent<ECS::Velocity>();
			}
			if (entity->HasComponent<ECS::Position>())
			{
				pos = &entity->GetComponent<ECS::Position>();
			}
			if (entity->HasComponent<ECS::HitBase>())
			{
				size.x = entity->GetComponent<ECS::HitBase>().w();
			}
		}
		void Update() override
		{
			pos->val.x -= vel.val.x;
			if (pos->val.x < 0 - size.x)
			{
				entity->Destroy();
			}
		}
		void Draw2D() override
		{

		}
	private:
		void Draw3D() override
		{

		}
	private:
		Position* pos;
		Velocity vel;
		Vec2 size;
	};
}
