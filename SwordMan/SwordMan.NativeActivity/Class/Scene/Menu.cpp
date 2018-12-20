#include "Menu.h"
namespace Scene
{
	Menu::Menu(IOnSceneChangeCallback * sceneTitleChange, Parameter* parame)
		: AbstractScene(sceneTitleChange)
	{
		//平坦なのしか出さないのでステージパラメーターはなんでもいい
		stageLoader.LoadStage("stage/stageparam03.csv");
		stageLoader.LoadStageConstitution();
		//以下のようにしないと動的にマップチップを切り替えられない
		ResourceManager::GetGraph().RemoveGraph(stageLoader.GetStageParam().mapImage);
		ResourceManager::GetGraph().Load("image/ground01.png", stage1);
		ResourceManager::GetGraph().Load("image/ground03.png", stage3);
		const_cast<StageParam&>(stageLoader.GetStageParam()).mapImage = stage1;
		stageCreator.SetMapParam(stageLoader.GetStageParam());
		stageCreator.FillUpFlatMap();
	
		//ステージの生成
		stageCreator.Run(nullptr, nullptr, nullptr);
		ECS::Cloud()("cloud");
	}
	Menu::~Menu()
	{
		auto entity = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::GameUI);
		for (auto& e : entity)
		{
			e->Destroy();
		}
	}
	void Menu::Update()
	{
		stageCreator.Run(nullptr, nullptr, nullptr);
		cloud.Run();
		ECS::EcsSystem::GetManager().Update();
		if (TouchInput::GetInput().GetBtnPress(0) == 1 && TouchInput::GetInput().GetTouchIDPos(0).x >= System::SCREEN_WIDIH/2)
		{
			auto param = std::make_unique<Parameter>();
			param->Set<const char*>("stageNum", stage1.c_str());
			param->Set<const char*>("stagePath", "stage/stageparam01.csv");		//stringだとなぜかバグる
			GetCallback().OnSceneChange(SceneName::Game, param.get(), SceneStack::Non);
			return;
		}
		if (TouchInput::GetInput().GetBtnPress(0) == 1 && TouchInput::GetInput().GetTouchIDPos(0).x <= System::SCREEN_WIDIH / 2)
		{
			auto param = std::make_unique<Parameter>();
			param->Set<const char*>("stageNum", stage3.c_str());
			param->Set<const char*>("stagePath", "stage/stageparam03.csv");		//stringだとなぜかバグる
			GetCallback().OnSceneChange(SceneName::Game, param.get(), SceneStack::Non);
			return;
		}
	}
	void Menu::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}