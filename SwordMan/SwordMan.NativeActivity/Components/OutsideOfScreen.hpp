//----------------------------------------------------
//!@file	OutsideOfScreen.hpp
//!@brief	画面外に出たら、Entityをなくすコンポーネントを作成します
//!@author	日比野　真聖
//!@date	2018/9/28
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../../Components/ComponentDatas/PlayerData.hpp"
#include "../Components/Renderer.hpp"
#include "../Components/Think.hpp"


namespace ECS
{
	//--------------------------------------------------------------
	//画面外(左側のみ)に出たら、プレイヤーの状態をDeathにします
	//--------------------------------------------------------------
	class OutsideOfScreen : public Component
	{
	public:
		~OutsideOfScreen()
		{
			pos = nullptr;
		}
		void Initialize() override
		{
			pos = nullptr;
		}
		void Update() override
		{
			pos = &entity->GetComponent<Position>();
			float sizeX = entity->GetComponent<HitBase>().w();
			if (pos->val.x < 0 - sizeX)
			{
				entity->GetComponent<Think>().ChangeMotion(PlayerData::State::Death);
			}
		}
		void Draw2D() override {}
	private:
		void Draw3D() override {}
	private:
		Position* pos;
	};
}