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
#include "../Components/EnemyJumpMove.hpp"


namespace ECS
{
	class EnemyCommonArcheType : public IArcheType<const EnemyCommonData&,const int>
	{
	public:
		ECS::Entity* operator()(const EnemyCommonData& data,const int id)
		{
			ECS::Entity* entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(data.pos);
			entity->AddComponent<Velocity>().val.x = data.moveSpeed;
			entity->AddComponent<HitBase>(data.size.x,data.size.y);
			entity->AddComponent<EnemyDefaultMove>();
			entity->AddComponent<Direction>();
			entity->AddComponent<AnimationDraw>(data.imageName.c_str());
			entity->AddComponent<AnimationController>(data.changeAnimFrameTime, data.animNum);

			switch (id)
			{
			case 0:	//青鎧
				entity->AddGroup(ENTITY_GROUP::Enemy);
				break;
			case 1: //赤
				entity->AddGroup(ENTITY_GROUP::Enemy);
				break;
			case 2: //緑バネ
				entity->AddComponent<Physics>();
				entity->AddComponent<TriggerJumpMove>(data.jumpPower);
				entity->AddComponent<EnemyJumpMove>(data.changeAnimFrameTime * 2);
				entity->AddGroup(ENTITY_GROUP::Enemy);
				break;
			case 3: //水色羽
				entity->AddGroup(ENTITY_GROUP::Enemy);
				break;
			case 4: //ゴール
				entity->AddGroup(ENTITY_GROUP::Back3);
				break;
			}
			return entity;
		}
	};
}