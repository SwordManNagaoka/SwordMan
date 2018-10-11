/**
* @file   Pause.hpp
* @brief  Pauseシーンでの動作を記述します
* @author tonarinohito
* @date 2018/9/21
*/
#pragma once
#include "Scene.hpp"
namespace Scene
{
	class Pause final : public ISceneBase
	{
	public:
		Pause();
		~Pause();
		void Update() override;
		void Draw() override;
	};
}