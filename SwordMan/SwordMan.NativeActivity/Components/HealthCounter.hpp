//----------------------------------------------------
//!@file	HealthCounter.hpp
//!@brief	体力を作成します
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
	class HealthCounter : public Component
	{
	public:
		HealthCounter(const int maxHealth)
		{
			maxValue = maxHealth;
		}
		void	Initialize() override
		{
			if (!entity->HasComponent<Health>())
			{
				health = &entity->AddComponent<Health>();
				health->value.SetCounter(maxValue, 1, 0, maxValue);
			}
			else
			{
				health = &entity->GetComponent<Health>();
				health->value.SetCounter(maxValue, 1, 0, maxValue);
			}
		}
		void	Update() override
		{
			
		}
		void	Draw2D() override
		{
			
		}
		//加算
		void	Add()
		{
			health->value.Add();
		}
		//減算
		void	Sub()
		{
			health->value.Sub();
		}
		//現在の体力値の取得
		int		GetCurrentHealth() const
		{
			return health->value.GetCurrentCount();
		}
	private:
		void	Draw3D() override {}
	private:
		Health* health;
		int maxValue;
	};
}