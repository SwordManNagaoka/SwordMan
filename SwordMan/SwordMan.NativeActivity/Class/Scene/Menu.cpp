#include "Menu.h"
namespace Scene
{
	Menu::Menu(IOnSceneChangeCallback * sceneTitleChange, const Parameter & parame)
		: AbstractScene(sceneTitleChange)
	{
		stageLoader.LoadStage("stage/stageparam03.csv");
		stageLoader.LoadStageConstitution();
		//以下のようにしないと動的にマップチップを切り替えられない
		ResourceManager::GetGraph().Load("image/ground03.png", "stage3");
		const_cast<StageParam&>(stageLoader.GetStageParam()).mapImage = std::string("stage3");
		stageCreator.SetMapParam(stageLoader.GetStageParam());
		stageCreator.FillUpFlatMap();
	
		//ステージの生成
		stageCreator.Run(nullptr, nullptr, nullptr);
		ECS::Cloud()("cloud");
	}
	Menu::~Menu()
	{
	}
	void Menu::Update()
	{
		stageCreator.Run(nullptr, nullptr, nullptr);
		cloud.Run();
		ECS::EcsSystem::GetManager().Update();
		if (TouchInput::GetInput().GetBtnPress(0) == 1)
		{
			Parameter param;
			GetCallback().OnSceneChange(SceneName::Game, param, SceneStack::OneClear);
			return;
		}
	}
	void Menu::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}