/**
* @file Game.hpp
* @brief Gameシーンでの動作を記述します
* @author tonarinohito
* @date 2018/9/21
*/
#pragma once
#include "Scene.hpp"
#include "../../Class/MapLoader.hpp"
#include "../../Class/MapCreator.hpp"
namespace Scene
{
	class Game final : public ISceneBase
	{
	private:
		MapLoader mapLoader;
		MapCreator mapCreator;
	public:
		Game();
		void Update() override;
		void Draw() override;
	};
}
