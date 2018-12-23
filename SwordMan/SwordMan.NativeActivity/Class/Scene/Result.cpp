#include "Result.h"

//アーキタイプ
#include "../../ArcheType/Button.hpp"
//コンポーネント
#include "../../Components/ImageFontDraw.hpp"
#include "../../Components/BlendMode.hpp"
#include "../../Utility/Converter.hpp"


#include <fstream>
#include "../../Class/DXFilieRead.hpp"


namespace Scene
{
	Result::Result(IOnSceneChangeCallback* sceneTitleChange, Parameter* parame)
		: AbstractScene(sceneTitleChange)
	{
		ECS::Entity* btn = ECS::ButtonArcheType()("pauseUI", Vec2(680, 400), Vec2(0, 0), Vec2(96, 144), 50);
		btn->GetComponent<ECS::CircleColiider>().SetOffset(48, 48);
		btn->AddComponent<ECS::BackTitleButtonTag>();
		btn->AddGroup(ENTITY_GROUP::GameUI);

		ECS::Entity* menuBtn = ECS::ButtonArcheType()("pauseUI", Vec2(480, 400), Vec2(192, 0), Vec2(96, 144), 50);
		menuBtn->GetComponent<ECS::CircleColiider>().SetOffset(48, 48);
		menuBtn->AddComponent<ECS::BackMenuButtonTag>();
		menuBtn->AddGroup(ENTITY_GROUP::GameUI);

		int scoreData = CommonData::TotalScore::val;
		int stageNo = CommonData::StageNum::val;

		//---スコアの表示---//
		ECS::Entity* scoreUI = &ECS::EcsSystem::GetManager().AddEntity();
		scoreUI->AddComponent<ECS::Color>(0,0,255);
		scoreUI->AddComponent<ECS::Position>(Vec2(100,100));
		scoreUI->AddComponent<ECS::ImageFontDraw>("font",Vec2(32,32),16).SetFontImageKind(false);
		scoreUI->GetComponent<ECS::ImageFontDraw>().SetDrawData("Score");
		scoreUI->AddGroup(ENTITY_GROUP::GameUI);

		ECS::Entity* scoreParam = &ECS::EcsSystem::GetManager().AddEntity();
		scoreParam->AddComponent<ECS::Color>(255, 0, 0);
		scoreParam->AddComponent<ECS::Position>(Vec2(300, 100));
		scoreParam->AddComponent<ECS::ImageFontDraw>("font", Vec2(32, 32), 16).SetFontImageKind(false);
		scoreParam->GetComponent<ECS::ImageFontDraw>().SetDrawData(Converter::ToString(scoreData).c_str());
		scoreParam->AddGroup(ENTITY_GROUP::GameUI);
		
		//---ランク表示---//
		ECS::Entity* rankUI = &ECS::EcsSystem::GetManager().AddEntity();
		rankUI->AddComponent<ECS::Color>(0, 0, 255);
		rankUI->AddComponent<ECS::Position>(Vec2(100,300));
		rankUI->AddComponent<ECS::ImageFontDraw>("font", Vec2(32, 32), 16).SetFontImageKind(false);
		rankUI->GetComponent<ECS::ImageFontDraw>().SetDrawData("Rank");
		rankUI->AddGroup(ENTITY_GROUP::GameUI);

		ECS::Entity* rankData = &ECS::EcsSystem::GetManager().AddEntity();
		rankData->AddComponent<ECS::Color>(255, 0, 0);
		rankData->AddComponent<ECS::Position>(Vec2(300, 300));
		rankData->AddComponent<ECS::ImageFontDraw>("font", Vec2(32, 32), 16).SetFontImageKind(false);
		std::string rankName;

		if (scoreData <= 2000)
		{
			rankName = "D";
		}
		else if(scoreData <= 4000)
		{
			rankName = "C";
		}
		else if (scoreData <= 6000)
		{
			rankName = "B";
		}
		else if (scoreData <= 8000)
		{
			rankName = "A";
		}
		else if (scoreData <= 10000)
		{
			rankName = "S";
		}
		rankData->GetComponent<ECS::ImageFontDraw>().SetDrawData(rankName.c_str());
		rankData->AddGroup(ENTITY_GROUP::GameUI);
		
		std::string stageName = "stage" + stageNo;
		stageName += ".dat";
		FileSystem().Save(stageName, &scoreData);

		//セーブデータのロード
		/*int data = -20;
		int stageNo = 1;
		std::string stageName = "stage" + stageNo;
		stageName += ".dat";
		FileSystem().Load(stageName, &data);*/
	}

	Result::~Result()
	{
		ECS::EcsSystem::GetManager().AllKill();
		ResourceManager::GetSound().Remove("BGM");
	}
	
	void Result::Update()
	{
		const auto& button = ECS::EcsSystem::GetManager().GetEntitiesByGroup(ENTITY_GROUP::GameUI);
		for (auto& b : button)
		{
			b->Update();
			if (b->HasComponent<ECS::BackTitleButtonTag>())
			{
				b->GetComponent<ECS::PushButton>().SetSceneCallBack(&GetCallback());
				auto changeFunc = [](Scene::IOnSceneChangeCallback* callBack)
				{
					callBack->OnSceneChange(SceneName::Game, nullptr, SceneStack::AllClear);
					return;
				};
				b->GetComponent<ECS::PushButton>().SetEventFunction(changeFunc);
			}
			if (b->HasComponent<ECS::BackMenuButtonTag>())
			{
				b->GetComponent<ECS::PushButton>().SetSceneCallBack(&GetCallback());
				auto changeFunc = [](Scene::IOnSceneChangeCallback* callBack)
				{
					callBack->OnSceneChange(SceneName::Menu, nullptr, SceneStack::AllClear);
					return;
				};
				b->GetComponent<ECS::PushButton>().SetEventFunction(changeFunc);
			}
		}
	}
	void Result::Draw()
	{
		ECS::EcsSystem::GetManager().OrderByDraw(ENTITY_GROUP::Max);
	}
}




