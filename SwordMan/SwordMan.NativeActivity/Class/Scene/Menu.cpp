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
		if (TouchInput::GetInput().GetBtnPress(0) == 1)
		{
			auto param = std::make_unique<Parameter>();
			param->Set<std::string>("stageNum", stage3);
			param->Set<std::string>("stagePath", "stage/stageparam03.csv");
			GetCallback().OnSceneChange(SceneName::Game, param.get(), SceneStack::OneClear);
			return;
		}
	}
	void Menu::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}