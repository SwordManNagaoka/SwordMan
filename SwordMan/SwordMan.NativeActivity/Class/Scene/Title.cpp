#include "Title.h"
#include "../../GameController/GameController.h"
#include "../../ECS/ECS.hpp"

//クラス
#include "../../Class/TouchInput.hpp"
#include "../../Class/Scene/SceneManager.hpp"
#include "../../Utility/Input.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
//アーキタイプ
#include "../../ArcheType/ArcheType.hpp"
#include "../../ArcheType/Cloud.hpp"
#include "../../ArcheType/Button.hpp"
#include "../../ArcheType/Player.hpp"
//コンポーネント


namespace Scene
{
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, Parameter* parame)
		: AbstractScene(sceneTitleChange)
	{
		stageLoader.LoadStage("stage/stageparam03.csv");
		stageLoader.LoadStageConstitution();
		ResourceManager::GetGraph().RemoveGraph(stageLoader.GetStageParam().mapImage);
		ResourceManager::GetGraph().Load("image/ground01.png", "stage1");
		ResourceManager::GetGraph().Load("image/ground02.png", "stage2");
		ResourceManager::GetGraph().Load("image/ground03.png", "stage3");
		ResourceManager::GetGraph().Load("image/title/taptostart.png", "taptostart");
		ResourceManager::GetGraph().Load("image/title/title.png", "title");
		const_cast<StageParam&>(stageLoader.GetStageParam()).mapImage = "stage1";
		stageCreator.SetMapParam(stageLoader.GetStageParam());
		stageCreator.FillUpFlatMap();
		//ステージの生成
		stageCreator.Run(nullptr, nullptr, nullptr);
		ECS::Cloud()("cloud");
		tapStartLogo = ECS::ArcheType()("taptostart", Vec2{ System::SCREEN_WIDIH / 2.f,500.f }, ENTITY_GROUP::GameUI);
		tapStartLogo->GetComponent<ECS::SimpleDraw>().DoCenter(true);
		title = ECS::ArcheType()("title", Vec2{ System::SCREEN_WIDIH / 2.f,225.f }, ENTITY_GROUP::GameUI);
		title->GetComponent<ECS::SimpleDraw>().DoCenter(true);
		
	}
	Title::~Title()
	{
		ResourceManager::GetGraph().RemoveGraph("title");
		ResourceManager::GetGraph().RemoveGraph("taptostart");
		auto entity = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::GameUI);
		for (auto& e : entity)
		{
			e->Destroy();
		}
	}
	
	void Title::Update()
	{
		cloud.Run();
		stageCreator.Run(nullptr, nullptr, nullptr);
		ECS::EcsSystem::GetManager().Update();
		if (TouchInput::GetInput().GetBtnPress(0) == 1)
		{
			isPlayGame = true;
		}
		if (isPlayGame)
		{
			titleEase.Run(Easing::QuintIn, 60.f);
			title->GetComponent<ECS::Position>().val.y = titleEase.GetVolume(225.f, (-600.f) - 225.f);
			startEase.Run(Easing::QuintIn, 60.f);
			tapStartLogo->GetComponent<ECS::Position>().val.y = startEase.GetVolume(500.f, (1200.f) - 500.f);
			if (titleEase.IsEaseEnd() && startEase.IsEaseEnd())
			{
				GetCallback().OnSceneChange(SceneName::Menu, nullptr, SceneStack::OneClear);
				return;
			}
		}
	}

	void Title::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}