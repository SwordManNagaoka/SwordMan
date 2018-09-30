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
#include "../Components/ComponentDatas/EnemyData.hpp"



namespace ECS
{
	//----------------------------------
	//敵生成器
	//----------------------------------
	class EnemyCreator
	{
	public:
		//敵の生成
		//型1: 渡すデータの型
		//型2: 生成するアーキタイプの型
		//引数: 渡すデータ型のデータ
		template<typename DataType, typename FuncType>
		static void Create(const DataType& data)
		{
			FuncType()(data);
		}
	};

	//共通
	class EnemyCommonArcheType : public IArcheType<const EnemyCommonData&>
	{
	public:
		ECS::Entity* operator()(const EnemyCommonData& data)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(data.pos);
			entity->AddComponent<Velocity>();
			entity->AddComponent<Direction>();
			entity->AddComponent<AnimationDraw>(data.imageName.c_str());
			entity->AddComponent<AnimationController>(data.changeAnimFrameTime, data.animNum);
			entity->AddGroup(ENTITY_GROUP::Enemy);
			return entity;
		}
	};

	//ノーマル(青鎧・水色羽)
	class NormalEnemyArcheType : public IArcheType<const NormalEnemyData&>
	{
	public:
		ECS::Entity* operator()(const NormalEnemyData& data)
		{
			ECS::Entity* entity = EnemyCommonArcheType()(data.commonData);
			AddCollision(entity, data);
			entity->AddComponent<ECS::EnemyDefaultMove>();
			return entity;
		}
	private:
		void AddCollision(ECS::Entity* entity, const NormalEnemyData& data)
		{
			if (!data.collisionData.commonData.isCollision) { return; }
			entity->AddComponent<HitBase>(data.collisionData.boxSize.x,data.collisionData.boxSize.y);
		}
	};

	//赤車輪
	class LeftMoveEnemyArcheType : public IArcheType<const LeftMoveEnemyData&>
	{
	public:
		ECS::Entity* operator()(const LeftMoveEnemyData& data)
		{
			ECS::Entity* entity = EnemyCommonArcheType()(data.commonData);
			AddCollision(entity, data);
			entity->AddComponent<EnemyDefaultMove>();
			return entity;
		}
	private:
		void AddCollision(ECS::Entity* entity, const LeftMoveEnemyData& data)
		{
			if (!data.collisionData.commonData.isCollision) { return; }
			entity->AddComponent<HitBase>(data.collisionData.boxSize.x, data.collisionData.boxSize.y);
		}
	};

	//緑バネ
	class JumpMoveEnemyArcheType : public IArcheType<const JumpMoveEnemyData&>
	{
	public:
		ECS::Entity* operator()(const JumpMoveEnemyData& data)
		{
			ECS::Entity* entity = EnemyCommonArcheType()(data.commonData);
			AddCollision(entity, data);
			entity->AddComponent<EnemyDefaultMove>();
			//entity->AddComponent<Physics>();
			//entity->AddComponent<TriggerJumpMove>(data.jumpPow);
			return entity;
		}
	private:
		void AddCollision(ECS::Entity* entity, const JumpMoveEnemyData& data)
		{
			if (!data.collisionData.commonData.isCollision) { return; }
			entity->AddComponent<HitBase>(data.collisionData.boxSize.x, data.collisionData.boxSize.y);
		}
	};

	//ゴール
	class GoalArcheType : public IArcheType<const GoalData&>
	{
	public:
		ECS::Entity* operator()(const GoalData& data)
		{
			ECS::Entity* entity = EnemyCommonArcheType()(data.commonData);
			AddCollision(entity, data);
			entity->AddComponent<EnemyDefaultMove>();
			return entity;
		}
	private:
		void AddCollision(ECS::Entity* entity, const GoalData& data)
		{
			if (!data.collisionData.commonData.isCollision) { return; }
			entity->AddComponent<HitBase>(data.collisionData.boxSize.x, data.collisionData.boxSize.y);
		}
	};
}