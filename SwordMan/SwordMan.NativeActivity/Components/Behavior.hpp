//----------------------------------------------------
//!@file	Think.hpp
//!@brief	思考(状態に応じた遷移)部分を作成します
//!@author	日比野　真聖
//!@date	2018/9/15
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../../Components/ComponentDatas/PlayerData.hpp"
#include "../../Components/Think.hpp"
#include "../../Components/Jump.hpp"


namespace ECS
{
	class Behavior : public Component
	{
	public:
		void	Initialize() override
		{
		}
		void	Update() override
		{
			if (entity->HasComponent<Think>())
			{
				auto think = entity->GetComponent<Think>();

				switch (think.GetNowState())
				{
				case PlayerData::State::Walk:
					if (entity->HasComponent<JumpMove>())
					{
						entity->GetComponent<JumpMove>().SetJumpFlag(false);
					}
					break;
				case PlayerData::State::Jump:
				{
					if (entity->HasComponent<JumpMove>())
					{
						entity->GetComponent<JumpMove>().SetJumpFlag(true);
					}
				}
				break;
				case PlayerData::State::Attack:
					break;
				case PlayerData::State::JumpAttack:
					break;
				case PlayerData::State::Damage:
					break;
				case PlayerData::State::Death:
					break;
				}
			}
		}
		void	Draw2D() override
		{

		}
	private:
		void	Draw3D() override {}
	};
}