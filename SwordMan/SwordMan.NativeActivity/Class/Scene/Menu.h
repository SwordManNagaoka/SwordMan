/**
* @file Menu.hpp
* @brief Menuシーンでの動作を記述します
* @author tonarinohito
* @date 2018/9/21
*/
#pragma once
#include "Scene.hpp"
#include "../Scene/SceneManager.hpp"
#include "../../Class/StageCreator.hpp"
#include "../../Class/CloudCreater.hpp"
#include "../../Class/StageLoader.hpp"

namespace Scene
{
	class Menu final : public AbstractScene
	{
	private:
		CloudCreater cloud;
		StageLoader stageLoader;
		StageCreator stageCreator;
	public:
		Menu(IOnSceneChangeCallback* sceneTitleChange, const Parameter& parame);
		~Menu();
		void Update() override;
		void Draw() override;
	};
}
