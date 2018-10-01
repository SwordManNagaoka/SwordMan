//----------------------------------------------------
//!@file	AnimationController.hpp
//!@brief	アニメーションコントローラーを作成します
//!@author	日比野　真聖
//!@date	2018/9/17
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../../Components/ComponentDatas/PlayerData.hpp"
#include "../../Class/TouchInput.hpp"
#include "../Components/Renderer.hpp"
#include "../Utility/Counter.hpp"


namespace ECS
{
	//------------------------------------------------------------------------
	//コンストラクタ
	//デフォルト
	//AnimationController();
	//
	//引数
	//AnimationController( 切り替えるフレーム時間,チップ枚数 );
	//------------------------------------------------------------------------
	class AnimationController : public Component
	{
	public:
		AnimationController()
		{
			frameTime = 60;
			chipNumber = 1;
		}
		AnimationController(const int frameTime, const int chipNumber)
			: frameTime(frameTime)
			, chipNumber(chipNumber)
		{
		}
		void	Initialize() override
		{
			animationID = 0;
			animationCnt.Reset();
			//entity->GetComponent<ECS::AnimationDraw>().SetIndex(animationID);
		}
		void	Update() override
		{
			int currentTime = animationCnt.GetCurrentCount();
			if (frameTime == 0) { return; }
			animationID = currentTime / frameTime % chipNumber;
			animationCnt.Add();
		}
		void	Draw2D() override
		{
			if (entity->HasComponent<ECS::AnimationDraw>())
			{
				entity->GetComponent<ECS::AnimationDraw>().SetIndex(animationID);
			}
		}
	private:
		void	Draw3D() override {}
	public:
		//!@brief	アニメーションを切り替えるフレーム時間と枚数を設定
		//!@param[in]	frameTime	フレーム時間
		//!@param[in]	chipNumber	画像チップの枚数
		void	SetAnimationTime(const int frameTime, const int chipNumber)
		{
			this->frameTime = frameTime;
			this->chipNumber = chipNumber;
			animationCnt.Reset();
		}
	private:
		int		frameTime;
		int		chipNumber;
		int		animationID;
		Counter	animationCnt;
	};
}