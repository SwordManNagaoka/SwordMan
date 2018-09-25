//----------------------------------------------------
//!@file	Think.hpp
//!@brief	思考(状態に応じた遷移)部分を作成します
//!@author	日比野　真聖
//!@date	2018/9/14
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../../Components/ComponentDatas/PlayerData.hpp"
#include "../../Class/TouchInput.hpp"

namespace ECS
{
	class Think : public Component
	{
	public:
		void	Initialize() override
		{
			data.state = PlayerData::State::Walk;

			if (entity->HasComponent<TriggerJumpMove>())
			{
				jumpMove = &entity->GetComponent<TriggerJumpMove>();
			}
		}
		void	Update() override
		{
			PlayerData::State	nowState = data.state;
			switch (nowState)
			{
			case PlayerData::State::Walk:
				if (TouchInput::GetInput().Push(0))
				{
					if (TouchInput::GetInput().GetTouchIDPos(0).x <= (System::SCREEN_WIDIH / 2.0f))
					{
						nowState = PlayerData::State::Jump;
					}
					else
					{
						if (jumpMove->IsLanding())
						{
							nowState = PlayerData::State::Attack;
						}
						else
						{
							nowState = PlayerData::State::JumpAttack;
						}
					}
				}
				break;
			case PlayerData::State::Jump:
				if (TouchInput::GetInput().Free(0))
				{
					nowState = PlayerData::State::Walk;
				}
				if (entity->HasComponent<TriggerJumpMove>())
				{
					if (jumpMove->IsLanding())
					{
						nowState = PlayerData::State::Walk;
					}	
				}
				break;
			case PlayerData::State::Attack:
				if (motionCnt.GetCurrentCount() >= 30)
				{
					if (jumpMove->IsLanding())
					{
						nowState = PlayerData::State::Walk;
					}
					else
					{
						nowState = PlayerData::State::Jump;
					}
				}
				break;
			case PlayerData::State::JumpAttack:
				if (motionCnt.GetCurrentCount() > 16)
				{
					if (jumpMove->IsLanding())
					{
						nowState = PlayerData::State::Walk;
					}
					else
					{
						nowState = PlayerData::State::Jump;
					}
				}
				break;
			case PlayerData::State::Damage:
				break;
			case PlayerData::State::Death:
				break;
			}
			motionCnt.Add();
			UpdateState(nowState);
		}
		void	Draw2D() override
		{

		}
		//!@brief	現在の状態を取得
		PlayerData::State	GetNowState() const
		{
			return data.state;
		}
		//!@brief	現在のモーションカウントを取得
		Counter	GetNowMotionCnt() const
		{
			return motionCnt;
		}
	private:
		void	Draw3D() override
		{
		}
		bool	UpdateState(const PlayerData::State& nowState)
		{
			if (data.state == nowState) { return false; }
			//更新
			motionCnt.Reset();
			data.state = nowState;
			return true;
		}
	private:
		PlayerData	data;
		Counter		motionCnt;
		TriggerJumpMove* jumpMove;
	};
}