//----------------------------------------------------
//!@file	Player.hpp
//!@brief	プレイヤーの原型を作成します
//!@author	日比野　真聖
//!@date	2018/9/14
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../../Components/Collider.hpp"
#include "../../Components/Renderer.hpp"
#include "../GameController/GameController.h"
#include "../Components/Jump.hpp"
#include "../Components/Think.hpp"
#include "../Components/Behavior.hpp"
#include "../Components/AnimationController.hpp"


namespace ECS
{
	class PlayerArcheType : public IArcheType<const Vec2&,const Vec2&>
	{
	public:
		ECS::Entity* operator()(const Vec2& pos,const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<Rotation>();
			entity->AddComponent<HitBase>(static_cast<float>(size.x), static_cast<float>(size.y)).SetColor(255, 0, 0);
			entity->AddComponent<Physics>();
			entity->AddComponent<TriggerJumpMove>(-10);
			entity->AddComponent<Think>();
			entity->AddComponent<Behavior>();
			entity->AddComponent<Direction>();
			entity->AddComponent<AnimationDraw>("player");
			entity->AddComponent<AnimationController>(20, 2);
			entity->AddGroup(ENTITY_GROUP::Player);
			return entity;
		}
	};
}