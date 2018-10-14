#include "Title.h"
#include "../../GameController/GameController.h"
#include "../../ECS/ECS.hpp"

//クラス
#include "../../Class/TouchInput.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Utility/Input.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
//アーキタイプ
#include "../../ArcheType/Button.hpp"
#include "../../ArcheType/Player.hpp"
//コンポーネント


namespace Scene
{
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, const Parameter& parame)
		: AbstractScene(sceneTitleChange)
	{
		stageLoader.LoadStage("stage/mapparamtest.csv");
		stageLoader.LoadStageConstitution();
		stageCreator.SetMapParam(stageLoader.GetStageParam());
		stageCreator.FillUpFlatMap();
		//ステージの生成
		stageCreator.Run(nullptr, nullptr, nullptr);
	}
	Title::~Title()
	{
		//すべてのEntityを殺す処理があると便利
		auto entity = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::GameUI);
		for (auto& e : entity)
		{
			e->Destroy();
		}
	}
	
	void Title::Update()
	{
		stageCreator.Run(nullptr, nullptr, nullptr);
		ECS::EcsSystem::GetManager().Update();
		if (TouchInput::GetInput().GetBtnPress(0) == 1)
		{
			Parameter param;
			ECS::PlayerArcheType()(Vec2(250, 300), Vec2(64, 96));
			callBack->OnSceneChange(SceneName::Game, param, true);
			return;
		}
	}

	void Title::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}