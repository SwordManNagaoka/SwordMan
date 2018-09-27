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
#include "../../Components/HealthCounter.hpp"
#include "../../Components/AnimationController.hpp"

namespace ECS
{
	class Think : public Component
	{
	public:
		void	Initialize() override
		{
			data.state = PlayerData::State::Walk;
			motionEndFlag = false;
			if (entity->HasComponent<TriggerJumpMove>())
			{
				jumpMove = &entity->GetComponent<TriggerJumpMove>();
			}
			if (entity->HasComponent<HealthCounter>())
			{
				health = &entity->GetComponent<HealthCounter>();
			}
		}
		void	Update() override
		{
			PlayerData::State	nowState = data.state;
			
			switch (nowState)
			{
			case PlayerData::State::Walk:
				if (LeftButtonTap())
				{
					nowState = PlayerData::State::Jump;
				}
				if (RightButtonTap())
				{
					nowState = PlayerData::State::Attack;
				}
				if (!jumpMove->IsLanding())
				{
					nowState = PlayerData::State::Airworthiness;
				}
				break;
			case PlayerData::State::Jump:
				if (jumpMove->IsLanding())
				{
					nowState = PlayerData::State::Walk;	
				}
				else
				{
					nowState = PlayerData::State::Airworthiness;
				}
				break;
			case PlayerData::State::Airworthiness:	
				if (RightButtonTap())
				{
					nowState = PlayerData::State::JumpAttack;
				}
				if (jumpMove->IsLanding())
				{
					nowState = PlayerData::State::Walk;
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
						nowState = PlayerData::State::Airworthiness;
					}
				}
				break;
			case PlayerData::State::JumpAttack:
				if (motionEndFlag)
				{
					if (jumpMove->IsLanding())
					{
						nowState = PlayerData::State::Walk;
					}
				}
				if (motionCnt.GetCurrentCount() > 16)
				{
					motionEndFlag = true;
				}
				if (jumpMove->IsLanding())
				{
					motionEndFlag = true;
				}
				break;
			case PlayerData::State::Damage:
				if (motionCnt.GetCurrentCount() == 0)
				{
					health->Sub();
				}
				if (health->GetCurrentHealth() <= 0)
				{
					nowState = PlayerData::State::Death;
				}
				if (motionCnt.GetCurrentCount() >= 30)
				{
					if (jumpMove->IsLanding())
					{
						nowState = PlayerData::State::Walk;
					}
				}
				break;
			case PlayerData::State::Death:
				if (!entity->HasComponent<KillEntity>())
				{
					entity->AddComponent<KillEntity>(30);
				}
				break;
			}
			motionCnt.Add();
			UpdateState(nowState);
		}
		void	Draw2D() override
		{
			//printfDx("状態:%d", data.state);
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
		//モーションを変化させます
		void	ChangeMotion(const PlayerData::State& motionState)
		{
			data.state = motionState;
		}
		//モーションの終了かのどうかのチェック
		//true:終了 false:終了していない
		bool	CheckMotionCancel()
		{
			return motionEndFlag;
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
			motionEndFlag = false;
			return true;
		}
		bool	LeftButtonTap()
		{
			if (TouchInput::GetInput().Push(0))
			{
				if (TouchInput::GetInput().GetTouchIDPos(0).x <= (System::SCREEN_WIDIH / 2.0f))
				{
					return true;
				}
			}
			return false;
		}
		bool	RightButtonTap()
		{
			if (TouchInput::GetInput().Push(0))
			{
				if (TouchInput::GetInput().GetTouchIDPos(0).x > (System::SCREEN_WIDIH / 2.0f))
				{
					return true;
				}
			}
			return false;
		}
	private:
		PlayerData	data;
		Counter		motionCnt;
		TriggerJumpMove* jumpMove;
		HealthCounter* health;
		bool motionEndFlag;
	};
}