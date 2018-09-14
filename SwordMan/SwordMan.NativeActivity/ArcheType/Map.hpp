/**
* @file Map.hpp
* @brief Mapの原型作成します。
* @author tonarinohito
* @date 2018/9/14
* @note 参考元 https://github.com/SuperV1234/Tutorials
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "../../Components/Collider.hpp"
#include "../../Components/Renderer.hpp"
#include "../GameController/Game.h"
namespace ECS
{
	//マップチップ一つあたりの大きさは96x96の予定
	class MapArcheType : public IArcheType<const char* ,const Vec2&, const Vec2&, const int, const int, const int, const int>
	{
	public:
		ECS::Entity* operator()(const char* name, const Vec2& pos, const Vec2& velocity,const int srcX, const int srcY, const int w, const int h) override
		{
			ECS::Entity* entity = &ECS::EcsSystem::GetManager().AddEntity();
			entity->AddComponent<Position>(pos);
			entity->AddComponent<Velocity>(velocity);
			entity->AddComponent<HitBase>(static_cast<float>(w), static_cast<float>(h)).SetColor(255,0,0);
			entity->AddComponent<RectDraw>(name, srcX, srcY, w, h);
			entity->AddGroup(ENTITY_GROUP::Ground);
			return entity;
		}

	};
}