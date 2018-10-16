/**
* @file Cloud.hpp
* @brief 背景の雲の原型を作ります
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "../../Components/Renderer.hpp"
#include "../GameController/GameController.h"
#include "../../Components/MapMove.hpp"
#include "../../Utility/Random.hpp"
namespace ECS
{
	class Cloud : public IArcheType<const char*>
	{
	public:
		ECS::Entity* operator()(const char* name)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntity();
			Random rand;
			entity->AddComponent<Position>(float(System::SCREEN_WIDIH), rand.GetRand(128.f, float(System::SCREEN_HEIGHT - 300)));
			entity->AddComponent<Velocity>(rand.GetRand(1.f,3.f),0.f);
			if (rand.GetRand(0, 1) == 0)
			{
				entity->AddComponent<RectDraw>(name, 0, 0, 256, 128);
			}
			else
			{
				entity->AddComponent<RectDraw>(name, 0, 256, 512, 128);
			}
			entity->AddGroup(ENTITY_GROUP::Back2);
			return entity;
		}
	};
}