//----------------------------------------------------
//!@file	Enemy.hpp
//!@brief	敵の原型を作成します
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
#include "../Components/EnemyDefaultMove.hpp"

namespace ECS
{
	//青鎧
	class Enemy1ArcheType : public IArcheType<const std::string&,const Vec2&,const Vec2&>
	{
	public:
		ECS::Entity* operator()(const std::string& imageName,const Vec2& pos,const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<HitBase>(size.x,size.y).SetColor(255,0,0);
			entity->AddComponent<EnemyDefaultMove>();
			entity->AddComponent<ECS::Direction>();
			entity->AddComponent<ECS::AnimationDraw>(imageName.c_str());
			entity->AddComponent<ECS::AnimationController>(20,2);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};


	//赤車輪
	class Enemy2ArcheType : public IArcheType<const std::string&,const Vec2&, const Vec2&>
	{
	public:
		ECS::Entity* operator()(const std::string& imageName,const Vec2& pos, const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<HitBase>(size.x, size.y).SetColor(255, 128, 0);
			entity->AddComponent<EnemyDefaultMove>();
			entity->AddComponent<ECS::Direction>();
			entity->AddComponent<ECS::AnimationDraw>(imageName.c_str());
			entity->AddComponent<ECS::AnimationController>(10, 4);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};

	//緑バネ
	class Enemy3ArcheType : public IArcheType<const std::string&,const Vec2&, const Vec2&>
	{
	public:
		ECS::Entity* operator()(const std::string& imageName,const Vec2& pos, const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<HitBase>(size.x, size.y).SetColor(255, 128, 0);
			entity->AddComponent<EnemyDefaultMove>();
			entity->AddComponent<ECS::Direction>();
			entity->AddComponent<ECS::AnimationDraw>(imageName.c_str());
			entity->AddComponent<ECS::AnimationController>(10, 6);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};

	//水色羽
	class Enemy4ArcheType : public IArcheType<const std::string&,const Vec2&, const Vec2&>
	{
	public:
		ECS::Entity* operator()(const std::string& imageName,const Vec2& pos, const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<HitBase>(size.x, size.y).SetColor(255, 128, 0);
			entity->AddComponent<EnemyDefaultMove>();
			entity->AddComponent<ECS::Direction>();
			entity->AddComponent<ECS::AnimationDraw>(imageName.c_str());
			entity->AddComponent<ECS::AnimationController>(10, 4);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};
}