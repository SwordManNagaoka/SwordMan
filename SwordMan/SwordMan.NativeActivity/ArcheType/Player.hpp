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
#include "../Components/HealthCounter.hpp"
#include "../Components/CorrectionPosition.hpp"
#include "../Components/OutsideOfScreen.hpp"
#include "../Components/SideHitBase.hpp"


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
			entity->AddComponent<HitBase>(size.x,size.y).SetColor(255, 0, 0);
			entity->AddComponent<Physics>();
			entity->AddComponent<TriggerJumpMove>(-24);
			entity->AddComponent<SideHitBase>(1.0f,96.0f).SetColor(0,255,0);
			entity->GetComponent<SideHitBase>().SetOffset(96.0f, 0.0f);
			entity->AddComponent<CorrectionPosition>(pos);
			entity->AddComponent<OutsideOfScreen>();
			entity->AddComponent<HealthCounter>(3);
			entity->AddComponent<Think>();
			entity->AddComponent<Behavior>();
			entity->AddComponent<Direction>();
			entity->AddComponent<AnimationDraw>("player");
			entity->AddComponent<AnimationController>(20, 2);
			entity->AddGroup(ENTITY_GROUP::Player);
			return entity;
		}
	};


	//仮
	class EnemyArcheType : public IArcheType<const Vec2&, const Vec2&>
	{
	public:
		ECS::Entity* operator()(const Vec2& pos, const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<Rotation>();
			entity->AddComponent<HitBase>(size.x, size.y).SetColor(0, 128, 0);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};
}